#pragma once

#include "i_draw_context.h"


namespace marty_draw_context {


inline
void drawSimpleRect( IDrawContext            *pDc
                   , const DrawCoord         &pos
                   , const DrawCoord         &size
                   , int                     penId = -1
                   )
{
    int prevPenId = pDc->selectPen( penId );
    pDc->moveTo(pos);
    pDc->lineTo(DrawCoord(pos.x+size.x, pos.y       ));
    pDc->lineTo(DrawCoord(pos.x+size.x, pos.y+size.y));
    pDc->lineTo(DrawCoord(pos.x       , pos.y+size.y));
    pDc->lineTo(DrawCoord(pos.x       , pos.y       ));
    pDc->selectPen( prevPenId );
}


inline
void drawSquareMarker( marty_draw_context::IDrawContext *pDc, DrawCoord pos
                     , int penId = -1
                     )
{
    int prevPenId = -1;
    if (penId<0)
       prevPenId = pDc->selectPen(pDc->getDefaultCosmeticPen());
    else
       prevPenId = pDc->selectPen( penId );
    auto sz = DrawCoord(1,1);
    pDc->rect( pos-sz, pos+sz );
    pDc->selectPen( prevPenId );
}



} // namespace marty_draw_context


