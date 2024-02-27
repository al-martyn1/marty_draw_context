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
    virtual bool drawFrame(IDrawContext *pdc, IAnimation *pAnimation, const DrawCoord &pos, const DrawCoord &size, int aniId, int frameNum) const = 0;

}; // struct IAnimationDrawingHandler


struct IAnimation
{
    virtual ~IAnimation() {}

    virtual void clear() = 0; // clears all
    virtual void clearAnimations() = 0; // Только список анимаций, базовая картинка остаётся та же

    virtual bool drawFrameEx(IDrawContext *pdc, int aniId, int frameNum) const = 0; // отрисовка конкретной фазы заданной анимации
    virtual bool drawFrame(IDrawContext *pdc, int aniId) const = 0; // отрисовка текущей фазы заданной анимации
    virtual bool drawCurrentFrame(IDrawContext *pdc, int ainId) const = 0; // отрисовка текущей фазы текущей анимации

    virtual bool setTargetPosition(const DrawCoord &pos ) = 0; // установка положения на экране, left/top
    virtual bool setTargetSize    (const DrawCoord &size) = 0; // установка размера на экране
    virtual bool setTargetScaled  (bool allowScale) = 0; // влияет ли targetSize на отрсовку, или изображение переносится попиксельно как есть

    virtual DrawCoord getTargetPosition() = 0;
    virtual DrawCoord getTargetSize() = 0;
    virtual bool getTargetScaled() = 0;

    virtual bool setAnimationDrawHandler( std::shared_ptr<IAnimationDrawingHandler> pHandler) const = 0;

    virtual bool setCurrentAnimationEx(unsigned curTickMs, int aniId, int frameId) = 0;
    virtual bool setCurrentAnimation(unsigned curTickMs, int aniId) = 0;

    // Возвращает true, если кадр пересчелкнулся
    virtual bool performAnimationStep(unsigned curTickMs) = 0;
    virtual bool pauseAnimation(bool bPause) = 0;
    virtual bool getAnimationPaused() = 0;

    virtual int addSimpleAnimation(int numFrames) = 0;

    virtual bool setAnimationBaseTiming(int aniId, unsigned ms) = 0; // Также очищает все кастомные тайминги

    virtual bool setAnimationFrameTiming(int aniId, int frameId, unsigned ms) = 0; // Задаёт время отображения фрейма (кастомный тайминг фрейма)

    virtual bool setAnimationLooping(int aniId, bool bLoop) = 0;
    virtual bool getAnimationLooping(int aniId) = 0;

};


struct ISpriteAnimation : public IAnimation
{
    virtual ~ISpriteAnimation() {}

    virtual bool assignAnimationCommonImage(std::shared_ptr<IImageList> pImgList, int imgId) = 0; // Очищает также все списки анимаций

    // Создаёт анимацию из вертикальной/горизонтальной ленты заданного изображения

    // Простая версия сама высчитывает количество кадров по размеру картинки
    virtual int addSpriteAnimation  (const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;

    // Расширенная версия использует указанное число кадров, но не более, чем есть в изображении
    virtual int addSpriteAnimationEx(const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) = 0;

    // Создаёт анимацию без IImageList и индекса изображения, их надо будет установить отдельно для каждого кадра
    virtual int addSpriteAnimationSimple(int numFrames) = 0;

    virtual bool setSpriteAnimationFrameImage(std::shared_ptr<IImageList> pImgList, int imgId) = 0;

}; // struct IAnimation




} // namespace marty_draw_context

