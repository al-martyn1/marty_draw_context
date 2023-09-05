#pragma once


#include "draw_context_types.h"

namespace marty_draw_context {



// http://algolist.ru/graphics/find_col.php
// Множители 30;59;11 - отражают различную чувствительность человеческого глаза к красному,зеленому и синему цветам соответственно.

// https://qna.habr.com/q/1093976

inline
unsigned calcColorRefDistanceScaled( ColorRef c1, ColorRef c2 )
{
    return c1.colorDistance(c2);
}

inline
unsigned calcColorRefDistanceExact( ColorRef c1, ColorRef c2 )
{
    return c1.colorDistanceEx(c2,1,1,1);
}



/*
inline
unsigned calcColorRefDistanceScaled( std::int32_t c1, std::int32_t c2 )
{
    return calcColorRefDistanceScaled(ColorRef::fromUnsigned(c1), ColorRef::fromUnsigned(c2));
}

inline
unsigned calcColorRefDistanceExact( std::int32_t c1, std::int32_t c2 )
{
    return calcColorRefDistanceExact(ColorRef::fromUnsigned(c1), ColorRef::fromUnsigned(c2));
}



inline
unsigned calcColorRefDistanceScaled( ColorRef c1, std::int32_t c2 )
{
    return calcColorRefDistanceScaled(c1, ColorRef::fromUnsigned(c2));
}

inline
unsigned calcColorRefDistanceExact( ColorRef c1, std::int32_t c2 )
{
    return calcColorRefDistanceExact(c1, ColorRef::fromUnsigned(c2));
}
*/





} // namespace marty_draw_context

