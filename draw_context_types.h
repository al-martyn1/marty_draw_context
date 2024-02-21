#pragma once


//#include <stdint>

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <utility>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <cerrno>

#include "marty_decimal/marty_decimal.h"

#include "dc_debug/uw_log.h"

#include "colorref.h"
#include "color_raw_enum.h"
#include "draw_context_enums.h"

#if defined(WIN32) || defined(_WIN32)

    #include <shlwapi.h>
    #if defined(_MSC_VER)
        #pragma comment (lib,"Shlwapi.lib")
    #endif

#endif


#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif



namespace marty_draw_context {




//----------------------------------------------------------------------------
// See
// https://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
// https://stackoverflow.com/questions/35985960/c-why-is-boosthash-combine-the-best-way-to-combine-hash-values/50978188#50978188
// http://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
// https://stackoverflow.com/questions/19195183/how-to-properly-hash-the-custom-struct

template <class T> inline
std::size_t hash_combine(std::size_t seed, const T &v)
{
    //std::hash<T> hasher;
    return seed ^ ( std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2) );
}

//----------------------------------------------------------------------------



template<typename FloatType>
FloatType floatFromString( const std::string &str, std::size_t* pPosOut = 0 )
{
    /*
    // Это не нужно - std::stof сама это делает
    // for(; *pStr && (*pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip leading WS

    if (*pStr==0) // вся строка - одни пробелы
    {
        if (pPosOut)
        {
            *pPosOut = 0;
        }
        else
        {
            throw std::invalid_argument("marty_draw_context::floatFromString: Failed to convert string to float value  empty string (space only)");
        }
    }
    */

    float f = std::stof(str, pPosOut);

    return FloatType(f);
}

template<typename FloatType>
FloatType floatFromString( const char* pStr, std::size_t* pPosOut = 0 )
{
    if (!pStr)
    {
        throw std::runtime_error("marty_draw_context::floatFromString: pStr is null");
    }

    return floatFromString<FloatType>(std::string(pStr), pPosOut);
}


template<>
double floatFromString<double>( const std::string &str, std::size_t* pPosOut )
{
    double f = std::stod(str, pPosOut);
    return double(f);
}

template<>
double floatFromString<double>( const char* pStr, std::size_t* pPosOut )
{
    if (!pStr)
    {
        throw std::runtime_error("marty_draw_context::floatFromString: pStr is null");
    }

    return floatFromString<double>(std::string(pStr), pPosOut);
}

template<>
marty::Decimal floatFromString<marty::Decimal>( const char* pStr, std::size_t* pPosOut )
{
    //TODO: !!! Протестировать

    if (!pStr)
    {
        throw std::runtime_error("marty_draw_context::floatFromString: pStr is null");
    }

    std::size_t pos = 0;
    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip leading WS

    // Вообще-то Decimal::fromString сам пробелы хавает, но нам нужно посчитать количество символов

    if (*pStr==0) // вся строка - одни пробелы
    {
        throw std::invalid_argument("marty_draw_context::floatFromString: Failed to convert string to float value: empty string (spaces only)");
    }

    std::size_t startPos = pos;

    pos = 0;

    if (*pStr=='+' || *pStr=='-')
    {
        ++pos;
    }

    // Возможно, после знака тоже стоит пропустить пробелы
    // for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip leading WS

    std::size_t dotCount = 0;

    auto isDecDigit = [&](char ch) -> bool
    {
        if (ch>='0' && ch<='9')
        {
            return true;
        }

        return false;
    };

    for(; *pStr && isDecDigit(pStr[pos]) && dotCount<2; ++pos)
    {
        if (pStr[pos]=='.')
        {
            ++dotCount;
        }
    }
    
    if (pPosOut)
    {
        *pPosOut = startPos + pos;
    }

    return marty::Decimal::fromString(std::string(pStr, pos));
}

