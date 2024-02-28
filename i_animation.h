#pragma once

#include "i_draw_context.h"
#include "i_image_list.h"

//
#include <memory>

/*
    Когда вызывать анимирование анимаций?

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
    virtual bool drawFrame(IDrawContext *pdc, const IAnimation *pAnimation, const DrawCoord &pos, const DrawCoord &size, bool useSize, int aniId, int frameNum) const = 0;

}; // struct IAnimationDrawingHandler


struct IAnimation
{
    virtual ~IAnimation() {}

    virtual int  size()  const = 0;
    virtual bool empty() const = 0;

    virtual void clear() = 0; // Только список анимаций

    // Невидимые анимации не будут рисоваться. С большой долей вероятности такая фича будет востребована, и, чтобы не хранить её отдельно, запилим сразу тут
    bool setVisible(bool bVisible) = 0;
    bool isVisible() const = 0;

    virtual bool drawAnimationFrame(IDrawContext *pdc, int aniId, int frameNum) const = 0; // отрисовка конкретной фазы заданной анимации
    virtual bool drawAnimationCurrentFrame(IDrawContext *pdc, int aniId) const = 0; // отрисовка текущей фазы заданной анимации
    virtual bool drawCurrentFrame(IDrawContext *pdc) const = 0; // отрисовка текущей фазы текущей анимации

    virtual bool setTargetPosition(const DrawCoord &pos ) = 0; // установка положения на экране, left/top
    virtual DrawCoord getTargetPosition() = 0;
    virtual bool setTargetSize    (const DrawCoord &size) = 0; // установка размера на экране
    virtual DrawCoord getTargetSize() = 0;
    virtual bool setTargetScaled  (bool allowScale) = 0; // влияет ли targetSize на отрисовку, или изображение переносится попиксельно как есть
    virtual bool getTargetScaled() = 0;

    virtual bool setAnimationFrameScale(int aniId, int frameNum, DrawCoord::value_type scale) = 0;
    
    virtual bool setAnimationDrawingHandler( std::shared_ptr<IAnimationDrawingHandler> pHandler) const = 0;
    virtual void clearAnimationDrawingHandler() = 0;

    virtual bool setCurrentAnimationEx(std::uint32_t curTickMs, int aniId, int frameId) = 0;
    virtual bool setCurrentAnimation(std::uint32_t curTickMs, int aniId) = 0;

    // Возвращает true, если кадр пересчелкнулся
    virtual bool performCurrentAnimationStep(std::uint32_t curTickMs, bool *pRestarted) = 0;
    virtual bool pauseCurrentAnimation(std::uint32_t curTickMs, bool bPause) = 0; // returns true if paused
    virtual bool isCurrentAnimationPaused() const = 0;

    virtual bool setAnimationsCommonFrameTiming(std::uint32_t ms) = 0; // Будет действовать на новые анимации
    virtual std::uint32_t getAnimationsCommonFrameTiming() const = 0;
    virtual bool setAnimationFramesTiming(int aniId, std::uint32_t ms) = 0; // Также переустанавливает все кастомные тайминги в анимации
    virtual int  addSimpleAnimation(int numFrames) = 0;
    virtual bool setAnimationFrameTiming(int aniId, int frameId, std::uint32_t ms) = 0; // Задаёт время отображения фрейма (кастомный тайминг фрейма)

    virtual bool setAnimationLooping(int aniId, bool bLoop) = 0;
    virtual bool getAnimationLooping(int aniId) = 0;

};


struct ISpriteAnimation : public virtual IAnimation
{
    virtual ~ISpriteAnimation() {}

    virtual bool setSpriteAnimationCommonImage(std::shared_ptr<IImageList> pImgList, int imgId) = 0;
    virtual bool clearAll() = 0; // Очищает все списки анимаций, а также CommonImage

    // Создаёт анимацию из вертикальной/горизонтальной ленты заданного изображения

    // Простая версия сама высчитывает количество кадров по размеру картинки
    virtual int addSpriteAnimationCustomImageList  (std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;

    // Расширенная версия использует указанное число кадров, но не более, чем есть в изображении
    virtual int addSpriteAnimationCustomImageListEx(std::shared_ptr<IImageList> pImageList, int imgId, const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) = 0;

    virtual int addSpriteAnimation  (const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;
    virtual int addSpriteAnimationEx(const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) = 0;


    // А оно надо? Есть же уже в родителе addSimpleAnimation
    // // Создаёт анимацию без IImageList и индекса изображения, их надо будет установить отдельно для каждого кадра
    // virtual int addSpriteAnimationSimple(int numFrames) = 0;
    //  

    virtual bool setSpriteAnimationFrameImage(int aniId, int frameId, std::shared_ptr<IImageList> pImgList, int imgId) = 0;

    virtual std::shared_ptr<IImageList> getSpriteAnimationFrameImageList (int aniId, int frameId) = 0;
    virtual int                         getSpriteAnimationFrameImageIndex(int aniId, int frameId) = 0;
    virtual ImageSize                   getSpriteAnimationFrameImagePos  (int aniId, int frameId) = 0;
    virtual ImageSize                   getSpriteAnimationFrameImageSize (int aniId, int frameId) = 0;



}; // struct IAnimation




} // namespace marty_draw_context

