#pragma once

#include "i_draw_context.h"
#include "i_image_list.h"


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


struct IAnimationDrawingHandler
{
    virtual ~IAnimationDrawingHandler() {};
    virtual bool drawFrame(IDrawContext *pdc, const DrawCoord &pos, const DrawCoord &size, int aniId, int frameNum) const = 0;

}; // struct IAnimationDrawingHandler


struct IAnimation
{
    virtual ~IAnimation() {}

    virtual void clear() = 0; // clears all
    virtual void clearAnimations() = 0; // Только список анимаций, базовая картинка остаётся та же

    virtual bool drawFrameEx(IDrawContext *pdc, int aniId, int frameNum) const = 0; // отрисовка конкретной фазы заданной анимации
    virtual bool drawFrame(IDrawContext *pdc, int aniId) const = 0; // отрисовка текущей фазы заданной анимации
    virtual bool drawCurrentFrame(IDrawContext *pdc, int ainId) const = 0; // отрисовка текущей фазы текущей анимации

    virtual bool setTargetPosition(const DrawCoord &pos ) = 0; // установка положения на экране, left/top, используется скалинг DrawContext'а
    virtual bool setTargetSize    (const DrawCoord &size) = 0; // установка размера на экране
    virtual bool setTargetScaled  (bool allowScale) = 0; // влияет ли targetSize на отрсовку, или изображение переносится попиксельно как есть

    virtual bool setAnimationDrawHandler( std::shared_pre<IAnimationDrawingHandler> pHandler) const = 0;

    virtual bool setCurrentAnimationEx(unsigned curTickMs, int aniId, int frameId) = 0;
    virtual bool setCurrentAnimation(unsigned curTickMs, int aniId) = 0;

    virtual bool performAnimationStep(unsigned curTickMs) = 0;
    virtual bool pauseAnimation() = 0;

    virtual int addSimpleAnimation(int numFrames) = 0;

    virtual bool setAnimationBaseTiming(int aniId, unsigned ms) = 0; // Также очищает все кастомные тайминги

    virtual bool setAnimationFrameTiming(int aniId, int frameId, unsigned ms) = 0; // Задаёт время отображения фрейма (кастомный тайминг фрейма)

};


struct ISpriteAnimation
{
    virtual ~ISpriteAnimation() {}

    virtual bool assignAnimationImage(IImageList *pImgList, int imgId) = 0; // Очищает также все списки анимаций

    // Создаёт анимацию из вертикальной/горизонтальной ленты заданного изображения

    // Простая версия сама высчитывает количество кадров по размеру картинки
    virtual int addAnimation  (const ImageSize &basePos, const ImageSize &frameSize, bool bVertical) = 0;

    // Расширенная версия использует указанное число кадров, но не более, чем есть в изображении
    virtual int addAnimationEx(const ImageSize &basePos, const ImageSize &frameSize, bool bVertical, int numFrames) = 0;

}; // struct IAnimation




} // namespace marty_draw_context