template<>
marty::Decimal floatFromString<marty::Decimal>( const std::string &str, std::size_t* pPosOut )
{
    //TODO: !!! Протестировать

    return floatFromString<marty::Decimal>(str.c_str(), pPosOut);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
std::string floatToString(float v)
{
    return std::to_string(v);
}

inline
std::string floatToString(double v)
{
    return std::to_string(v);
}

inline
std::string floatToString(const marty::Decimal &v)
{
    return v.toString();
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawCoord;

DrawCoord operator*( const DrawCoord &c1, const DrawCoord &c2 );
//DrawCoord operator*( DrawCoord::value_type scale, const DrawCoord &c );
//DrawCoord operator*( const DrawCoord &c, DrawCoord::value_type scale );
DrawCoord operator/( const DrawCoord &c1, const DrawCoord &c2 );
//DrawCoord operator/( const DrawCoord &c, DrawCoord::value_type d );
DrawCoord operator+( const DrawCoord &c1, const DrawCoord &c2 );
DrawCoord operator-( const DrawCoord &c1, const DrawCoord &c2 );

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

#if defined(DEBUG) || defined(_DEBUG)

    #define UNDERWOOD_DRAWCOORD_VALUE_TYPE_IS_INTEGRAL  1

#else

    // #define UNDERWOOD_DRAWCOORD_VALUE_TYPE_IS_INTEGRAL  0
    #define UNDERWOOD_DRAWCOORD_VALUE_TYPE_IS_INTEGRAL  1

#endif

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawCoord
{
    //typedef marty::Decimal  value_type;
    #if defined(UNDERWOOD_DRAWCOORD_VALUE_TYPE_IS_INTEGRAL) && UNDERWOOD_DRAWCOORD_VALUE_TYPE_IS_INTEGRAL!=0
        typedef double          value_type;
        static constexpr  bool  isValueTypeIntegral() { return true; }
    #else
        typedef marty::Decimal  value_type;
        static constexpr  bool  isValueTypeIntegral() { return false; }
    #endif

    value_type              x;
    value_type              y;



    DrawCoord() : x(0), y(0) {}

    // template<typename T>
    // DrawCoord( T tx, T ty ) : x(tx), y(ty) {}

    template<typename T1, typename T2>
    DrawCoord( T1 tx, T2 ty ) : x(tx), y(ty) {}

    // template<typename T>
    // DrawCoord( const T &t ) : x(t), y(t) {}

    //DrawCoord(const DrawCoord &c) : x(c.x), y(c.y) {}

    // Преобразование из строки в отдельную координату ()
    static
    value_type valueFromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        return floatFromString<value_type>(pStr, pPosOut);
    }

    static
    value_type valueFromString(const std::string &str, std::size_t* pPosOut = 0)
    {
        return floatFromString<value_type>(str.c_str(), pPosOut);
    }

    static
    value_type valueFromStringExact(const char* pStr)
    {
        std::size_t pos = 0;
        value_type v = valueFromString(pStr, &pos);

        // У нас должно быть только значение в строке на входе, и, возможно, какие-то пробелы в хвосте. Ничего другого не допустимо

        for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip trailing WS
        
        if (*pStr!=0)
        {
            throw std::invalid_argument("marty_draw_context::DrawCoord::valueFromStringExact: Failed to convert string to float value");
        }

        return v;
    }

    static
    value_type valueFromStringExact(const std::string &str)
    {
        return valueFromStringExact(str.c_str());
    }

    // Преобразование из строки в пару DrawCoord ()
    static
    DrawCoord fromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        std::size_t pos = 0;

        DrawCoord resCoord;

        // X
        for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip leading WS

        std::size_t
        pos2 = 0;
        resCoord.x = floatFromString<value_type>(pStr, &pos2);
        pos  += pos2;
        pStr += pos2;

        // Y
        for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip leading WS
    
        // Вообще-то Decimal::fromString сам пробелы хавает, но нам нужно посчитать количество символов. Да и Decimal::fromString не хавает \r\n
    
        if (*pStr==0) // вся строка - одни пробелы
        {
            throw std::invalid_argument("marty_draw_context::DrawCoord::fromString: Failed to convert string to float value: missing Y");
        }

        // -20+30 или -20-30 - это две компоненты, разделитель ','/';' - отсутствует, признаком разделения на компоненты выступает знак числа.
        // Такая херня практикуется в формате SVG
        if (*pStr!=',' && *pStr!=';' && *pStr!='+' && *pStr!='-')
        {
            throw std::invalid_argument("marty_draw_context::DrawCoord::fromString: Failed to convert string to float value: missing x/y separator char (','/';')");
        }

        if (*pStr==',' || *pStr==';')
        {
            ++pos;
            ++pStr;
        }

        //std::size_t 
        pos2 = 0;

        resCoord.y = floatFromString<value_type>(pStr, &pos2);

        if (pPosOut)
        {
            *pPosOut = pos+pos2;
        }

        return resCoord;
    }

    static
    DrawCoord fromString(const std::string &str, std::size_t* pPosOut = 0)
    {
        return fromString(str.c_str(), pPosOut);
    }


//double floatFromString<marty::Decimal>( const std::string str, std::size_t* pPosOut = 0 )    


    // Расстояние со знаком для точек на горизонтальной/вертикальной прямой, или 0 если такого нет
    value_type sdistanceTo(const DrawCoord& other) const
    {
        if (x==other.x)      return y-other.y;
        else if (y==other.y) return x-other.x;
        else return 0;
    }


    value_type distanceTo(const DrawCoord& other) const
    {
        // if (x==other.x)      return std::abs(y-other.y);
        // else if (y==other.y) return std::abs(x-other.x);
        // else 
        // {
        //  
        // }
        
        auto dx = x-other.x;
        auto dy = y-other.y;

        return std::sqrt(dx*dx+dy*dy);
    }

    DrawCoord reflectTo(const DrawCoord& relativeTo) const
    {
        DrawCoord vec = relativeTo - *this;
        return *this + vec;
    }

    bool operator==( const DrawCoord &coord ) const
    {
        return x==coord.x && y==coord.y;
    }

    bool operator!=( const DrawCoord &coord ) const
    {
        return x!=coord.x || y!=coord.y;
    }

    DrawCoord operator-() const
    {
        return DrawCoord(-x,-y);
    }

    DrawCoord operator+() const
    {
        return DrawCoord(x,y);
    }

    DrawCoord& operator*=( const DrawCoord &coord )
    {
        x *= coord.x;
        y *= coord.y;
        return *this;
    }

    DrawCoord& operator*=( DrawCoord::value_type scale )
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    DrawCoord& operator/=( const DrawCoord &coord )
    {
        x /= coord.x;
        y /= coord.y;
        return *this;
    }

    DrawCoord& operator/=( DrawCoord::value_type d )
    {
        x /= d;
        y /= d;
        return *this;
    }

    DrawCoord& operator+=( const DrawCoord &coord )
    {
        x += coord.x;
        y += coord.y;
        return *this;
    }

    DrawCoord& operator-=( const DrawCoord &coord )
    {
        x -= coord.x;
        y -= coord.y;
        return *this;
    }

}; // DrawCoord

