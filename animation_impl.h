#pragma once


#include "i_animation.h"

//
#include "dc_debug/uw_log.h"

//
#include <atomic>

//TODO: !!! Осталось сделать реализацию IAnimationDrawingHandler, которая отрисовывает картинки
//TODO: !!! Затем биндинги в белку, IAnimationDrawingHandler не особо и нужно пока
//TODO: !!! А IAnimationFrameChangeHandler нужен в белке, это либо класс, либо свободная функция, с возможностью использования и того и другого
//TODO: !!! При биндинге эти колбеки принимают IAnimation, надо будет сделать из этого указателя shared_ptr и передать стандартную обёртку, но пользователь ССЗБ, если будет это где-то сохранять
//TODO: !!! Нужно сделать append версии всех addSpriteAnimation* методов


// #define MARTY_DRAW_CONTEXT_ANIMATION_IMPL_USE_ATOMIC


namespace marty_draw_context {


struct AnimationFrameInfo
{
    std::shared_ptr<IImageList>  pImgList    ;
    int                          imgId       = -1;
    ImageSize                    imgPos      = ImageSize{0,0}; // положение спрайта в картинке
    ImageSize                    imgSize     = ImageSize{0,0}; // размер спрайта в картинке
    ImageSize                    pivotPoint  = ImageSize{0,0}; // базовая точка спрайта
    std::uint32_t                frameTiming = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду
    int                          frameScalePercent  = 100;

protected:

    ImageSize scaleImageSize(ImageSize sz) const
    {
        return ImageSize{sz.width*frameScalePercent/100, sz.height*frameScalePercent/100};
    }

public:

    ImageSize getScaledSize() const
    {
        return scaleImageSize(imgSize);
    }

    ImageSize getScaledPivotPoint() const
    {
        return scaleImageSize(pivotPoint);
    }



}; // struct AnimationFrameInfo


struct AnimationInfo
{
    AnimationInfo() = default;
    AnimationInfo(const AnimationInfo&) = default;
    AnimationInfo& operator=(const AnimationInfo&) = default;
    AnimationInfo(AnimationInfo&&) = default;
    AnimationInfo& operator=(AnimationInfo&&) = default;

    std::vector<AnimationFrameInfo>   frames              ;
    bool                              autoRestart         = false;
    std::size_t                       curFrame            = 0; // если >= frames.size() - то анимация дошла до конца и рисуем последний фрейм
    bool                              hasPivots           = false;
    std::uint32_t                     commonFrameTaiming  = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду
    std::uint32_t                     startTick           = 0;
    std::uint32_t                     pauseTick           = 0;
    //int                               pauseCounter        = 0;


    // По хорошему, это надо перенести в контейнер анимаций, а не паузить анимации по отдельности
    // Все равно при смене анимации пауза автоматом сбрасывается
    // Пока оставим так.
    // А может ли быть такое, что нам нужно сменить анимацию во время паузы, и что бы режим паузы остался?
    // Вот если понадобится, тогда и переедем.

    int                               pauseCounter        = 0;

    bool isDone() const
    {
        return curFrame>=frames.size();
    }

    void clearPausedState()
    {
        pauseCounter = 0;
    }

    bool isPaused() const
    {
        return pauseCounter>0;
    }

    // returns true if paused
    bool doPause(std::uint32_t curTickMs, bool bPause)
    {
        bool prevPausedState = isPaused();

        pauseCounter += bPause ? +1 : -1;

        bool curPausedState = isPaused();

        if (prevPausedState!=curPausedState)
        {
            // состояние паузы изменилось
            if (curPausedState)
            {
                // стали в паузу, сохраняем тик
                pauseTick = curTickMs;
            }
            else
            {
                // нужно прибавить к стартовому тику столько, сколько мы висели в паузе, чтобы фаза анимации не перескочила
                std::uint32_t pauseTickDelta = curTickMs - pauseTick;
                startTick += pauseTickDelta;
            }

        }

        return curPausedState;

    }


    bool updatePivotsSummaryCache()
    {
        hasPivots = false;

        for(const auto &fi: frames)
        {
            if (fi.pivotPoint.width!=0 || fi.pivotPoint.height!=0)
            {
                hasPivots = true;
                break;
            }
        }

        return hasPivots;
    }

