#pragma once

#include "i_draw_context.h"
#include "i_image_list.h"

//
#include <memory>

/*
    Краткое описание.

    У нас есть IDrawContext. У нас есть IImageList, IDrawContext умеет отрисовывать его
    элементы и части элементов, бит блитом, стреч блитом, и альфаблендом (тут масштабирование 
    искаропки).

    Само собой, реализации IDrawContext и IImageList должны быть совместимыми - т.е. если 
    будет потом движок под кути, то они должны быть QtDrawContextImpl/QtImageListImpl, из 
    указателя на интерфейс указатель на реализацию получается dynamic_cast'ом.
    И, хотя под виндой можно будет создать QtDrawContextImpl и Win32ImageListImpl - 
    они не будут работать вместе. Для этого у IDrawContext есть методы 
    createImageList/createSharedImageList, хотя есть и free standing аналогичные функции.

    Идея анимации хранить в каждом кадре IImageList, и индекс изображения в нём, размеры 
    спрайта и позицию спрайта в изображении. Таким образом, мы можем делать анимацию как 
    из частей одного изображения, так и из отдельных изображений.

    Первый вариант - хранить все кадры в одном большом изображении - лучше, так как каждое 
    изображение (в текущей реализации для Win32) хранится в HBITMAP, что есть GDI ресурс, 
    которых на процесс может быть не более 10К.

    Второй вариант (и идея хранить pImageList и imgId в каждом кадре) - родился чуть позже, 
    как костыль для отображения GIF. Покадрово GIF замечательно загружается в ImageList, и 
    корректно отображается, а вот из отдельных кадров HBITMAP компонуется не очень.
    Это относится ко всем изображениям из любых форматов, проблема в компоновке. Отображается,
    но как-то не так. Искать проблему было лень, было решено расширить функционал IAnimation'а.

    Далее, у каждого кадра можно задать тайминг и pivot point. По умолчанию они устанавливаются 
    дефолтные, потом можно переназначить всей анимации, или отдельным кадрам.

    Каждый объект IAnimation (вернее ISpriteAnimation) хранит набор анимаций отдельного персонажа,
    обычно они все на одном полотне. Такие полотна для всех персонажей могут храниться как в одном 
    ImageList, так и в разных.

    Можно, конечно, хранить анимации всех персонажей в одном объекте анимации, это дело хозяйское.

    По таймеру для всех анимаций вызывается performCurrentAnimationStep. Если кадр сменился, вызывается
    спец обработчик, в котором можно сменить анимацию/кадр. Если анимация сменила кадр, возвражается 
    true, что означает необходимость перерисовки сцены.

    При перерисовке сцены надо для всех анимаций drawCurrentFrame с нужным DC для отрисовки.

    В целом всё.

    Да, Есть IAnimation, есть ISpriteAnimation.
    Класс ISpriteAnimation наследует IAnimation, и добавляет методы для создания анимаций по картинкам.
    IAnimation предоставляет больее общие методы, и предназначен для анимации тех вещей, которые
    отрисовываются векторно, например, анимация трансформации вида UI-контрола.

    Текущая реализация IDrawContext и IImageList для Win32 поддерживает WinXP SP3, работает через GDI/GDI+
    и должна работать в тч и в терминальной сессии, так что на платформе можно делать и какие-то 
    общесистемные программы.

    IImageList поддерживает загрузку .ico и .bmp - своя реализация разбора формата,
    .png/.jpg/.gif и пр - через WIC.

    IAnimation и ISpriteAnimation реализованы уже поверх IDrawContext и IImageList и являются отвязанными
    от платформы.


    //------------------------------

    Заметки по белке.

    Когда вызывать анимирование анимаций в белке?

    Наверное, хорошим вариантом будет вызывать анимирование анимаций
    после того, как вызван onUpdate, по результатам onUpdate будет (или нет) перерисована общая сцена,
    и поверх неё надо нарисовать текущие кадры анимации.

    Т.е. делаем всё это добро по таймеру, вызываем onUpdate, процессим результат и если надо, делаем
    вызываем перерисовку сцены, и потом вызываем onAnimationAnimate для отрисовки всех анимаций в текущих их фазах.

    Как-то так.


 */

namespace marty_draw_context {


struct IAnimation;

struct IAnimationDrawingHandler
{
    virtual ~IAnimationDrawingHandler() {};
    virtual bool drawAnimationFrame( IDrawContext *pdc, IAnimation* pAnimation, IImageList* pImgList, int imgId
                                   , const DrawCoord &screenPos, const DrawCoord &screenSize
                                   , ImageSize imgPartLeftTop, ImageSize imgPartSize
                                   ) const = 0;

    // Почти напрямую можно вызывать
    // bool IDrawContext::drawImageScaled( std::shared_ptr<IImageList> pImgList, int idx, const DrawCoord &pos, const DrawCoord &imgScreenSize, ImageSize imgPartLeftTop, ImageSize imgPartSize) = 0;

}; // struct IAnimationDrawingHandler


struct IAnimationFrameChangeHandler
{
    virtual ~IAnimationFrameChangeHandler() {}
    virtual void onAnimationFrameChanged(IAnimation* pAnimation, std::uint32_t curTickMs, int aniId, int newFrameId, bool bDone, bool bRestarted) = 0; // при bDone bRestarted может быть true/false, иначе игнор

}; // struct IAnimationFrameChangeHandler


struct IAnimation
{
    virtual ~IAnimation() {}