//----------------------------------------------------------------------------

inline
DrawCoord::value_type distance(const DrawCoord& c1, const DrawCoord& c2)
{
    return c1.distanceTo(c2);
}

//------------------------------
inline
DrawCoord operator*( const DrawCoord &c1, const DrawCoord &c2 )
{
    return DrawCoord{ c1.x*c2.x, c1.y*c2.y };
}

inline
DrawCoord operator*( DrawCoord::value_type scale, const DrawCoord &c )
{
    return DrawCoord{ c.x*scale, c.y*scale };
}

inline
DrawCoord operator*( const DrawCoord &c, DrawCoord::value_type scale )
{
    return DrawCoord{ c.x*scale, c.y*scale };
}


inline
DrawCoord operator*( std::size_t n, const DrawCoord &c2 )
{
    return DrawCoord{ c2.x*(DrawCoord::value_type)n, c2.y*(DrawCoord::value_type)n };
}

inline
DrawCoord operator*( const DrawCoord &c1, std::size_t n )
{
    return DrawCoord{ c1.x*(DrawCoord::value_type)n, c1.y*(DrawCoord::value_type)n };
}

//------------------------------
inline
DrawCoord operator/( const DrawCoord &c1, const DrawCoord &c2 )
{
    return DrawCoord{ c1.x/c2.x, c1.y/c2.y };
}

inline
DrawCoord operator/( const DrawCoord &c, DrawCoord::value_type d )
{
    return DrawCoord{ c.x/d, c.y/d };
}

inline
DrawCoord operator+( const DrawCoord &c1, const DrawCoord &c2 )
{
    return DrawCoord{ c1.x+c2.x, c1.y+c2.y };
}