    // Возвращает true при смене кадра
    bool performStep(std::uint32_t curTickMs, bool *pDone = 0, bool *pRestarted = 0)
    {
        if (isPaused())
            return false;

        if (startTick==0)
        {
            startTick = curTickMs;
        }

        //std::uint32_t tickDelta = curTickMs - startTick;
        int curTickDelta = (int)(curTickMs - startTick);

        //UW_LOG() << "   ---\n";

        //UW_LOG() << "performStep, startTick: " << startTick << ", curTickDelta: " << curTickDelta << ", curFrame: " << curFrame << "\n";

        std::size_t timingFrameIdx = 0;
        for(; timingFrameIdx!=frames.size(); ++timingFrameIdx)
        {
            std::uint32_t curFrameTiming = frames[timingFrameIdx].frameTiming;
            if (curFrameTiming<5)
            {
                curFrameTiming = 5; // не более 200 кадров в секунду
            }

            //UW_LOG() << "curFrameTiming: " << curFrameTiming << "\n";

            int newTickDelta = curTickDelta - (int)curFrameTiming;

            //UW_LOG() << "curFrameTiming: " << curFrameTiming << ", newTickDelta: " << newTickDelta << ", curTickDelta: " << curTickDelta << "\n";

            if (newTickDelta<0)
            {
                //UW_LOG() << "Shown frame #" << timingFrameIdx << ", break" << "\n";
                // нашли текущий отображаемый кадр
                break;
            }

            //UW_LOG() << "Go to checking next frame\n";

            curTickDelta = newTickDelta;
        }

        //UW_LOG() << "* Found active frame: " << timingFrameIdx << "\n";

        if (pRestarted)
        {
            *pRestarted = false;
        }

        if (pDone)
        {
            *pDone = false;
        }

        if (curFrame!=timingFrameIdx)
        {
            //UW_LOG() << "! Frame change\n";

            // произошла смена кадра
            if (timingFrameIdx>=frames.size())
            {
                if (pDone)
                {
                    *pDone = true;
                }

                if (autoRestart)
                {
                    curFrame = 0;
                    if (pRestarted)
                    {
                        *pRestarted = true;
                    }
                }
                // else
                // {
                // }
            }

            curFrame = timingFrameIdx;

            return true; // сигнализируем о смене кадра
        }

        return false;
    }

}; // struct AnimationInfo



class AnimationImpl : public IAnimation
{

protected:

    std::shared_ptr<IAnimationDrawingHandler>        m_pAnimationDrawingHandler;
    std::shared_ptr<IAnimationFrameChangeHandler>    m_pAnimationFrameChangeHandler;
    std::vector<AnimationInfo>                       m_animations;
    std::size_t                                      m_curAnimation                = 0;
    DrawCoord                                        m_drawingPos                  = DrawCoord{0,0};
    DrawCoord                                        m_drawingScale                 = DrawCoord{0,0};
    bool                                             m_targetScaled                = false;
    std::uint32_t                                    m_animationsCommonFrameTiming = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду

    int                                              m_visibilityCounter              = 0;

public:

    AnimationImpl() = default;
    AnimationImpl(const AnimationImpl&) = delete;
    AnimationImpl& operator=(const AnimationImpl&) = delete;
    AnimationImpl(AnimationImpl&&) = delete;
    AnimationImpl& operator=(AnimationImpl&&) = delete;


    virtual bool isVisible() const override
    {
        return m_visibilityCounter>0;
    }

    virtual bool setVisible(bool bVisible) override
    {
        bool prevVisibilityState = isVisible();

        m_visibilityCounter += bVisible ? +1 : -1;

        bool curVisibilityState = isVisible();

        if (prevVisibilityState!=curVisibilityState)
        {
            // состояние паузы изменилось
            if (curVisibilityState)
            {
                // стали в паузу, сохраняем тик
                //pauseTick = curTickMs;
            }
            else
            {
                // нужно прибавить к стартовому тику столько, сколько мы висели в паузе, чтобы фаза анимации не перескочила
                // std::uint32_t pauseTickDelta = curTickMs - pauseTick;
                // startTick += pauseTickDelta;
            }

        }

        return curVisibilityState;
    }

    virtual bool setAnimationDrawingHandler( std::shared_ptr<IAnimationDrawingHandler> pHandler) override
    {
        m_pAnimationDrawingHandler = pHandler;
        return true;
    }

    virtual void clearAnimationDrawingHandler() override
    {
        m_pAnimationDrawingHandler.reset();
    }


    virtual int  size()  const override
    {
        return (int)m_animations.size();
    }

    virtual bool empty() const override
    {
        return m_animations.empty();
    }

    virtual void clear() override // Только список анимаций
    {
        return m_animations.clear();
    }

    virtual std::uint32_t getCurTick() const override
    {
        #if defined(WIN32) || defined(_WIN32)

            return (std::uint32_t)GetTickCount();

        #else

            // тупая заглушка, которая выдаёт новый инкрементируемый тик при каждом вызове
            static std::uint32_t counter = 0;

            std::uint32_t res = counter;
            ++counter;
            return res;

        #endif
    }

    virtual std::uint32_t getCheckedCurTick(std::uint32_t tick) const override
    {
        if (tick==0)
            tick = getCurTick();
        return tick;
    }

    bool checkConvertAniIds(int aniId_, int frameNum_, std::size_t &aniId, std::size_t &frameNum) const
    {
        std::size_t tmp_aniId = (std::size_t)aniId_;
        if (tmp_aniId>=m_animations.size())
            return false;

        std::size_t tmp_frameNum = (std::size_t)frameNum_;

        const AnimationInfo &animationInfo = m_animations[aniId];

        if (tmp_frameNum>=animationInfo.frames.size())
            return false;

        // рисование только в одном месте, а frameNum должен влезать в диапазон во всех остальных местах
        // if (animationInfo.frames.empty())
        //     return false;
        //  
        // if (tmp_frameNum>=animationInfo.frames.size())
        // {
        //     tmp_frameNum = animationInfo.frames.size()-1; // рисуем последний кадр
        // }

        aniId    = tmp_aniId   ;
        frameNum = tmp_frameNum;

        return true;
    }

    bool checkConvertAniIds(int aniId_, std::size_t &aniId) const
    {
        std::size_t tmp_aniId = (std::size_t)aniId_;
        if (tmp_aniId>=m_animations.size())
            return false;

        aniId = tmp_aniId;

        return true;
    }