    virtual int  size()  const = 0;
    virtual bool empty() const = 0;

    virtual void clear() = 0; // Только список анимаций

    virtual std::uint32_t getCurTick() const = 0;
    virtual std::uint32_t getCheckedCurTick(std::uint32_t tick) const = 0;

    // Невидимые анимации не будут рисоваться. С большой долей вероятности такая фича будет востребована, и, чтобы не хранить её отдельно, запилим сразу тут
    virtual bool setVisible(bool bVisible) = 0;
    virtual bool isVisible() const = 0;

    virtual int getAnimationNumFrames(int aniId) const = 0;

    virtual bool drawAnimationFrame       (IDrawContext *pdc, int aniId, int frameNum, const DrawCoord &scale=DrawCoord{1,1}) const = 0; // отрисовка конкретной фазы заданной анимации
    virtual bool drawAnimationCurrentFrame(IDrawContext *pdc, int aniId, const DrawCoord &scale=DrawCoord{1,1}) const = 0; // отрисовка текущей фазы заданной анимации
    virtual bool drawCurrentFrame         (IDrawContext *pdc, const DrawCoord &scale=DrawCoord{1,1}) const = 0; // отрисовка текущей фазы текущей анимации

    virtual bool setTargetPosition(const DrawCoord &pos ) = 0; // установка положения на экране, left/top
    virtual DrawCoord getTargetPosition() = 0;
    virtual bool setTargetScale    (const DrawCoord &scale) = 0; // установка размера на экране
    virtual DrawCoord getTargetScale() const = 0;
    virtual bool setTargetScaledOnOff(bool allowScale) = 0; // влияет ли targetSize на отрисовку, или изображение переносится попиксельно как есть
    virtual bool getTargetScaledOnOff() const = 0;

    virtual bool setAnimationFrameScalePercent(int aniId, int frameNum, int precent) = 0;
    
    virtual bool setAnimationDrawingHandler( std::shared_ptr<IAnimationDrawingHandler> pHandler) = 0;
    virtual void clearAnimationDrawingHandler() = 0;

    virtual bool setAnimationFrameChangeHandler( std::shared_ptr<IAnimationFrameChangeHandler> pHandler) = 0;
    virtual void clearAnimationFrameChangeHandler() = 0;

    virtual bool setCurrentAnimationEx(std::uint32_t curTickMs, int aniId, int frameId) = 0;
    virtual bool setCurrentAnimation(std::uint32_t curTickMs, int aniId) = 0;

    // Возвращает true, если кадр пересчелкнулся
    virtual bool performCurrentAnimationStep(std::uint32_t curTickMs, bool *pDone=0, bool *pRestarted=0) = 0;
    virtual bool pauseCurrentAnimation(std::uint32_t curTickMs, bool bPause) = 0; // returns true if paused
    virtual bool isCurrentAnimationPaused() const = 0;

    virtual bool setAnimationsCommonFrameTiming(std::uint32_t ms) = 0; // Будет действовать на новые анимации
    virtual std::uint32_t getAnimationsCommonFrameTiming() const = 0;
    virtual bool setAnimationFramesTiming(int aniId, std::uint32_t ms) = 0; // Также переустанавливает все кастомные тайминги в анимации
    virtual int  addSimpleAnimation(int numFrames) = 0;
    virtual bool setAnimationFrameTiming(int aniId, int frameId, std::uint32_t ms) = 0; // Задаёт время отображения фрейма (кастомный тайминг фрейма)

    virtual bool setAnimationLooping(int aniId, bool bLoop) = 0;
    virtual bool getAnimationLooping(int aniId) = 0;

}; // struct IAnimation

//----------------------------------------------------------------------------





//----------------------------------------------------------------------------
struct ISpriteAnimation : public virtual IAnimation
{
    virtual ~ISpriteAnimation() {}

    virtual bool setSpriteAnimationCommonImage(std::shared_ptr<IImageList> pImgList, int imgId) = 0;
    virtual void clearAll() = 0; // Очищает все списки анимаций, а также CommonImage

    // Создаёт анимацию из вертикальной/горизонтальной ленты заданного изображения

