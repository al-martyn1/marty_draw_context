#pragma once


#include "dc_debug/uw_log.h"
#include "color_raw_enum.h"


namespace marty_draw_context {


#if 0

struct ColorHsl
{
    color_component_type  h;
    color_component_type  l;
    color_component_type  s;

    // operator ColorRgb()
    // {}
    //
    // ColorHsl(const ColorRgb &rgb)
    // {}
};

#if defined(UMBA_SIMPLE_FORMATTER_H)
inline
umba::SimpleFormatter& operator<<(umba::SimpleFormatter &s, const ColorHsl &chls)
{
    s << "hue: " << chls.h << ", luminance: " << chls.l << ", saturation: " << chls.s;
    return s;
}
#endif

template<typename StreamType>
inline
StreamType& printTo(StreamType& s, const char* msg, const ColorHsl &hls)
{
    s << msg << "hue: " << hls.h << ", luminance: " << hls.l << ", saturation: " << hls.s;
    return s;
}

#endif


struct ColorHsv
{
    std::uint8_t  h;
    std::uint8_t  s;
    std::uint8_t  v;

};

template<typename StreamType>
inline
StreamType& printTo(StreamType& s, const char* msg, const ColorHsv &hls)
{
    s << msg << "hue: " << hsv.h << ", saturation: " << hsv.s << ", value: " << hsv.v;
    return s;
}



struct ColorRef
{
    std::uint8_t  r = 0; // 0xFF0000
    std::uint8_t  g = 0; // 0x00FF00
    std::uint8_t  b = 0; // 0x0000FF

    std::uint8_t  a = 0; // Пока игнорируем

#if 0
    operator ColorRgb() const
    {
        return ColorRgb{ (color_component_type)r / (color_component_type)256
                       , (color_component_type)g / (color_component_type)256
                       , (color_component_type)b / (color_component_type)256
                       };
    }

    ColorRef(const ColorRgb &rgb)
    : r((std::uint8_t)(unsigned)(rgb.r*255))
    , g((std::uint8_t)(unsigned)(rgb.g*255))
    , b((std::uint8_t)(unsigned)(rgb.b*255))
    { }
#endif

    static
    int calcColorComponentDelta( std::uint8_t c1, std::uint8_t c2 )
    {
        return ((int)(std::uint16_t)c1) - ((int)(std::uint16_t)c2);
    }

    static
    unsigned calcColorComponentDeltaSquare( std::uint8_t c1, std::uint8_t c2 )
    {
        int delta = calcColorComponentDelta(c1,c2);
        return (unsigned)(delta*delta);
    }

    unsigned colorDistanceEx( ColorRef c, unsigned scR, unsigned scG, unsigned scB ) const
    {
        return scR*calcColorComponentDeltaSquare(r,c.r)
             + scG*calcColorComponentDeltaSquare(g,c.g)
             + scB*calcColorComponentDeltaSquare(b,c.b)
             ;
    }

    unsigned colorDistance( ColorRef c ) const
    {
        return colorDistanceEx( c, 30, 59, 11 ); // Множители отражают различную чувствительность человеческого глаза к красному,зеленому и синему цветам соответственно.
    }

    #if 0
    ColorHsl toHsl() const
    {
        #if defined(WIN32) || defined(_WIN32)

            // https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-colorrgbtohls

            WORD     hue       ; // тон
            WORD     luminance ; // светлота
            WORD     saturation; // насыщенность

            ColorRGBToHLS( toWinColorRef(), &hue, &luminance, &saturation );

            return ColorHsl{(color_component_type)hue, (color_component_type)luminance, (color_component_type)saturation};

        #else

            return ColorHsl{0, 0, 0};

        #endif

    }
    #endif