    virtual int getAnimationNumFrames(int aniId_) const override
    {
        std::size_t aniId    = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return 0;

        return (int)m_animations[aniId].frames.size();
    }

    virtual bool drawAnimationFrame(IDrawContext *pdc, int aniId_, int frameNum_, const DrawCoord &scale=DrawCoord{1,1}) const override // отрисовка конкретной фазы заданной анимации
    {
        if (!isVisible())
            return false;

        if (!pdc)
            return false;

        if (!m_pAnimationDrawingHandler)
            return false;

        std::size_t aniId    = 0;
        std::size_t frameNum = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        const AnimationInfo &animationInfo = m_animations[aniId];
        frameNum = (std::size_t)frameNum_;

        if (animationInfo.frames.empty())
            return false;

        if (frameNum>=animationInfo.frames.size())
        {
            frameNum = animationInfo.frames.size()-1; // рисуем последний кадр
        }

        const AnimationFrameInfo &frameInfo = m_animations[aniId].frames[frameNum];

        /*
            scale используется, если установлено m_targetScaled
            Если установлено m_targetScaled, то используется также и скалинг DrawContext'а

            Но если pivot point задан, то мы не можем просто так смещать базовую точку для отрисовки спрайта, 
            потому что pivot point может быть разный, и без учета масштабирования будет гавно

            Проблема с масштабированием - это то, что оно работает медленнее, чем тупое копирование.
            Другой вопрос, что у нас спрайты с анимацией из PNG, а там альфаканал, а функция AlphaBlend всё равно не быстрая.


        
         */

        bool targetScaled = m_targetScaled;
        //if (frameInfo.pivotPoint.width!=0 || frameInfo.pivotPoint.height!=0)
        if (animationInfo.hasPivots)
        {
            targetScaled = true;
        }

        // Тут пока используется масштабирование отдельного спрайта в процентах
        ImageSize spriteSize = frameInfo.getScaledSize();
        ImageSize pivotPoint = frameInfo.getScaledPivotPoint();

        DrawCoord targetSize  = DrawCoord{spriteSize.width,spriteSize.height};
        DrawCoord targetPivot = DrawCoord{pivotPoint.width,pivotPoint.height};

        if (targetScaled)
        {
            DrawScale dcScale = pdc->getScale();

            // На DC Scale надо тут делить, оно потом обратно отмасштабируется при отрисовке

            //targetSize  /= dcScale;
            targetSize  *= scale  ;

            //targetPivot /= dcScale;
            targetPivot *= scale  ;
        }

        DrawCoord targetPos = m_drawingPos - targetPivot;

        auto ncThis = const_cast<AnimationImpl*>(this);

        return m_pAnimationDrawingHandler->drawAnimationFrame( pdc, static_cast<IAnimation*>(ncThis), frameInfo.pImgList.get(), frameInfo.imgId
                                                             , targetPos, targetSize
                                                             , frameInfo.imgPos, frameInfo.imgSize
                                                             );

        // virtual bool drawAnimationFrame( IDrawContext *pdc, IAnimation* pAnimation, IImageList* pImgList, int imgId
        //                                , const DrawCoord &screenPos, const DrawCoord &screenSize
        //                                , ImageSize imgPartLeftTop, ImageSize imgPartSize
        //                                ) const = 0;

    }

    virtual bool drawAnimationCurrentFrame(IDrawContext *pdc, int aniId_, const DrawCoord &scale=DrawCoord{1,1}) const override // отрисовка текущей фазы заданной анимации
    {
        std::size_t aniId = 0;
        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        return drawAnimationFrame(pdc, aniId_, (int)m_animations[aniId].curFrame, scale);
    }

    virtual bool drawCurrentFrame(IDrawContext *pdc, const DrawCoord &scale=DrawCoord{1,1}) const override // отрисовка текущей фазы текущей анимации
    {
        return drawAnimationCurrentFrame(pdc, (int)m_curAnimation, scale);
    }

    virtual bool setTargetPosition(const DrawCoord &pos ) override // установка положения на экране, left/top
    {
        m_drawingPos = pos;
        return true;
    }

    virtual DrawCoord getTargetPosition() override
    {
        return m_drawingPos;
    }

    virtual bool setTargetScale    (const DrawCoord &scale) override // установка размера на экране
    {
        m_drawingScale = scale;
        return true;
    }

    virtual DrawCoord getTargetScale() const override
    {
        return m_drawingScale;
    }

    virtual bool setTargetScaledOnOff  (bool allowScale) override // влияет ли targetSize на отрисовку, или изображение переносится попиксельно как есть
    {
        m_targetScaled = allowScale;
        return true;
    };

    virtual bool getTargetScaledOnOff() const override
    {
        return m_targetScaled;
    }

    virtual bool setAnimationFrameScalePercent(int aniId_, int frameNum_, int percent) override
    {
        std::size_t aniId    = 0;
        std::size_t frameNum = 0;

        if (!checkConvertAniIds(aniId_, frameNum_, aniId, frameNum))
            return false;

        m_animations[aniId].frames[frameNum].frameScalePercent = percent;

        return true;
    }