    // Простая версия сама высчитывает количество кадров по размеру картинки
    virtual int addSpriteAnimationCustomImageList  (std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;

    // Расширенная версия использует указанное число кадров, но не более, чем есть в изображении
    virtual int addSpriteAnimationCustomImageListEx(std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int maxNumFrames) = 0;

    virtual int addSpriteAnimation  (const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;
    virtual int addSpriteAnimationEx(const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) = 0;

    virtual int addSpriteAnimationCustomImageListFramesList(std::shared_ptr<IImageList> pImageList, const std::vector<int> &frameList) = 0;
    virtual int addSpriteAnimationCustomImageListFramesRange(std::shared_ptr<IImageList> pImageList, int firstFrameIdx, int numFrames) = 0;
    virtual int addSpriteAnimationCustomImageListFramesAll(std::shared_ptr<IImageList> pImageList) = 0;


    // Версии для добавления кадров к существующим анимациям, возвращают aniId, если всё хорошо, или -1 при ошибке
    virtual int appendSpriteAnimationCustomImageList  (int aniId, std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;
    virtual int appendSpriteAnimationCustomImageListEx(int aniId, std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int maxNumFrames) = 0;
    virtual int appendSpriteAnimation  (int aniId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;
    virtual int appendSpriteAnimationEx(int aniId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) = 0;
    virtual int appendSpriteAnimationCustomImageListFramesList (int aniId, std::shared_ptr<IImageList> pImageList, const std::vector<int> &frameList) = 0;
    virtual int appendSpriteAnimationCustomImageListFramesRange(int aniId, std::shared_ptr<IImageList> pImageList, int firstFrameIdx, int numFrames) = 0;
    virtual int appendSpriteAnimationCustomImageListFramesAll  (int aniId, std::shared_ptr<IImageList> pImageList) = 0;

    // А оно надо? Есть же уже в родителе addSimpleAnimation
    // // Создаёт анимацию без IImageList и индекса изображения, их надо будет установить отдельно для каждого кадра
    // virtual int addSpriteAnimationSimple(int numFrames) = 0;
    //  

    virtual bool setSpriteAnimationFrameImage(int aniId, int frameId, std::shared_ptr<IImageList> pImgList, int imgId) = 0;

    virtual std::shared_ptr<IImageList> getSpriteAnimationFrameImageList (int aniId, int frameId) const = 0;
    virtual int       getSpriteAnimationFrameImageIndex(int aniId, int frameId) const = 0;
    virtual ImageSize getSpriteAnimationFrameImagePos  (int aniId, int frameId) const = 0;
    virtual ImageSize getSpriteAnimationFrameImageSize (int aniId, int frameId) const = 0;
    virtual ImageSize getSpriteAnimationFramePivotPoint(int aniId, int frameId) const = 0;

    virtual bool setSpriteAnimationFramePivotPoint(int aniId, int frameId, ImageSize pivotPoint) = 0;
    virtual bool setSpriteAnimationPivotPoint(int aniId, ImageSize pivotPoint) = 0;
    virtual bool setSpriteAnimationPivotPointToCenter(int aniId, bool bVerticalCenter) = 0;
    virtual bool setSpriteAnimationPivotPointCoord(int aniId, bool bVerticalCoord, int coordValue) = 0;



}; // struct ISpriteAnimation

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
struct SpriteAnimationDrawer : public IAnimationDrawingHandler
{
    virtual bool drawAnimationFrame( IDrawContext *pdc, IAnimation* pAnimation, IImageList* pImgList, int imgId
                                   , const DrawCoord &screenPos, const DrawCoord &screenSize
                                   , ImageSize imgPartLeftTop, ImageSize imgPartSize
                                   ) const override
    {
        if (!pdc  /* || !pAnimation */  || !pImgList)
            return false;

        MARTY_ARG_USED(pAnimation);

        pdc->drawImageScaled( pImgList, imgId, screenPos, screenSize, imgPartLeftTop, imgPartSize);

        return true;
    }

}; // struct SpriteAnimationDrawer

//----------------------------------------------------------------------------
inline
std::shared_ptr<IAnimationDrawingHandler> createSharedSpriteAnimationDrawer()
{
    auto pDrawerImpl = std::make_shared<SpriteAnimationDrawer>();
    return std::static_pointer_cast<IAnimationDrawingHandler>(pDrawerImpl);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename THandler>
class AnimationFrameChangeHandler : public IAnimationFrameChangeHandler
{
protected:

    THandler   handler;

    void onAnimationFrameChanged(IAnimation* pAnimation, std::uint32_t curTickMs, int aniId, int newFrameId, bool bDone, bool bRestarted) override // при bDone bRestarted может быть true/false, иначе игнор
    {
        handler(pAnimation, curTickMs, aniId, newFrameId, bDone, bRestarted);
    }

public:

    AnimationFrameChangeHandler(THandler h) : handler(h) {}

    AnimationFrameChangeHandler(const AnimationFrameChangeHandler&) = delete;
    AnimationFrameChangeHandler& operator=(const AnimationFrameChangeHandler&) = delete;

    AnimationFrameChangeHandler(AnimationFrameChangeHandler&&) = default;
    AnimationFrameChangeHandler& operator=(AnimationFrameChangeHandler&&) = default;

}; // class AnimationFrameChangeHandler

//----------------------------------------------------------------------------
template<typename THandler> inline
std::shared_ptr<IAnimationFrameChangeHandler> createSharedAnimationFrameChangeHandler(THandler h)
{
    auto impl = std::make_shared< AnimationFrameChangeHandler<THandler> >(h);
    return std::static_pointer_cast<IAnimationFrameChangeHandler>(impl);
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------



//----------------------------------------------------------------------------


} // namespace marty_draw_context


