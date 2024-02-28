#pragma once


#include "i_animation.h"

//
#include <atomic>



namespace marty_draw_context {


struct AnimationFrameInfo
{
    std::shared_ptr<IImageList>  pImgList    ;
    int                          imgId       ;
    ImageSize                    imgPos      ; // положение спрайта в картинке
    ImageSize                    imgSize     ; // размер спрайта в картинке
    std::uint32_t                frameTiming = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду
    DrawCoord::value_type        frameScale  = 1;

}; // struct AnimationFrameInfo


struct AnimationInfo
{
    std::vector<AnimationFrameInfo>   frames              ;
    bool                              autoRestart         = false;
    std::size_t                       curFrame            = 0; // если >= frames.size() - то анимация дошла до конца и рисуем последний фрейм
    std::uint32_t                     commonFrameTaiming  = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду
    std::uint32_t                     startTick           = 0;
    std::uint32_t                     pauseTick           = 0;
    //int                               pauseCounter        = 0;
    std::atomic<int>                  pauseCounter        = 0;  // Нафига я стал тут возится с атомиком? Всё равно, по идее, если и будет многопоточность какая-то, то анимации все целиком, или, как минимум, каждая целиком, будут защищаться


    void clearPausedState()
    {
        pauseCounter.store(0);
    }

    bool isPaused() const
    {
        int pcVal = pauseCounter.load();
        return pcVal>0;
    }

    // returns true if paused
    bool doPause(std::uint32_t curTickMs, bool bPause)
    {
        bool prevPausedState = isPaused();
        if (bPause)
        {
            pauseCounter.fetch_add(1 /* , std::memory_order_acquire */ );
        }
        else
        {
            pauseCounter.fetch_sub(1 /* , std::memory_order_acquire */ );
        }

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


    // Возвращает true при смене кадра
    bool performStep(std::uint32_t curTickMs, bool *pRestarted = 0)
    {
        if (isPaused())
            return false;

        //std::uint32_t tickDelta = curTickMs - startTick;
        int curTickDelta = (int)(curTickMs - startTick);

        std::size_t timingFrameIdx = 0;
        for(; timingFrameIdx!=timingFrameIdx.size(); ++timingFrameIdx)
        {
            std::uint32_t curFrameTiming = frames[timingFrameIdx].frameTiming;
            if (curFrameTiming<5)
            {
                curFrameTiming = 5; // не более 200 кадров в секунду
            }

            int newTickDelta = curTickDelta - (int)curFrameTiming;
            if (newTickDelta<0)
            {
                // мы находимся в процессе демонстрации текущего кадра
                break;
            }

            curTickDelta = newTickDelta;
        }

        if (pRestarted)
        {
            *pRestarted = false;
        }

        if (curFrame!=timingFrameIdx)
        {
            // произошла смена кадра
            if (timingFrameIdx>=frames.size())
            {
                if (autoRestart)
                {
                    curFrame = 0;
                    if (pRestarted)
                    {
                        *pRestarted = true;
                    }
                }
                else
                {
                    curFrame = timingFrameIdx;
                }
            }

            return true; // сигнализируем о смене кадра
        }

        return false;
    }

}; // struct AnimationInfo



class AnimationImpl : public IAnimation
{

protected:

    std::shared_ptr<IAnimationDrawingHandler> m_pAnimationDrawingHandler;
    std::vector<AnimationInfo>                m_animations;
    std::size_t                               m_curAnimation                = 0;
    DrawCoord                                 m_drawingPos                  = DrawCoord{0,0};
    DrawCoord                                 m_drawingSize                 = DrawCoord{0,0};
    bool                                      m_targetScaled                = false;
    std::uint32_t                             m_animationsCommonFrameTiming = 1000/20; // базовый тайминг для фреймов - 50мс/20 кадров в секунду


public:

    virtual bool setAnimationDrawingHandler( std::shared_ptr<IAnimationDrawingHandler> pHandler) const override
    {
        m_pAnimationDrawingHandler = pHandler;
        return true;
    }

    virtual void clearAnimationDrawingHandler() override
    {
        m_pAnimationDrawingHandler.reset(0);
    }


    virtual int  size()  const override
    {
        return (int)animations.size();
    }

    virtual bool empty() const override
    {
        return animations.empty();
    }

    virtual void clear() override // Только список анимаций
    {
        return animations.clear();
    }