    virtual bool setCurrentAnimationEx(std::uint32_t curTickMs, int aniId_, int frameNum_) override
    {
        curTickMs = getCheckedCurTick(curTickMs);

        std::size_t aniId = (std::size_t)aniId_;
        if (aniId>=m_animations.size())
        {
            aniId = 0;
        }

        m_curAnimation = aniId;

        std::size_t frameNum = (std::size_t)frameNum_;
        if (frameNum>=m_animations[aniId].frames.size())
        {
            frameNum = 0;
        }

        m_animations[aniId].curFrame  = frameNum;
        m_animations[aniId].startTick = curTickMs;
        m_animations[aniId].clearPausedState();

        return true;
    }

    virtual bool setCurrentAnimation(std::uint32_t curTickMs, int aniId_) override
    {
        return setCurrentAnimationEx(curTickMs, aniId_, 0);
    }

    virtual bool performCurrentAnimationStep(std::uint32_t curTickMs, bool *pDone=0, bool *pRestarted=0) override
    {
        if (m_curAnimation>=m_animations.size())
            return false;

        curTickMs = getCheckedCurTick(curTickMs);

        bool restarted = false;
        bool done      = false;
        bool res = m_animations[m_curAnimation].performStep(curTickMs, &done, &restarted);

        if (pDone)
        {
            *pDone = done;
        }

        if (pRestarted)
        {
            *pRestarted = restarted;
        }

        //TODO: !!! Надо вызвать какой-то хэндлер, если изменился текущий фрейм
        if (m_pAnimationFrameChangeHandler)
        {
            m_pAnimationFrameChangeHandler->onAnimationFrameChanged(this, curTickMs, (int)m_curAnimation, (int)m_animations[m_curAnimation].curFrame, done, restarted);
        }

        return res;
    }

    virtual bool setAnimationFrameChangeHandler( std::shared_ptr<IAnimationFrameChangeHandler> pHandler) override
    {
        m_pAnimationFrameChangeHandler = pHandler;
        return true;
    }

    virtual void clearAnimationFrameChangeHandler() override
    {
        m_pAnimationFrameChangeHandler.reset();
    }

    virtual bool pauseCurrentAnimation(std::uint32_t curTickMs, bool bPause) override
    {
        if (m_curAnimation>=m_animations.size())
            return false;

        curTickMs = getCheckedCurTick(curTickMs);

        return m_animations[m_curAnimation].doPause(curTickMs, bPause);
    }

    virtual bool isCurrentAnimationPaused() const override
    {
        if (m_curAnimation>=m_animations.size())
            return false;

        return m_animations[m_curAnimation].isPaused();
    }


    virtual bool setAnimationsCommonFrameTiming(std::uint32_t ms) override // Будет действовать на новые анимации
    {
        m_animationsCommonFrameTiming = ms;
        if (m_animationsCommonFrameTiming<5)
        {
            m_animationsCommonFrameTiming = 5;
        }
        return true;
    }

    virtual std::uint32_t getAnimationsCommonFrameTiming() const override
    {
        return m_animationsCommonFrameTiming;
    }

    virtual bool setAnimationFramesTiming(int aniId_, std::uint32_t ms) override // Также переустанавливает все кастомные тайминги в анимации
    {
        std::size_t aniId    = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        if (ms<5)
            ms = 5;

        AnimationInfo &animationInfo = m_animations[aniId];
        animationInfo.commonFrameTaiming = ms;

        for(auto &frame : animationInfo.frames)
        {
            frame.frameTiming = ms;
        }

        return true;
    }

    virtual int  addSimpleAnimation(int numFrames) override
    {
        if (numFrames<0 || numFrames > 8192) // нельзя слишком много фреймов в одной анимации
        {
            return -1;
        }

        int res = -1;
        try
        {
            AnimationInfo animationInfo;
            animationInfo.frames = std::vector<AnimationFrameInfo>((std::size_t)numFrames);
            res = (int)m_animations.size();
            m_animations.emplace_back(animationInfo);
        }
        catch(...)
        {
            return -1;
        }

        return res;
    }

    virtual bool setAnimationFrameTiming(int aniId_, int frameNum_, std::uint32_t ms) override // Задаёт время отображения фрейма (кастомный тайминг фрейма)
    {
        std::size_t aniId    = 0;
        std::size_t frameNum = 0;

        if (!checkConvertAniIds(aniId_, frameNum_, aniId, frameNum))
            return false;

        if (ms<5)
            ms = 5;

        m_animations[aniId].frames[frameNum].frameTiming = ms;

        return true;
    }

    virtual bool setAnimationLooping(int aniId_, bool bLoop) override
    {
        std::size_t aniId    = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        m_animations[m_curAnimation].autoRestart = bLoop;

        return true;
    }