    // https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
    ColorHsv toHsv() const
    {
         ColorHsv hsv;
         unsigned char rgbMin, rgbMax;

         auto rgb = *this;

         rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
         rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

         hsv.v = rgbMax;
         if (hsv.v == 0)
         {
             hsv.h = 0;
             hsv.s = 0;
             return hsv;
         }

         hsv.s = (std::uint8_t)(255 * long(rgbMax - rgbMin) / hsv.v);
         if (hsv.s == 0)
         {
             hsv.h = 0;
             return hsv;
         }

         if (rgbMax == rgb.r)
             hsv.h = (std::uint8_t)(0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin));
         else if (rgbMax == rgb.g)
             hsv.h = (std::uint8_t)(85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin));
         else
             hsv.h = (std::uint8_t)(171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin));

         return hsv;
    }

    static
    ColorRef fromHsv( ColorHsv hsv )
    {
        ColorRef rgb;
        unsigned char region, remainder, p, q, t;

        if (hsv.s == 0)
        {
            rgb.r = hsv.v;
            rgb.g = hsv.v;
            rgb.b = hsv.v;
            return rgb;
        }

        region = (std::uint8_t)(hsv.h / 43);
        remainder = (std::uint8_t)((hsv.h - (region * 43)) * 6);

        p = (std::uint8_t)((hsv.v * (255 - hsv.s)) >> 8);
        q = (std::uint8_t)((hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8);
        t = (std::uint8_t)((hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8);

        switch (region)
        {
            case 0:
                rgb.r = hsv.v; rgb.g = t; rgb.b = p;
                break;
            case 1:
                rgb.r = q; rgb.g = hsv.v; rgb.b = p;
                break;
            case 2:
                rgb.r = p; rgb.g = hsv.v; rgb.b = t;
                break;
            case 3:
                rgb.r = p; rgb.g = q; rgb.b = hsv.v;
                break;
            case 4:
                rgb.r = t; rgb.g = p; rgb.b = hsv.v;
                break;
            default:
                rgb.r = hsv.v; rgb.g = p; rgb.b = q;
                break;
        }

        return rgb;
    }

    // Переделать светлоту
    ColorRef lumAdjusted( int lumAdjustmentPermille ) const
    {
        MARTY_ARG_USED(lumAdjustmentPermille);

        #if 0

        #if defined(WIN32) || defined(_WIN32)

            // https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-coloradjustluma

            return fromWinColorRef( ColorAdjustLuma( toWinColorRef()
                                                   , lumAdjustmentPermille
                                                   , TRUE // non-absolute value
                                                   )
                                  );

        #else

            return *this;

        #endif

        #endif

        return *this;
    }


    ColorRef satAdjusted( int satAdjustmentPermille ) const
    {
        ColorHsv hsv = toHsv();

        bool adjNeg = satAdjustmentPermille<0;
        unsigned adjValAbs = (unsigned)(satAdjustmentPermille<0 ? -satAdjustmentPermille : satAdjustmentPermille);

        int sat = (int)hsv.s;

        if (adjValAbs)
        {
            unsigned adjVal = sat*adjValAbs/1000;
            if (adjNeg)
            {
                //sat -= (int)adjVal;
                sat -= (int)adjVal;
            }
            else
            {
                //sat += (int)adjVal;
                sat += (int)adjVal;
            }
        }

        if (sat<0)
        {
            sat = 0;
        }

        if (sat>255)
        {
            sat = 255;
        }

        hsv.s = (std::uint8_t)sat;

        return fromHsv(hsv);

        #if 0
        #if defined(WIN32) || defined(_WIN32)

            // https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-colorrgbtohls

            WORD     hue       ; // тон
            WORD     luminance ; // светлота
            WORD     saturation; // насыщенность

            ColorRGBToHLS( toWinColorRef(), &hue, &luminance, &saturation );

            // https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-colorhlstorgb

            bool adjNeg = satAdjustmentPermille<0;
            unsigned adjValAbs = (unsigned)(satAdjustmentPermille<0 ? -satAdjustmentPermille : satAdjustmentPermille);

            int sat = (int)saturation;

            if (adjValAbs)
            {
                unsigned adjVal = sat*adjValAbs/1000;
                if (adjNeg)
                {
                    //sat -= (int)adjVal;
                    sat -= (int)adjVal;
                }
                else
                {
                    //sat += (int)adjVal;
                    sat += (int)adjVal;
                }
            }

            if (sat<0)
            {
                sat = 0;
            }

            if (sat>255)
            {
                sat = 255;
            }

            WORD wNewSat = (WORD)(unsigned)sat;

            return fromWinColorRef( ColorHLSToRGB(hue, luminance, wNewSat) );

        #else

            return *this;

        #endif
        #endif
    }


    // // Color constants.
    // const COLORREF rgbRed   =  0x000000FF;
    // const COLORREF rgbGreen =  0x0000FF00;
    // const COLORREF rgbBlue  =  0x00FF0000;
    // const COLORREF rgbBlack =  0x00000000;
    // const COLORREF rgbWhite =  0x00FFFFFF;

    std::uint32_t toWinColorRef() const
    {
        return (((std::uint32_t)b)<<16)
             | (((std::uint32_t)g)<< 8)
             | (((std::uint32_t)r)<< 0)
             ;
    }

    static
    ColorRef fromWinColorRef(std::uint32_t crul)
    {
        auto r = (std::uint8_t)((crul&0x0000FFu)>>0);
        auto g = (std::uint8_t)((crul&0x00FF00u)>>8);
        auto b = (std::uint8_t)((crul&0xFF0000u)>>16);
        return ColorRef{ r, g, b };
    }


    std::uint32_t toUnsigned() const
    {
        return (((std::uint32_t)r)<<16)
             | (((std::uint32_t)g)<< 8)
             | (((std::uint32_t)b)<< 0)
             ;
    }

    static
    ColorRef fromUnsigned(std::uint32_t crul)
    {
        auto r = (std::uint8_t)((crul&0xFF0000u)>>16);
        auto g = (std::uint8_t)((crul&0x00FF00u)>>8);
        auto b = (std::uint8_t)((crul&0x0000FFu)>>0);
        return ColorRef{ r, g, b };
    }

    static
    ColorRef deserialize(std::string str)
    {
        if (str.empty())
        {
            throw std::runtime_error("ColorRef::deserialize: empty input");
        }


        if (str[0]=='#')
        {
            str.erase(0,1); // remove leading '#'

            if (str.size()==3)
            {
                std::string tmp;
                for(auto ch: str)
                {
                    tmp.append(2, ch);
                }

                swap(tmp,str);
            }

            if (str.size()!=6)
            {
                throw std::runtime_error("ColorRef::deserialize: invalid format - color value must be 3 or 6 hex digits len");
            }

            //auto tmp = std::string(str, 1);
            std::string::size_type sz = 0;
            unsigned long crul = std::stoul(str, &sz, 16);
            if (sz!=str.size())
                throw std::runtime_error("ColorRef::deserialize: bad hex value");

            return fromUnsigned(crul);
        }

        return fromUnsigned( (std::uint32_t)marty_draw_context::enum_deserialize_EColorRawEnum(str) );
    }

    std::string serialize() const
    {
        std::uint32_t crul = toUnsigned();

        std::string serialized = marty_draw_context::enum_serialize_EColorRawEnum((marty_draw_context::EColorRawEnum)crul);
        if (!serialized.empty())
             return serialized;

        #if defined(_MSC_VER)
            #pragma warning(push)
            #pragma warning(disable:4996) // warning C4996: This function or variable may be unsafe. Consider using sprintf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
        #endif

        char buf[32];
        std::sprintf(buf, "#%06X", crul);

        #if defined(_MSC_VER)
            #pragma warning(pop)
        #endif

        return std::string(buf);
    }

    bool operator<(ColorRef other) const
    {
        return toUnsigned() < other.toUnsigned();
    }

    bool operator>(ColorRef other) const
    {
        return toUnsigned() > other.toUnsigned();
    }

}; // struct ColorRef

#if 1
#if defined(UMBA_SIMPLE_FORMATTER_H)
inline
umba::SimpleFormatter& operator<<(umba::SimpleFormatter &s, const ColorRef &rgb)
{
    s << "r: " << (unsigned)rgb.r << ", g: " << (unsigned)rgb.g << ", b: " << (unsigned)rgb.b;
    return s;
}
#else
    #ifdef _MSC_VER
        #pragma message("dc/colorref.h: umba::SimpleFormatter not found")
    #else
        // #error "dc/colorref.h: umba::SimpleFormatter not found"
    #endif
#endif
#endif

template<typename StreamType>
inline
StreamType& printTo(StreamType& s, const char* msg, const ColorRef &rgb)
{
    s << msg << "r: " << (unsigned)rgb.r << ", g: " << (unsigned)rgb.g << ", b: " << (unsigned)rgb.b;
    return s;
}



} // namespace marty_draw_context