    bool checkConvertAniIds(int aniId_, int frameNum_, std::size_t &aniId, std::size_t &frameNum) const
    {
        std::size_t tmp_aniId = (std::size_t)aniId_;
        if (tmp_aniId>=m_animations.size())
            return false;

        aniId = tmp_aniId;

        std::size_t tmp_frameNum = (std::size_t)frameNum_;

        const AnimationInfo &animationInfo = m_animations[aniId];

        if (animationInfo.frames.empty())
            return false;

        if (tmp_frameNum>=animationInfo.frames.size())
        {
            tmp_frameNum = animationInfo.frames.size()-1; // рисуем последний кадр
        }

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

    virtual bool drawAnimationFrame(IDrawContext *pdc, int aniId_, int frameNum_) const override // отрисовка конкретной фазы заданной анимации
    {
        if (!pdc)
            return false;

        if (!m_pAnimationDrawingHandler)
            return false;

        std::size_t aniId    = 0;
        std::size_t frameNum = 0;

        if (!checkConvertAniIds(aniId_, frameNum_, aniId, frameNum))
            return false;

        const AnimationFrameInfo &frameInfo = m_animations[aniId].frames[frameNum];

        if (!m_targetScaled)
        {
            return m_pAnimationDrawingHandler->drawFrame(pdc, static_cast<const IAnimation*>(this), m_drawingPos, m_drawingSize, m_targetScaled, (int)aniId, (int)frameNum);
        }
        else
        {
            DrawCoord::value_type frameScale = frameInfo.frameScale;
            DrawCoord drawingSize        = m_drawingSize*DrawCoord{frameScale,frameScale};
            DrawCoord drawingSizeDelta   = drawingSize - m_drawingSize; // допустим, было увеличение, значит, позицию надо уменьшать
            DrawCoord drawingSizeDelta2  = drawingSizeDelta / DrawCoord{2,2};
            DrawCoord drawingPos         = m_drawingPos - drawingSizeDelta2;

            return m_pAnimationDrawingHandler->drawFrame(pdc, static_cast<const IAnimation*>(this), drawingPos, drawingSize, m_targetScaled, (int)aniId, (int)frameNum);
        }
    }

    virtual bool drawAnimationCurrentFrame(IDrawContext *pdc, int aniId_) const override // отрисовка текущей фазы заданной анимации
    {
        std::size_t aniId = 0;
        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        return drawAnimationFrame(pdc, aniId_, (int)m_animations[aniId].curFrame);
    }

    virtual bool drawCurrentFrame(IDrawContext *pdc) const override // отрисовка текущей фазы текущей анимации
    {
        return drawAnimationCurrentFrame(pdc, (int)m_curAnimation);
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

    virtual bool setTargetSize    (const DrawCoord &size) override // установка размера на экране
    {
        m_drawingSize = size;
        return true;
    }

    virtual DrawCoord getTargetSize() override
    {
        return m_drawingSize;
    }

    virtual bool setTargetScaled  (bool allowScale) override // влияет ли targetSize на отрисовку, или изображение переносится попиксельно как есть
    {
        m_targetScaled = allowScale;
        return true;
    };

    virtual bool getTargetScaled() override
    {
        return m_targetScaled;
    }

    virtual bool setAnimationFrameScale(int aniId_, int frameNum_, DrawCoord::value_type scale) override
    {
        std::size_t aniId    = 0;
        std::size_t frameNum = 0;

        if (!checkConvertAniIds(aniId_, frameNum_, aniId, frameNum))
            return false;

        m_animations[aniId].frames[frameNum].frameScale = scale;

        return true;
    }

    virtual bool setCurrentAnimationEx(std::uint32_t curTickMs, int aniId_, int frameId_) override
    {
        std::size_t aniId    = 0;
        std::size_t frameNum = 0;

        if (!checkConvertAniIds(aniId_, frameNum_, aniId, frameNum))
            return false;

        m_curAnimation = aniId;
        m_animations[aniId].frames[frameNum].curFrame = frameNum;
        m_animations[aniId].startTick = curTickMs;
        m_animations[aniId].clearPausedState();

        return true;
    }

    virtual bool setCurrentAnimation(std::uint32_t curTickMs, int aniId) override
    {
        std::size_t aniId    = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        m_curAnimation = aniId;
        m_animations[aniId].frames[frameNum].curFrame = 0;
        m_animations[aniId].startTick = curTickMs;
        m_animations[aniId].clearPausedState();

        return true;
    }

    virtual bool performCurrentAnimationStep(std::uint32_t curTickMs, bool *pRestarted) override
    {
        if (m_curAnimation>=m_animations.size())
            return false;

        bool restarted = false;
        bool res = m_animations[m_curAnimation].performStep(curTickMs, &restarted);

        if (pRestarted)
        {
            *pRestarted = restarted;
        }

        //TODO: !!! Надо вызвать какой-то хэндлер, если изменился текущий фрейм

        return res;
    }

    virtual bool pauseCurrentAnimation(std::uint32_t curTickMs, bool bPause) override
    {
        if (m_curAnimation>=m_animations.size())
            return false;

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

    virtual bool setAnimationFrameTiming(int aniId_, int frameId_, std::uint32_t ms) override // Задаёт время отображения фрейма (кастомный тайминг фрейма)
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

    virtual bool getAnimationLooping(int aniId) override
    {
        std::size_t aniId    = 0;

        if (!checkConvertAniIds(aniId_, aniId))
            return false;

        return m_animations[m_curAnimation].autoRestart;
    }


}; // class AnimationImpl





    // std::shared_ptr<IAnimationDrawingHandler> m_pAnimationDrawingHandler;
    // std::vector<AnimationInfo>                m_animations;
    // std::size_t                               m_curAnimation = 0;
    // DrawCoord                                 m_drawingPos   = DrawCoord{0,0};
    // DrawCoord                                 m_drawingSize  = DrawCoord{0,0};
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