    virtual bool getAnimationLooping(int aniId_) override
    {
        std::size_t aniId    = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        return m_animations[m_curAnimation].autoRestart;
    }


}; // class AnimationImpl





class SpriteAnimationImpl : public AnimationImpl
                          , public ISpriteAnimation
{

protected:

    std::shared_ptr<IImageList> m_pCommonImageList;
    int                         m_commonImageId   = -1;


public:

    SpriteAnimationImpl() = default;
    SpriteAnimationImpl(const SpriteAnimationImpl&) = delete;
    SpriteAnimationImpl& operator=(const SpriteAnimationImpl&) = delete;
    SpriteAnimationImpl(SpriteAnimationImpl&&) = delete;
    SpriteAnimationImpl& operator=(SpriteAnimationImpl&&) = delete;

    virtual bool setSpriteAnimationCommonImage(std::shared_ptr<IImageList> pImgList, int imgId) override
    {
        m_pCommonImageList = pImgList;
        m_commonImageId    = imgId   ;
        return true;
    }


    virtual void clearAll() override // Очищает все списки анимаций, а также CommonImage
    {
        m_pCommonImageList = std::shared_ptr<IImageList>();
        m_commonImageId    = -1;
        AnimationImpl::clear();
    }

    // Создаёт анимацию из вертикальной/горизонтальной ленты заданного изображения

    std::vector<AnimationFrameInfo> makeAnimationFramesHelper(std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int maxNumFrames) const
    {
        std::vector<AnimationFrameInfo> resVec;

        if (!pImageList)
        {
            return resVec;
        }

        ImageListImageInfo imageInfo;
        if (!pImageList->getImageInfo(imgId, &imageInfo))
        {
            return resVec;
        }

        ImageSize curPos  = basePos;
        ImageSize posStep = ImageSize{0,0};
        if (bVertical)
        {
            posStep.height = frameSize.height;
        }
        else
        {
            posStep.width = frameSize.width;
        }

        ImageSize nextPos = curPos + posStep;
        while(nextPos.width<imageInfo.imageSize.width && nextPos.height<imageInfo.imageSize.height)
        {
            if (maxNumFrames>=0) // лимит задан
            {
                if ((std::size_t)maxNumFrames >= resVec.size())
                {
                    break; // лимит на число кадров кончился
                }
            }

            AnimationFrameInfo frame;
            frame.pImgList     = pImageList;
            frame.imgId        = imgId     ;
            frame.imgPos       = curPos;
            frame.imgSize      = frameSize;
            frame.frameTiming  = m_animationsCommonFrameTiming;
            frame.frameScalePercent = 100; // default - no scale

            try
            {
                resVec.emplace_back(frame);
            }
            catch(...)
            {
                return std::vector<AnimationFrameInfo>();
            }

            curPos  += posStep;
            nextPos += posStep;

        }

        return resVec;
    }

    std::vector<AnimationFrameInfo> makeAnimationFramesHelper(std::shared_ptr<IImageList> pImageList, const std::vector<int> &frameList_) const
    {
        std::vector<AnimationFrameInfo> resVec;

        if (!pImageList)
            return resVec;

        std::vector<int> frameList = frameList_;
        if(frameList.empty())
        {
            int imgListSize = pImageList->size();
            frameList.reserve((std::size_t)imgListSize);
            for(int id=0; id<imgListSize; ++id)
            {
                frameList.emplace_back(id);
            }
        }

        for(int imgId : frameList)
        {
            ImageListImageInfo imageInfo;
            if (!pImageList->getImageInfo(imgId, &imageInfo))
                continue;

            AnimationFrameInfo frame;
            frame.pImgList     = pImageList;
            frame.imgId        = imgId     ;
            frame.imgPos       = ImageSize{0,0};
            frame.imgSize      = imageInfo.imageSize;
            frame.frameTiming  = m_animationsCommonFrameTiming;
            frame.frameScalePercent = 100; // default - no scale

            try
            {
                resVec.emplace_back(frame);
            }
            catch(...)
            {
                return std::vector<AnimationFrameInfo>();
            }

        }

        return resVec;

    }

    AnimationInfo fillAnimationInfo() const
    {
        AnimationInfo newAnimationInfo;
        newAnimationInfo.autoRestart        = false;
        newAnimationInfo.curFrame           = 0;
        newAnimationInfo.hasPivots          = false;
        newAnimationInfo.commonFrameTaiming = m_animationsCommonFrameTiming;
        newAnimationInfo.startTick          = 0;
        newAnimationInfo.pauseTick          = 0;
        newAnimationInfo.pauseCounter       = 0;

        return newAnimationInfo;
    }


    // Простая версия сама высчитывает количество кадров по размеру картинки
    virtual int addSpriteAnimationCustomImageList  (std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) override
    {
        AnimationInfo newAnimationInfo = fillAnimationInfo();
        newAnimationInfo.frames = makeAnimationFramesHelper(pImageList, imgId, basePos, frameSize, bVertical, -1 /* maxNumFrames */ );
        if (newAnimationInfo.frames.empty())
            return -1;

        int res = (int)m_animations.size();

        try
        {
            m_animations.emplace_back(newAnimationInfo);
        }
        catch(...)
        {
            return -1;
        }

        return res;
    }

    // Расширенная версия использует указанное число кадров, но не более, чем есть в изображении
    virtual int addSpriteAnimationCustomImageListEx(std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int maxNumFrames) override
    {
        AnimationInfo newAnimationInfo = fillAnimationInfo();
        newAnimationInfo.frames        = makeAnimationFramesHelper(pImageList, imgId, basePos, frameSize, bVertical, maxNumFrames );
        if (newAnimationInfo.frames.empty())
            return -1;

        int res = (int)m_animations.size();

        try
        {
            m_animations.emplace_back(newAnimationInfo);
        }
        catch(...)
        {
            return -1;
        }

        return res;
    }

    virtual int appendSpriteAnimationCustomImageList  (int aniId_, std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) override
    {
        std::size_t aniId = 0;
        if (!checkConvertAniIds(aniId_, aniId))
            return -1;

        AnimationInfo &animationInfo = m_animations[aniId];
        auto frames = makeAnimationFramesHelper(pImageList, imgId, basePos, frameSize, bVertical, -1 /* maxNumFrames */ );
        if (frames.empty())
            return -1;

        try
        {
            animationInfo.frames.insert(animationInfo.frames.end(), frames.begin(), frames.end());
        }
        catch(...)
        {
            return -1;
        }

        return aniId_;
    
    }

    virtual int appendSpriteAnimationCustomImageListEx(int aniId_, std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int maxNumFrames) override
    {
        std::size_t aniId = 0;
        if (!checkConvertAniIds(aniId_, aniId))
            return -1;

        AnimationInfo &animationInfo = m_animations[aniId];
        auto frames = makeAnimationFramesHelper(pImageList, imgId, basePos, frameSize, bVertical, maxNumFrames );
        if (frames.empty())
            return -1;

        try
        {
            animationInfo.frames.insert(animationInfo.frames.end(), frames.begin(), frames.end());
        }
        catch(...)
        {
            return -1;
        }

        return aniId_;
    }


    virtual int addSpriteAnimation  (const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) override
    {
        return addSpriteAnimationCustomImageList(m_pCommonImageList, m_commonImageId, basePos, frameSize, bVertical);
    }

    virtual int addSpriteAnimationEx(const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) override
    {
        return addSpriteAnimationCustomImageListEx(m_pCommonImageList, m_commonImageId, basePos, frameSize, bVertical, numFrames);
    }

    virtual int appendSpriteAnimation  (int aniId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) override
    {
        return appendSpriteAnimationCustomImageList(aniId, m_pCommonImageList, m_commonImageId, basePos, frameSize, bVertical);
    }

    virtual int appendSpriteAnimationEx(int aniId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) override
    {
        return appendSpriteAnimationCustomImageListEx(aniId, m_pCommonImageList, m_commonImageId, basePos, frameSize, bVertical, numFrames);
    }


    virtual int addSpriteAnimationCustomImageListFramesList(std::shared_ptr<IImageList> pImageList, const std::vector<int> &frameList) override
    {
        AnimationInfo newAnimationInfo = fillAnimationInfo();
        newAnimationInfo.frames = makeAnimationFramesHelper(pImageList, frameList);

        if (newAnimationInfo.frames.empty())
        {
            return -1;
        }

        int res = (int)m_animations.size();

        try
        {
            m_animations.emplace_back(newAnimationInfo);
        }
        catch(...)
        {
            return -1;
        }

        return res;
    }

    virtual int addSpriteAnimationCustomImageListFramesRange(std::shared_ptr<IImageList> pImageList, int firstFrameIdx, int numFrames) override
    {
        std::vector<int> frameList; frameList.reserve((std::size_t)numFrames);
        for(int idx=0; idx<numFrames; ++idx)
        {
            frameList.emplace_back(firstFrameIdx+idx);
        }

        return addSpriteAnimationCustomImageListFramesList(pImageList, frameList);
    }

    virtual int addSpriteAnimationCustomImageListFramesAll(std::shared_ptr<IImageList> pImageList) override
    {
        return addSpriteAnimationCustomImageListFramesList(pImageList, std::vector<int>());
    }

    virtual int appendSpriteAnimationCustomImageListFramesList (int aniId_, std::shared_ptr<IImageList> pImageList, const std::vector<int> &frameList) override
    {
        std::size_t aniId = 0;
        if (!checkConvertAniIds(aniId_, aniId))
            return -1;

        AnimationInfo &animationInfo = m_animations[aniId];
        auto frames = makeAnimationFramesHelper(pImageList, frameList);
        if (frames.empty())
            return -1;

        try
        {
            animationInfo.frames.insert(animationInfo.frames.end(), frames.begin(), frames.end());
        }
        catch(...)
        {
            return -1;
        }

        return aniId_;
    }

    virtual int appendSpriteAnimationCustomImageListFramesRange(int aniId, std::shared_ptr<IImageList> pImageList, int firstFrameIdx, int numFrames) override
    {
        std::vector<int> frameList; frameList.reserve((std::size_t)numFrames);
        for(int idx=0; idx<numFrames; ++idx)
        {
            frameList.emplace_back(firstFrameIdx+idx);
        }

        return appendSpriteAnimationCustomImageListFramesList(aniId, pImageList, frameList);
    }

    virtual int appendSpriteAnimationCustomImageListFramesAll  (int aniId, std::shared_ptr<IImageList> pImageList) override
    {
        return appendSpriteAnimationCustomImageListFramesList(aniId, pImageList, std::vector<int>());
    }


    virtual bool setSpriteAnimationFrameImage(int aniId_, int frameId_, std::shared_ptr<IImageList> pImgList, int imgId) override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return false;

        if (aniId>=m_animations.size())
            return false;

        AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return false;

        AnimationFrameInfo &fi = ani.frames[frameId];

        fi.pImgList = pImgList;
        fi.imgId    = imgId   ;

        return true;
    }