inline
DrawCoord operator-( const DrawCoord &c1, const DrawCoord &c2 )
{
    return DrawCoord{ c1.x-c2.x, c1.y-c2.y };
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
DebugStreamImplBase& operator<<( DebugStreamImplBase& s, const DrawCoord &c )
{
    s<<c.x<<","<<c.y;
    return s;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

typedef DrawCoord DrawPoint;
typedef DrawCoord DrawSize ;
typedef DrawCoord DrawScale;



//----------------------------------------------------------------------------
// https://www.w3.org/TR/SVGTiny12/coords.html#ViewBoxAttribute
// A list of four <number>s (<min-x>, <min-y>, <width> and <height>), separated by white space and/or a comma
// "none"
struct ViewBox
{
    DrawCoord    leftTop = DrawCoord(0,0);
    DrawCoord    size    = DrawCoord(0,0);

    static 
    ViewBox fromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        ViewBox vb;

        if (!pStr || std::string("none")==pStr)
        {
            return vb;
        }

        std::size_t posTotal = 0;
        std::size_t pos = 0;

        vb.leftTop.x = DrawCoord::valueFromString(pStr, &pos);
        posTotal += pos;
        pStr     += pos;
        for(; *pStr && (*pStr==',' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++posTotal) {}

        vb.leftTop.y = DrawCoord::valueFromString(pStr, &pos);
        posTotal += pos;
        pStr     += pos;
        for(; *pStr && (*pStr==',' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++posTotal) {}

        vb.size.x = DrawCoord::valueFromString(pStr, &pos);
        posTotal += pos;
        pStr     += pos;
        for(; *pStr && (*pStr==',' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++posTotal) {}

        vb.size.y = DrawCoord::valueFromString(pStr, &pos);
        posTotal += pos;
        pStr     += pos;
        //for(; *pStr && (*pStr==',' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++posTotal) {}

        if (pPosOut)
        {
            *pPosOut = posTotal;
        }

        return vb;

    }

    static
    ViewBox fromString(const std::string &str, std::size_t* pPosOut = 0)
    {
        return fromString(str.c_str(), pPosOut);
    }

};

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// https://www.w3.org/TR/SVGTiny12/coords.html#Units
// The list of unit identifiers in SVG are: in, cm, mm, pt, pc, px and percentages (%).
struct ValueWithDimension
{
    typedef DrawCoord::value_type  value_type;

    value_type     value;
    std::string    dim  ;

    ValueWithDimension() : value(0), dim() {}
    ValueWithDimension(value_type v) : value(v), dim() {}
    ValueWithDimension(value_type v, const std::string &d) : value(v), dim(d) {}


    static 
    ValueWithDimension fromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        std::size_t pos = 0;

        ValueWithDimension vd;

        vd.value = floatFromString<value_type>(pStr, &pos);

        pStr += pos;
        std::size_t posNoSkipSpaces = pos;

        for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // удаляем пробелы после числа до юнитов

        if ( *pStr==0 || (*pStr=='+' || *pStr=='-' || (*pStr>='0' && *pStr<='9')) ) // конец строки, или знак или цифра - это следующее число, юнитов нет
        {
            // Юнитов нет, возвращаем длину без скипнутых пробелов
            if (pPosOut)
            {
                *pPosOut = posNoSkipSpaces;
            }

            return vd;
        }

        for(; *pStr && (*pStr!='\r' && *pStr!='\n' && *pStr!=' ' && *pStr!='\t'); ++pStr, ++pos)
        {
            vd.dim.append(1, *pStr);
        }

        if (pPosOut)
        {
            *pPosOut = pos;
        }

        return vd;
    
    }

    static
    ValueWithDimension fromString(const std::string &str, std::size_t* pPosOut = 0)
    {
        return fromString(str.c_str(), pPosOut);
    }


}; // struct ValueWithDimension

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct SizeWithDimensions
{
    ValueWithDimension    width ;
    ValueWithDimension    height;

    static
    ValueWithDimension valueFromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        return ValueWithDimension::fromString(pStr, pPosOut);
    }

    static
    ValueWithDimension valueFromString(const std::string str, std::size_t* pPosOut = 0)
    {
        return ValueWithDimension::fromString(str, pPosOut);
    }

}; // struct SizeWithDimensions

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct GradientParams
{
    ColorRef                 colorBegin;
    ColorRef                 colorMid  ;
    ColorRef                 colorEnd  ;

    DrawCoord::value_type    midPoint  = (DrawCoord::value_type)0.5;

}; // struct GradientParams

// struct DrawCoord
// {
//     //typedef marty::Decimal  value_type;





template<typename FloatType> inline
int floatToInt(FloatType f)
{
    return int(f);
}

template<> inline
int floatToInt<float>(float f)
{
    return f>0.0 ? int(f+0.5) : int(f-0.5);
}

template<> inline
int floatToInt<double>(double f)
{
    return f>0.0 ? int(f+0.5) : int(f-0.5);
}

template<> inline
int floatToInt<marty::Decimal>(marty::Decimal f)
{
    return int(f.round(0, marty::Decimal::RoundingMethod::roundMath));
}


template<typename FloatType> inline
float floatToFloat( FloatType f)
{
    return float(f);
}

template<> inline
float floatToFloat<float>( float f)
{
    return float(f);
}

template<> inline
float floatToFloat<double>( double f)
{
    return float(f);
}

template<> inline
float floatToFloat<int>( int f)
{
    return float(f);
}

template<> inline
float floatToFloat<marty::Decimal>( marty::Decimal f)
{
    return f.toFloat(); // int(f.round(0, marty::Decimal::RoundingMethod::roundMath));
}


template<typename FloatType> inline
double floatToDouble( FloatType f)
{
    return float(f);
}

template<> inline
double floatToDouble<float>( float f)
{
    return (float)f;
}

template<> inline
double floatToDouble<double>( double f)
{
    return (float)f;
}

template<> inline
double floatToDouble<int>( int f)
{
    return (float)f;
}

template<> inline
double floatToDouble<marty::Decimal>( marty::Decimal f)
{
    return (float)f.toDouble(); // int(f.round(0, marty::Decimal::RoundingMethod::roundMath));
}


//----------------------------------------------------------------------------
inline
double& drawCoordValueTypeFromStringHelper(double& n, const std::string &str)
{
    std::string::size_type idx = 0;

    double tmp = std::stod(str, &idx);
    if (idx!=str.size())
    {
        throw std::runtime_error("drawCoordValueTypeFromStringHelper: conversion to double fails");
    }

    n = tmp;
    return n;
}

//------------------------------
inline
marty::Decimal& drawCoordValueTypeFromStringHelper(marty::Decimal& n, const std::string &str)
{
    n = marty::Decimal(str);
    return n;
}

//------------------------------
inline
DrawCoord::value_type drawCoordValueTypeFromString(const std::string &str)
{
    DrawCoord::value_type res;
    return drawCoordValueTypeFromStringHelper(res,str);
}

//----------------------------------------------------------------------------




namespace ArcDirection {

static const bool CounterClockwise = true;
static const bool Clockwise        = false;

static const bool Ccw              = true;
static const bool Cw               = false;


} // namespace ArcDirection

//                        directionCounterclockwise = true;


inline
int getFontWeightWidthScale(FontWeight fw)
{
    unsigned ufw = (unsigned)fw;
    if (ufw<100) return  85;
    if (ufw<200) return  91;
    if (ufw<300) return  94;
    if (ufw<400) return  97;
    if (ufw<500) return 100;
    if (ufw<600) return 103;
    if (ufw<700) return 106;
    if (ufw<800) return 109;
    if (ufw<900) return 112;
    return 115;
}


template<typename StringType>
struct FontSimpleParamsT
{
    typedef typename StringType /* ::value_type */   string_type   ;
    typedef typename DrawCoord::value_type           font_height_t ;

    FontWeight        fontWeight       = FontWeight::normal;
    FontStyleFlags    fontStyleFlags   = FontStyleFlags::normal;
    StringType        fontFace         ; // = "Arial";

};



template<typename StringType>
struct FontParamsT
{

    typedef typename StringType /* ::value_type */   string_type   ;
    typedef typename DrawCoord::value_type           font_height_t ;

    DrawCoord::value_type  height         = (font_height_t)10;
    int                    escapement     =  0;
    int                    orientation    =  0;
    FontWeight             weight         = FontWeight::normal;
    //int                    fontStyleFlags =  0;
    FontStyleFlags         fontStyleFlags =  FontStyleFlags::normal;
    StringType             fontFace       ; // "Courier";

    int                    monospaceFontCharWidth = -1; // -1 - unknown, 0 - non-monospace, >0 - monospace
    int                    proportionalFontScale  = -1; // -1 - unknown - cached scale value for proportional fonts


    FontParamsT() = default;
    FontParamsT( const FontParamsT &) = default;
    FontParamsT( FontParamsT &&)      = default;
    FontParamsT& operator=( const FontParamsT &) = default;


    FontParamsT(const FontSimpleParamsT<StringType> &fsp)
    : height((font_height_t)10)
    , escapement(0)
    , orientation(0)
    , weight(fsp.weight)
    , fontStyleFlags(fsp.fontStyleFlags)
    , fontFace(fsp.fontFace)
    , monospaceFontCharWidth(fsp.monospaceFontCharWidth)
    , proportionalFontScale (fsp.proportionalFontScale)
    {}

    FontParamsT(const FontSimpleParamsT<StringType> &fsp, DrawCoord::value_type fontHeight)
    : height(fontHeight)
    , escapement(0)
    , orientation(0)
    , weight(fsp.weight)
    , fontStyleFlags(fsp.fontStyleFlags)
    , fontFace(fsp.fontFace)
    , monospaceFontCharWidth(fsp.monospaceFontCharWidth)
    , proportionalFontScale (fsp.proportionalFontScale)
    {}


    FontParamsT( DrawCoord::value_type _height, int _escapement, int _orientation, FontWeight _weight, FontStyleFlags _fontStyleFlags )
        : height(_height), escapement(_escapement), orientation(_orientation), weight(_weight), fontStyleFlags(_fontStyleFlags) {}
    FontParamsT( DrawCoord::value_type _height, int _escapement, int _orientation, FontWeight _weight, FontStyleFlags _fontStyleFlags, const StringType &_fontFace )
        : height(_height), escapement(_escapement), orientation(_orientation), weight(_weight), fontStyleFlags(_fontStyleFlags), fontFace(_fontFace) {}
    FontParamsT( DrawCoord::value_type _height, int _escapement, int _orientation, FontWeight _weight, FontStyleFlags _fontStyleFlags, const typename StringType::value_type *_fontFace )
        : height(_height), escapement(_escapement), orientation(_orientation), weight(_weight), fontStyleFlags(_fontStyleFlags), fontFace(_fontFace) {}

    FontParamsT( const FontParamsT &fp, const StringType &_fontFace )
        : height(fp.height), escapement(fp.escapement), orientation(fp.orientation), weight(fp.weight), fontStyleFlags(fp.fontStyleFlags), fontFace(fp.fontFace), monospaceFontCharWidth(fp.monospaceFontCharWidth), proportionalFontScale (fp.proportionalFontScale) {}
    FontParamsT( const FontParamsT &fp, const typename StringType::value_type *_fontFace )
        : height(fp.height), escapement(fp.escapement), orientation(fp.orientation), weight(fp.weight), fontStyleFlags(fp.fontStyleFlags), fontFace(fp.fontFace), monospaceFontCharWidth(fp.monospaceFontCharWidth), proportionalFontScale (fp.proportionalFontScale) {}


    bool operator<(const FontParamsT<StringType> &other) const
    {
        if (height         < other.height        ) return true ;
        if (height         > other.height        ) return false;

        if (escapement     < other.escapement    ) return true ;
        if (escapement     > other.escapement    ) return false;

        if (orientation    < other.orientation   ) return true ;
        if (orientation    > other.orientation   ) return false;

        if (weight         < other.weight        ) return true ;
        if (weight         > other.weight        ) return false;

        if (fontStyleFlags < other.fontStyleFlags) return true ;
        if (fontStyleFlags > other.fontStyleFlags) return false;

        if (fontFace       < other.fontFace      ) return true ;
        if (fontFace       > other.fontFace      ) return false;

        return false;
    }

    bool operator>(const FontParamsT<StringType> &other) const
    {
        if (height         > other.height        ) return true ;
        if (height         < other.height        ) return false;

        if (escapement     > other.escapement    ) return true ;
        if (escapement     < other.escapement    ) return false;

        if (orientation    > other.orientation   ) return true ;
        if (orientation    < other.orientation   ) return false;

        if (weight         > other.weight        ) return true ;
        if (weight         < other.weight        ) return false;

        if (fontStyleFlags > other.fontStyleFlags) return true ;
        if (fontStyleFlags < other.fontStyleFlags) return false;

        if (fontFace       > other.fontFace      ) return true ;
        if (fontFace       < other.fontFace      ) return false;

        return false;
    }

};

typedef FontParamsT<std::string >   FontParamsA;
typedef FontParamsT<std::wstring>   FontParamsW;


struct SimpleFontMetrics
{
    DrawCoord::value_type      height  ; //!< The height (ascent + descent) of characters.
    DrawCoord::value_type      ascent  ; //!< The ascent (units above the base line) of characters.
    DrawCoord::value_type      descent ; //!< The descent (units below the base line) of characters.
    DrawCoord::value_type      overhang; //!< The extra width per string that may be added to some synthesized fonts.
};



// enum class SmoothingMode
// {
//     invalid              = -1,
//     defMode              =  0,
//  
//     highSpeed            =  1,
//     lowQuality           =  1,
//  
//     highQuality          =  2,
//     lowSpeed             =  2,
//  
//     none                 =  3,
//  
//     antiAlias            =  4,
//  
// };




struct PenParamsWithColor;

struct PenParams
{
    DrawCoord::value_type      width  ;
    LineEndcapStyle            endcaps;
    LineJoinStyle              join   ;

    PenParams() : width((DrawCoord::value_type)1), endcaps(LineEndcapStyle::round), join(LineJoinStyle::bevel) {}
    PenParams( DrawCoord::value_type w, LineEndcapStyle ec, LineJoinStyle j ) : width(w), endcaps(ec), join(j) {}
    PenParams( const PenParams &) = default;
    PenParams( PenParams &&)      = default;
    PenParams& operator=( const PenParams &) = default;

    PenParams( const PenParamsWithColor &ppc );

};

struct PenParamsWithColor
{
    DrawCoord::value_type      width;
    LineEndcapStyle            endcaps;
    LineJoinStyle              join;
    ColorRef                   color;

    PenParamsWithColor() : width((DrawCoord::value_type)1), endcaps(LineEndcapStyle::round), join(LineJoinStyle::bevel), color() {}
    PenParamsWithColor( DrawCoord::value_type w, LineEndcapStyle ec, LineJoinStyle j, ColorRef c) : width(w), endcaps(ec), join(j), color(c) {}
    PenParamsWithColor( const PenParamsWithColor &) = default;
    PenParamsWithColor( PenParamsWithColor &&)      = default;
    PenParamsWithColor& operator=( const PenParamsWithColor &) = default;

    PenParamsWithColor( const PenParams &pp, ColorRef c ) : width(pp.width), endcaps(pp.endcaps), join(pp.join), color(c) {}

    bool operator<(const PenParamsWithColor &other) const
    {
        if ((unsigned)endcaps<(unsigned)other.endcaps)
            return true;
        if ((unsigned)endcaps>(unsigned)other.endcaps)
            return false;

        if ((unsigned)join<(unsigned)other.join)
            return true;
        if ((unsigned)join>(unsigned)other.join)
            return false;

        if (color<other.color)
            return true;
        if (color>other.color)
            return false;

        if (width<other.width)
            return true;

        return false;
    }

};



inline
PenParams::PenParams( const PenParamsWithColor &ppc )
    : width  (ppc.width  )
    , endcaps(ppc.endcaps)
    , join   (ppc.join   )
{
}




inline
LineType detectLineType( const DrawCoord &p1, const DrawCoord &p2 )
{
    if (p1.x==p2.x)
        return LineType::vertical;
    else if (p1.y==p2.y)
        return LineType::horizontal;
    return LineType::diagonal;
}

inline
bool isLineTypeVH( LineType lt )
{
    switch(lt)
    {
        case LineType::vertical: case LineType::horizontal: return true;
        case LineType::diagonal: [[fallthrough]];
        case LineType::invalid : [[fallthrough]];
        default: return false;
    }
}


inline
DrawCoord::value_type getVhLineLen( const DrawCoord &p1, const DrawCoord &p2, LineType lt )
{
    DrawCoord::value_type l = DrawCoord::value_type(0);
    switch(lt)
    {
        case LineType::vertical  : l = p1.y-p2.y; break;
        case LineType::horizontal: l = p1.x-p2.x; break;
        case LineType::diagonal  : [[fallthrough]];
        case LineType::invalid   : [[fallthrough]];
        default: {}
    }

    if (l<0)
        l = -l;

    return l;
}

inline
LineDirection getVhLineDirection( const DrawCoord &sp, const DrawCoord &ep, LineType lt, DrawCoord::value_type *pOutLen = 0 )
{
    DrawCoord::value_type l = DrawCoord::value_type(0);
    switch(lt)
    {
        case LineType::vertical  : l = ep.y-sp.y; break;
        case LineType::horizontal: l = ep.x-sp.x; break;
        case LineType::diagonal  : [[fallthrough]];
        case LineType::invalid   : [[fallthrough]];
        default: {}
        //default: //DrawCoord(0);
    }

    if (l<0) // конец левее/выше начала
    {
        if (pOutLen)
           *pOutLen = -l;
        return LineDirection::fromRightToLeft; // fromBottomToTop = fromRightToLeft
    }
    else
    {
        if (pOutLen)
           *pOutLen = l;
        return LineDirection::fromLeftToRight; // fromTopToBottom = fromLeftToRight
    }
}


inline
DrawCoord::value_type getVhLineLen( const DrawCoord &p1, const DrawCoord &p2 )
{
    return getVhLineLen( p1, p2, detectLineType(p1,p2) );
}

inline
bool extractCoordVals( const DrawCoord &p1, const DrawCoord &p2, LineType lt
                     , DrawCoord::value_type &coordCommon, DrawCoord::value_type &coordStart, DrawCoord::value_type &coordEnd
                     )
{
    switch(lt)
    {
        case LineType::vertical  :
             coordCommon = p1.x;
             coordStart  = p1.y;
             coordEnd    = p2.y;
             break;
        case LineType::horizontal:
             coordCommon = p1.y;
             coordStart  = p1.x;
             coordEnd    = p2.x;
             break;

        case LineType::diagonal: [[fallthrough]];
        case LineType::invalid : [[fallthrough]];

        default:
             coordCommon = 0;
             coordStart  = 0;
             coordEnd    = 0;
             return false;
    }

    return true;
}

inline
bool extractCoordVals( const DrawCoord &p1, const DrawCoord &p2
                     , DrawCoord::value_type &coordCommon, DrawCoord::value_type &coordStart, DrawCoord::value_type &coordEnd
                     )
{
    return extractCoordVals( p1, p2, detectLineType(p1,p2), coordCommon, coordStart, coordEnd );
}

inline
bool makeCoordsFromVals( const DrawCoord::value_type coordCommon, const DrawCoord::value_type coordStart, const DrawCoord::value_type coordEnd
                       , DrawCoord &p1, DrawCoord &p2, LineType lt
                       )
{
    switch(lt)
    {
        case LineType::vertical  :
             p1.x = coordCommon;
             p1.y = coordStart ;
             p2.x = coordCommon;
             p2.y = coordEnd   ;
             break;
        case LineType::horizontal:
             p1.x = coordStart ;
             p1.y = coordCommon;
             p2.x = coordEnd   ;
             p2.y = coordCommon;
             break;

        case LineType::diagonal: [[fallthrough]];
        case LineType::invalid : [[fallthrough]];

        default:
             return false;
    }

    return true;

}

inline
bool adjustRoundedCornerLinesLen( DrawCoord             &s1
                                , DrawCoord             &e1
                                , LineType              lt1
                                , DrawCoord::value_type len1
                                , DrawCoord &s2
                                , DrawCoord &e2
                                , LineType  lt2
                                , DrawCoord::value_type len2
                                , DrawCoord::value_type dblR
                                , DrawCoord::value_type &cornersR // IN - taken radius, OUT - calculated radius
                                )
{
    if (lt1==lt2)
        return true; // no need to adjust

    // DrawCoord::value_type len1 = getVhLineLen( s1, e1, lt1 );
    // DrawCoord::value_type len2 = getVhLineLen( s2, e2, lt2 );

    DrawCoord::value_type minLen = std::min(len1,len2);

    //DrawCoord::value_type r = cornersR;
    if (dblR>minLen)
        cornersR = minLen/2;

    //---

    {
        DrawCoord::value_type coordCommon1, coordS1, coordE1;
        if (!extractCoordVals( s1, e1, lt1, coordCommon1, coordS1, coordE1 ))
            return false;

        // первую линию - укоротить в конце; vertical
        if (coordS1<coordE1  /* && lt1==LineType::horizontal */ ) // линия - слева направо (сверху вниз)
        {
            coordE1 -= cornersR;
        }
        else
        {
            coordE1 += cornersR;
        }

        makeCoordsFromVals( coordCommon1, coordS1, coordE1, s1, e1, lt1 );
    }

    //---

    {
        DrawCoord::value_type coordCommon2, coordS2, coordE2;
        if (!extractCoordVals( s2, e2, lt2, coordCommon2, coordS2, coordE2 ))
            return false;

        // вторую линию - укоротить в начале
        if (coordS2<coordE2) // линия - слева направо (сверху вниз)
        {
            coordS2 += cornersR;
        }
        else
        {
            coordS2 -= cornersR;
        }

        makeCoordsFromVals( coordCommon2, coordS2, coordE2, s2, e2, lt2 );
    }

    //---

    return true;

}


struct DcResourcesState
{
    int         nPens      = 0;
    int         penId      = 0;
    int         nBrushes   = 0;
    int         brushId    = 0;
    int         nFonts     = 0;
    int         fontId     = 0;

    ColorRef    textColor;
    ColorRef    bkColor  ;

};


struct DcOffsetScale
{
    DrawCoord              offset;
    DrawCoord              scale ;

    DrawCoord::value_type  penScale;
};



struct KerningPair
{
    std::uint32_t            chFirst   ;
    std::uint32_t            chSecond  ;
    DrawCoord::value_type    kernAmount;

    bool operator==( const KerningPair &kp ) const
    {
        return chFirst==kp.chFirst && chSecond==kp.chSecond;
    }

    bool operator!=( const KerningPair &kp ) const
    {
        return chFirst!=kp.chFirst || chSecond!=kp.chSecond;
    }

};




} // namespace marty_draw_context










namespace std {

template <>
struct hash<marty_draw_context::DrawCoord>
{
    std::size_t operator()(const marty_draw_context::DrawCoord& c) const
    {
        std::size_t seed = marty_draw_context::hash_combine(0,c.x);
        return marty_draw_context::hash_combine(seed,c.y);
    }
};


template <>
struct hash<marty_draw_context::ColorRef>
{
    std::size_t operator()(const marty_draw_context::ColorRef& c) const
    {
        return marty_draw_context::hash_combine(0,c.toUnsigned());
    }
};


template <>
struct hash<marty_draw_context::PenParamsWithColor>
{
    std::size_t operator()(const marty_draw_context::PenParamsWithColor& pp) const
    {
        std::size_t seed = marty_draw_context::hash_combine(0,pp.width);
        seed = marty_draw_context::hash_combine( seed, pp.endcaps );
        seed = marty_draw_context::hash_combine( seed, pp.join );
        return marty_draw_context::hash_combine( seed, pp.color );
    }
};


template <>
struct hash<marty_draw_context::KerningPair>
{
    std::size_t operator()(const marty_draw_context::KerningPair& kp) const
    {
        std::size_t seed = marty_draw_context::hash_combine(0,kp.chFirst);
        return marty_draw_context::hash_combine(seed,kp.chSecond);
    }
};




} // namespace std