    virtual std::shared_ptr<IImageList> getSpriteAnimationFrameImageList(int aniId_, int frameId_) const override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return std::shared_ptr<IImageList>();

        if (aniId>=m_animations.size())
            return std::shared_ptr<IImageList>();

        const AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return std::shared_ptr<IImageList>();

        const AnimationFrameInfo &fi = ani.frames[frameId];

        return fi.pImgList;
    }

    virtual int               getSpriteAnimationFrameImageIndex(int aniId_, int frameId_) const override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return -1;

        if (aniId>=m_animations.size())
            return -1;

        const AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return -1;

        const AnimationFrameInfo &fi = ani.frames[frameId];

        return fi.imgId;
    }

    virtual ImageSize         getSpriteAnimationFrameImagePos  (int aniId_, int frameId_) const override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return ImageSize{0,0};

        if (aniId>=m_animations.size())
            return ImageSize{0,0};

        const AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return ImageSize{0,0};

        const AnimationFrameInfo &fi = ani.frames[frameId];

        return fi.imgPos;
    }

    virtual ImageSize         getSpriteAnimationFrameImageSize (int aniId_, int frameId_) const override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return ImageSize{0,0};

        if (aniId>=m_animations.size())
            return ImageSize{0,0};

        const AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return ImageSize{0,0};

        const AnimationFrameInfo &fi = ani.frames[frameId];

        return fi.imgSize;
    }

    virtual ImageSize                   getSpriteAnimationFramePivotPoint(int aniId_, int frameId_) const override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return ImageSize{0,0};

        if (aniId>=m_animations.size())
            return ImageSize{0,0};

        const AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return ImageSize{0,0};

        const AnimationFrameInfo &fi = ani.frames[frameId];

        return fi.pivotPoint;
    }

    virtual bool setSpriteAnimationFramePivotPoint(int aniId_, int frameId_, ImageSize pivotPoint) override
    {
        std::size_t aniId   = 0;
        std::size_t frameId = 0;

        if (!checkConvertAniIds(aniId_, frameId_, aniId, frameId))
            return false;

        if (aniId>=m_animations.size())
            return false;

        AnimationInfo &ani = m_animations[aniId];

        if (frameId>=ani.frames.size())
            return false;

        AnimationFrameInfo &fi = ani.frames[frameId];

        if (pivotPoint.width>=fi.imgSize.width || pivotPoint.height>=fi.imgSize.height)
            return false;

        fi.pivotPoint = pivotPoint;

        ani.updatePivotsSummaryCache();

        return true;
    }

    virtual bool setSpriteAnimationPivotPoint(int aniId_, ImageSize pivotPoint) override
    {
        std::size_t aniId   = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        AnimationInfo &ani = m_animations[aniId];

        for(auto &fi : ani.frames)
        {
            fi.pivotPoint = pivotPoint;
        }

        ani.updatePivotsSummaryCache();

        return true;
    }

    virtual bool setSpriteAnimationPivotPointToCenter(int aniId_, bool bVerticalCenter) override
    {
        std::size_t aniId   = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        AnimationInfo &ani = m_animations[aniId];

        for(auto &fi : ani.frames)
        {
            if (bVerticalCenter)
            {
                fi.pivotPoint.height = fi.imgSize.height/2;
            }
            else
            {
                fi.pivotPoint.width = fi.imgSize.width/2;
            }
        }

        ani.updatePivotsSummaryCache();

        return true;
    }

    virtual bool setSpriteAnimationPivotPointCoord(int aniId_, bool bVerticalCoord, int coordValue) override
    {
        std::size_t aniId   = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        AnimationInfo &ani = m_animations[aniId];

        for(auto &fi : ani.frames)
        {
            if (bVerticalCoord)
            {
                fi.pivotPoint.height = coordValue;
            }
            else
            {
                fi.pivotPoint.width = coordValue;
            }
        }

        ani.updatePivotsSummaryCache();

        return true;
    }




    //------------------------------
    virtual int  size()  const override                                                          { return AnimationImpl::size(); }
    virtual bool empty() const override                                                          { return AnimationImpl::empty(); }

    virtual void clear() override                                                                { return AnimationImpl::clear(); }

    virtual std::uint32_t getCurTick() const                                                     { return AnimationImpl::getCurTick(); }
    virtual std::uint32_t getCheckedCurTick(std::uint32_t tick) const                            { return AnimationImpl::getCheckedCurTick(tick); }

    virtual bool setVisible(bool bVisible) override                                              { return AnimationImpl::setVisible(bVisible); }
    virtual bool isVisible() const override                                                      { return AnimationImpl::isVisible(); }

    virtual int getAnimationNumFrames(int aniId) const override                                  { return AnimationImpl::getAnimationNumFrames(aniId); }

    virtual bool drawAnimationFrame(IDrawContext *pdc, int aniId, int frameNum, const DrawCoord &scale=DrawCoord{1,1}) const override   { return AnimationImpl::drawAnimationFrame(pdc, aniId, frameNum, scale); }
    virtual bool drawAnimationCurrentFrame(IDrawContext *pdc, int aniId, const DrawCoord &scale=DrawCoord{1,1}) const override          { return AnimationImpl::drawAnimationCurrentFrame(pdc, aniId, scale); }
    virtual bool drawCurrentFrame(IDrawContext *pdc, const DrawCoord &scale=DrawCoord{1,1}) const override                              { return AnimationImpl::drawCurrentFrame(pdc, scale); }

    virtual bool setTargetPosition(const DrawCoord &pos ) override                               { return AnimationImpl::setTargetPosition(pos); }
    virtual DrawCoord getTargetPosition() override                                               { return AnimationImpl::getTargetPosition(); }
    virtual bool setTargetScale    (const DrawCoord &scale) override                             { return AnimationImpl::setTargetScale(scale); }
    virtual DrawCoord getTargetScale() const override                                            { return AnimationImpl::getTargetScale(); }
    virtual bool setTargetScaledOnOff(bool allowScale) override                                  { return AnimationImpl::setTargetScaledOnOff(allowScale); }
    virtual bool getTargetScaledOnOff() const override                                           { return AnimationImpl::getTargetScaledOnOff(); }

    virtual bool setAnimationFrameScalePercent(int aniId, int frameNum, int precent) override    { return AnimationImpl::setAnimationFrameScalePercent(aniId, frameNum, precent); }
    
    virtual bool setAnimationDrawingHandler( std::shared_ptr<IAnimationDrawingHandler> pHandler) override { return AnimationImpl::setAnimationDrawingHandler(pHandler); }
    virtual void clearAnimationDrawingHandler() override                                         { return AnimationImpl::clearAnimationDrawingHandler(); }

    virtual bool setAnimationFrameChangeHandler( std::shared_ptr<IAnimationFrameChangeHandler> pHandler) override { return AnimationImpl::setAnimationFrameChangeHandler(pHandler); }
    virtual void clearAnimationFrameChangeHandler() override                                     { return AnimationImpl::clearAnimationFrameChangeHandler(); }

    virtual bool setCurrentAnimationEx(std::uint32_t curTickMs, int aniId, int frameId) override { return AnimationImpl::setCurrentAnimationEx(curTickMs, aniId, frameId); }
    virtual bool setCurrentAnimation(std::uint32_t curTickMs, int aniId) override                { return AnimationImpl::setCurrentAnimation(curTickMs, aniId); }

    virtual bool performCurrentAnimationStep(std::uint32_t curTickMs, bool *pDone=0, bool *pRestarted=0) override { return AnimationImpl::performCurrentAnimationStep(curTickMs, pDone, pRestarted); }
    virtual bool pauseCurrentAnimation(std::uint32_t curTickMs, bool bPause) override            { return AnimationImpl::pauseCurrentAnimation(curTickMs, bPause); }
    virtual bool isCurrentAnimationPaused() const override                                       { return AnimationImpl::isCurrentAnimationPaused(); }

    virtual bool setAnimationsCommonFrameTiming(std::uint32_t ms) override                       { return AnimationImpl::setAnimationsCommonFrameTiming(ms); }
    virtual std::uint32_t getAnimationsCommonFrameTiming() const override                        { return AnimationImpl::getAnimationsCommonFrameTiming(); }
    virtual bool setAnimationFramesTiming(int aniId, std::uint32_t ms) override                  { return AnimationImpl::setAnimationFramesTiming(aniId, ms); }
    virtual int  addSimpleAnimation(int numFrames) override                                      { return AnimationImpl::addSimpleAnimation(numFrames); }
    virtual bool setAnimationFrameTiming(int aniId, int frameId, std::uint32_t ms) override      { return AnimationImpl::setAnimationFrameTiming(aniId, frameId, ms); }

    virtual bool setAnimationLooping(int aniId, bool bLoop) override                             { return AnimationImpl::setAnimationLooping(aniId, bLoop); }
    virtual bool getAnimationLooping(int aniId) override                                         { return AnimationImpl::getAnimationLooping(aniId); }


}; // class SpriteAnimationImpl


    // std::shared_ptr<IAnimationDrawingHandler> m_pAnimationDrawingHandler;
    // std::vector<AnimationInfo>                m_animations;
    // std::size_t                               m_curAnimation = 0;
    // DrawCoord                                 m_drawingPos   = DrawCoord{0,0};
    // DrawCoord                                 m_drawingScale  = DrawCoord{0,0};
    // bool                                      m_targetScaled = false;
    // std::uint32_t                             m_animationsCommonTiming = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду

// struct AnimationFrameInfo
// {
//     std::shared_ptr<IImageList>  pImgList    ;
//     int                          imgId       ;
//     ImageSize                    imgPos      ; // положение спрайта в картинке
//     ImageSize                    imgSize     ; // размер спрайта в картинке
//     std::uint32_t                frameTiming = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду
//     DrawCoord::value_type        frameScale  = 1;
//  
// }; // struct AnimationFrameInfo
//  
//  
// struct AnimationInfo
// {
//     std::vector<AnimationFrameInfo>   frames              ;
//     bool                              autoRestart         = false;
//     std::size_t                       curFrame            = 0; // если >= frames.size() - то анимация дошла до конца и рисуем последний фрейм
//     std::uint32_t                     commonFrameTaiming  = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду
//     std::uint32_t                     startTick           = 0;
//     std::uint32_t                     pauseTick           = 0;
//     //int                               pauseCounter        = 0;
//     std::atomic<int>                  pauseCounter        = 0;  // Нафига я стал тут возится с атомиком? Всё равно, по идее, если и будет многопоточность какая-то, то анимации все целиком, или, как минимум, каждая целиком, будут защищаться








} // namespace marty_draw_context
