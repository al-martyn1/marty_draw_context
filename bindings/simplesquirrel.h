/*! \file
    \brief Squirrel bindings for marty_draw_context types and interfaces (using al-martyn1/simplesquirrel)
*/

#pragma once


#include <simplesquirrel/simplesquirrel.hpp>

#include <cstdint>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
#include <algorithm>

// 
#include "../colorref.h"
#include "../draw_context_enums.h"
#include "../draw_context_types.h"
#include "../i_draw_context.h"


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/*! \def MARTY_DC_BIND_SQUIRREL_ASSERT(expr)
    Проверка условия и аварийный выход (или сообщение с последующим продолжением работы).

    При компиляции под Qt или Win32 будут вызваны соответствующие функции Qt/Windows, отображающие диалог с сообщением об ошибке.

    При компиляции для железа и работе под отладчиком последний должен показать место, где произошел assert.
    \note Не факт что это всегда работает.
*/

#if defined(Q_ASSERT)

    #define MARTY_DC_BIND_SQUIRREL_ASSERT( statement )         Q_ASSERT(statement)

#elif defined(WIN32) || defined(_WIN32)

    #include <winsock2.h>
    #include <windows.h>
    #include <crtdbg.h>

    #define MARTY_DC_BIND_SQUIRREL_ASSERT( statement )         _ASSERTE(statement)

#else

    #include <cassert>

    #define MARTY_DC_BIND_SQUIRREL_ASSERT( statement )         assert(condition) 

#endif


//------------------------------
//! MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL срабатывает всегда, и ставится туда, куда, по идее, никогда попадать не должны
#define MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL()                        MARTY_DC_BIND_SQUIRREL_ASSERT( 0 )

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

// marty_draw_context::simplesquirrel::
namespace marty_draw_context {

namespace simplesquirrel {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace utils {

//------------------------------
inline
std::string to_ascii(const char* str)
{
    return str ? std::string(str) : std::string();
}

//------------------------------
inline
std::string to_ascii(const std::string &str)
{
    return str;
}

//------------------------------
inline
std::string to_ascii(const std::wstring &str)
{
    std::string strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (char)(unsigned char)ch);
    return strRes;
}

//------------------------------
inline
std::string to_ascii(const wchar_t* str)
{
    return str ? to_ascii(std::wstring(str)) : std::string();
}

//------------------------------
struct CToAscii
{
    std::string operator()(const char* str) const
    {
        return to_ascii(str);
    }

    std::string operator()(const std::string &str) const
    {
        return to_ascii(str);
    }

    std::string operator()(const std::wstring &str) const
    {
        return to_ascii(str);
    }

    std::string operator()(const wchar_t* str) const
    {
        return to_ascii(str);
    }

    std::string operator()() const
    {
    }

}; // struct CToAscii

//------------------------------



//------------------------------
inline
std::wstring to_wide(const wchar_t* str)
{
    return str ? std::wstring(str) : std::wstring();
}

//------------------------------
inline
std::wstring to_wide(const std::wstring &str)
{
    return str;
}

//------------------------------
inline
std::wstring to_wide(const std::string &str)
{
    std::wstring strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (wchar_t)ch);
    return strRes;
}

//------------------------------
inline
std::wstring to_wide(const char* str)
{
    return str ? to_wide(std::string(str)) : std::wstring();
}

//------------------------------
struct CToWide
{
    std::wstring operator()(const wchar_t* str) const
    {
        return to_wide(str);
    }

    std::wstring operator()(const std::wstring &str) const
    {
        return to_wide(str);
    }

    std::wstring operator()(const std::string &str) const
    {
        return to_wide(str);
    }

    std::wstring operator()(const char* str) const
    {
        return to_wide(str);
    }

}; // struct CToWide

//------------------------------



//------------------------------
#if !defined(SQUNICODE)

    template<typename CharType>
    inline std::string to_sqstring(const CharType* pStr)
    {
        return to_ascii(pStr);
    }

    template<typename StringType>
    inline std::string to_sqstring(const StringType &str)
    {
        return to_ascii(str);
    }

#else

    template<typename CharType>
    inline std::wstring to_sqstring(const CharType* pStr)
    {
        return to_wide(pStr);
    }

    template<typename StringType>
    inline std::wstring to_sqstring(const StringType &str)
    {
        return to_wide(str);
    }

#endif

//------------------------------




} // namespace utils

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template<typename TargetType> inline
TargetType fromObjectConvertHelper(ssq::Object &o, const SQChar *paramName)
{
    MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL(); // not implemented for generic type
}

//----------------------------------------------------------------------------
template<> inline
float fromObjectConvertHelper<float>(ssq::Object &o, const SQChar *paramName)
{
    (void)paramName;

    if (o.isNull() || o.isEmpty())
    {
        return 0.0;
    }

    ssq::Type t = o.getType();
    switch(t)
    {
        case ssq::Type::INTEGER:
            return (float)o.toInt();

        case ssq::Type::FLOAT:
            return o.toFloat();

        case ssq::Type::STRING:
            {
                auto str = o.toString();
                try
                {
                    return std::stof(str);
                }
                catch(const std::invalid_argument &)
                {
                    throw ssq::TypeException("invalid argument", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                }
                catch(const std::out_of_range &)
                {
                    throw ssq::TypeException("out of range", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                }
                catch(...)
                {
                    throw ssq::TypeException("unknown error", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                }
            }

        case ssq::Type::BOOL:
        case ssq::Type::NULLPTR:
        case ssq::Type::TABLE:
        case ssq::Type::ARRAY:
        case ssq::Type::USERDATA:
        case ssq::Type::CLOSURE:
        case ssq::Type::NATIVECLOSURE:
        case ssq::Type::GENERATOR:
        case ssq::Type::USERPOINTER:
        case ssq::Type::THREAD:
        case ssq::Type::FUNCPROTO:
        case ssq::Type::CLASS:
        case ssq::Type::INSTANCE:
        case ssq::Type::WEAKREF:
        case ssq::Type::OUTER:
            [[fallthrough]];		
        default: {}
    }

    throw ssq::TypeException("bad cast", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));

}

//----------------------------------------------------------------------------
template<> inline
int fromObjectConvertHelper<int>(ssq::Object &o, const SQChar *paramName)
{
    (void)paramName;

    if (o.isNull() || o.isEmpty())
    {
        return 0;
    }

    ssq::Type t = o.getType();
    switch(t)
    {
        case ssq::Type::INTEGER:
            return (int)o.toInt();

        case ssq::Type::FLOAT:
            {
                float f = o.toFloat();
                return (int)(f+0.5);
            }

        case ssq::Type::STRING:
            {
                auto str = o.toString();
                try
                {
                    return std::stoi(str);
                }
                catch(const std::invalid_argument &)
                {
                    throw ssq::TypeException("invalid argument", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                }
                catch(const std::out_of_range &)
                {
                    throw ssq::TypeException("out of range", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                }
                catch(...)
                {
                    throw ssq::TypeException("unknown error", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                }
            }

        case ssq::Type::BOOL:
        case ssq::Type::NULLPTR:
        case ssq::Type::TABLE:
        case ssq::Type::ARRAY:
        case ssq::Type::USERDATA:
        case ssq::Type::CLOSURE:
        case ssq::Type::NATIVECLOSURE:
        case ssq::Type::GENERATOR:
        case ssq::Type::USERPOINTER:
        case ssq::Type::THREAD:
        case ssq::Type::FUNCPROTO:
        case ssq::Type::CLASS:
        case ssq::Type::INSTANCE:
        case ssq::Type::WEAKREF:
        case ssq::Type::OUTER:
            [[fallthrough]];		
        default: {}
    }

    throw ssq::TypeException("bad cast", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));

}

//----------------------------------------------------------------------------
template<> inline
ssq::sqstring fromObjectConvertHelper<ssq::sqstring>(ssq::Object &o, const SQChar *paramName)
{
    (void)paramName;

    if (o.isNull() || o.isEmpty())
    {
        return 0;
    }

    ssq::Type t = o.getType();
    switch(t)
    {
        case ssq::Type::INTEGER:
            return utils::to_sqstring(std::to_string(o.toInt()));

        case ssq::Type::FLOAT:
            return utils::to_sqstring(std::to_string(o.toFloat()));

        case ssq::Type::STRING:
            return o.toString();

        case ssq::Type::BOOL:
        case ssq::Type::NULLPTR:
        case ssq::Type::TABLE:
        case ssq::Type::ARRAY:
        case ssq::Type::USERDATA:
        case ssq::Type::CLOSURE:
        case ssq::Type::NATIVECLOSURE:
        case ssq::Type::GENERATOR:
        case ssq::Type::USERPOINTER:
        case ssq::Type::THREAD:
        case ssq::Type::FUNCPROTO:
        case ssq::Type::CLASS:
        case ssq::Type::INSTANCE:
        case ssq::Type::WEAKREF:
        case ssq::Type::OUTER:
            [[fallthrough]];		
        default: {}
    }

    throw ssq::TypeException("bad cast", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));

}





//----------------------------------------------------------------------------
struct DrawingColor : public ColorRef
{

    DrawingColor() : ColorRef() {}

    DrawingColor(ColorRef clr) : ColorRef(clr) {}
    DrawingColor(const DrawingColor &clr) : ColorRef(clr) {}
    DrawingColor(DrawingColor &&clr)      : ColorRef(clr) {}

    DrawingColor& operator=(ColorRef clr)
    {
        r = clr.r;
        g = clr.g;
        b = clr.b;
        a = clr.a;
        return *this;
    }

    DrawingColor& operator=(const DrawingColor &clr) = default;
    DrawingColor& operator=(DrawingColor &&clr) = default;


    operator marty_draw_context::ColorRef() const
    {
        return (ColorRef)*this;
    }

    static
    DrawingColor fromString(const ssq::Class&, const ssq::sqstring &colorName)
    {
        try
        {
            #if !defined(SQUNICODE)

                return (DrawingColor)ColorRef::deserialize(colorName);

            #else

                std::string colorNameAscii = utils::to_ascii(colorName);
                return (DrawingColor)ColorRef::deserialize(colorNameAscii);

            #endif
        }
        catch(...)
        {
        }

        return DrawingColor();
    }

    static
    DrawingColor fromUnsignedBindHelper( const ssq::Class&, std::uint32_t uclr )
    {
        return (DrawingColor)ColorRef::fromUnsigned(uclr);
    }

    static
    DrawingColor fromIntBindHelper( const ssq::Class&, int iclr )
    {
        return (DrawingColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)iclr);
    }

    int toIntBindHelper() const
    {
        return (int)(std::int32_t)toUnsigned();
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Color"))
    {
        const bool staticMethod = true ;
        //const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , [](ssq::Object o) -> DrawingColor*
                                {
                                    if (o.isNull() || o.isEmpty())
                                    {
                                        return new DrawingColor();
                                    }

                                    ssq::Type t = o.getType();
                                    switch(t)
                                    {
                                        case ssq::Type::INTEGER:
                                            return new DrawingColor((DrawingColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)o.toInt()));
                                
                                        case ssq::Type::FLOAT:
                                            return new DrawingColor((DrawingColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)(0.5+o.toFloat())));
                                
                                        case ssq::Type::STRING:
                                            return new DrawingColor(fromString(ssq::Class(), o.toString()));

                                        case ssq::Type::CLASS:
                                        {
                                            auto cls = o.toClass();
                                            break;
                                        }

                                        case ssq::Type::BOOL:
                                        case ssq::Type::NULLPTR:
                                        case ssq::Type::TABLE:
                                        case ssq::Type::ARRAY:
                                        case ssq::Type::USERDATA:
                                        case ssq::Type::CLOSURE:
                                        case ssq::Type::NATIVECLOSURE:
                                        case ssq::Type::GENERATOR:
                                        case ssq::Type::USERPOINTER:
                                        case ssq::Type::THREAD:
                                        case ssq::Type::FUNCPROTO:
                                        case ssq::Type::INSTANCE:
                                        case ssq::Type::WEAKREF:
                                        case ssq::Type::OUTER:
                                            [[fallthrough]];		
                                        default: {}
                                    }

                                    return new DrawingColor();
                                }
                              , true // release
                              );

        cls.addFunc( _SC("toUnsigned")  , &DrawingColor::toUnsigned);
        cls.addFunc( _SC("fromUnsigned"), &DrawingColor::fromUnsignedBindHelper);

        cls.addFunc( _SC("toInt")       , &DrawingColor::toIntBindHelper);
        cls.addFunc( _SC("fromInt")     , &DrawingColor::fromIntBindHelper, staticMethod);

        cls.addFunc( _SC("fromString")  , &DrawingColor::fromString);
        cls.addFunc( _SC("toString")
                   , [](DrawingColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                         return utils::to_sqstring(self->serialize());
                     }
                   );


        cls.addVar(_SC("r")     , &DrawingColor::r);
        cls.addVar(_SC("g")     , &DrawingColor::g);
        cls.addVar(_SC("b")     , &DrawingColor::b);
        cls.addVar(_SC("a")     , &DrawingColor::a);


        // алиасы с динными именами для r/g/b
        // может, не делать с длинными именами?
        // может, стоит сделать кучу статиков-алисов для именованных цветов?

        // Пока не буду добавлять
        // cls.addVar(_SC("red")   , &DrawingColor::r);
        // cls.addVar(_SC("green") , &DrawingColor::g);
        // cls.addVar(_SC("blue")  , &DrawingColor::b);
        // cls.addVar(_SC("alpha") , &DrawingColor::a);

        return cls;
    }


}; // struct DrawingColor

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawingCoords
{
    float x;
    float y;

    DrawingCoords() : x(0.0), y(0.0) {}
    DrawingCoords(float x_, float y_) : x(x_), y(y_) {}
    DrawingCoords(const DrawCoord &c) : x(floatToFloat(c.x)), y(floatToFloat(c.y)) {}
    DrawingCoords(const DrawingCoords &c) : x(c.x), y(c.y) {}
    DrawingCoords(DrawingCoords&&) = default;

    DrawingCoords& operator=(const DrawingCoords &c) = default;
    DrawingCoords& operator=(DrawingCoords &&) = default;

    DrawingCoords& operator=(const DrawCoord &c)
    {
        x = floatToFloat(c.x);
        y = floatToFloat(c.y);
        return *this;
    }

    operator marty_draw_context::DrawCoord() const
    {
        marty_draw_context::DrawCoord res;
        res.x = (marty_draw_context::DrawCoord::value_type)x;
        res.y = (marty_draw_context::DrawCoord::value_type)y;
        return res;
    }


    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Coords"))
    {
        // const bool staticMethod = true ;
        // const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object ox, ssq::Object oy  /* float x, float y */  ) -> DrawingCoords*
                                {
                                    return new DrawingCoords{fromObjectConvertHelper<float>(ox, _SC("x")), fromObjectConvertHelper<float>(oy, _SC("y"))};
                                }
                              , true // release
                              );

        cls.addVar(_SC("x"), &DrawingCoords::x);
        cls.addVar(_SC("y"), &DrawingCoords::y);

        return cls;
    }

}; // struct DrawingCoords

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
struct DrawingFontParams
{
    float                  height         = 10.0;
    int                    escapement     = 0;
    int                    orientation    = 0;
    int                    weight         = 400;
    int                    fontStyleFlags = 0;
    ssq::sqstring          fontFace       = _SC("Courier");

    DrawingFontParams() {}

    DrawingFontParams(float h, int e, int o, int w, int fsf, const ssq::sqstring &fface)
    : height        (h)
    , escapement    (e)
    , orientation   (o)
    , weight        (w)
    , fontStyleFlags(fsf)
    , fontFace      (fface)
    {}

    DrawingFontParams(const FontParamsT<ssq::sqstring> &fp)
    : height        (floatToFloat(fp.height))
    , escapement    (fp.escapement )
    , orientation   (fp.orientation)
    , weight        ((int)fp.weight)
    , fontStyleFlags((int)fp.fontStyleFlags)
    , fontFace      (fp.fontFace)
    {}

    DrawingFontParams(const DrawingFontParams&) = default;
    DrawingFontParams(DrawingFontParams&&) = default;


    operator marty_draw_context::FontParamsT<ssq::sqstring>() const
    {
        marty_draw_context::FontParamsT<ssq::sqstring> fpRes;

        fpRes.height          = (DrawCoord::value_type)height;
        fpRes.escapement      = escapement ;
        fpRes.orientation     = orientation;
        fpRes.weight          = (FontWeight)weight;
        fpRes.fontStyleFlags  = (FontStyleFlags)fontStyleFlags;
        fpRes.fontFace        = fontFace;
        //fpRes.

        return fpRes;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("FontParams"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object h, ssq::Object w, ssq::Object style, ssq::Object face )
                                {
                                    float         height_         = fromObjectConvertHelper<float>(h, _SC("height"));
                                    // int           escapement     = 0;
                                    // int           orientation    = 0;
                                    int           weight_         = fromObjectConvertHelper<int>(w, _SC("weight"));
                                    int           fontStyleFlags_ = fromObjectConvertHelper<int>(style, _SC("style"));
                                    ssq::sqstring fontFace_       = fromObjectConvertHelper<ssq::sqstring>(face , _SC("face"));

                                    return new DrawingFontParams(height_, 0, 0, weight_, fontStyleFlags_, fontFace_);
                                }
                              , true // release
                              );

        //auto cls = vm.addClass( className.c_str(), []() { return new DrawingFontParams(); }, true /* release */ );

        cls.addVar(_SC("height")             , &DrawingFontParams::height        );
        //cls.addVar(_SC("escapement")         , &DrawingFontParams::escapement    );
        //cls.addVar(_SC("orientation")        , &DrawingFontParams::orientation   );
        cls.addVar(_SC("weight")             , &DrawingFontParams::weight        );
        cls.addVar(_SC("fontStyleFlags")     , &DrawingFontParams::fontStyleFlags);
        cls.addVar(_SC("fontFace")           , &DrawingFontParams::fontFace      );

        return cls;
    }

    //ssq::sqstring fromObjectConvertHelper<ssq::sqstring>(ssq::Object &o, const SQChar *paramName)

}; // struct DrawingFontParams

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawingGradientParams
{
    DrawingColor     colorBegin;
    DrawingColor     colorMid  ;
    DrawingColor     colorEnd  ;

    float         midPoint  = (DrawCoord::value_type)0.5;

    operator marty_draw_context::GradientParams() const
    {
        marty_draw_context::GradientParams gpRes;
        gpRes.colorBegin = colorBegin;
        gpRes.colorMid   = colorMid  ;
        gpRes.colorEnd   = colorEnd  ;
        gpRes.midPoint   = (marty_draw_context::DrawCoord::value_type)midPoint;

        return gpRes;
    }
    

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("GradientParams"))
    {
        auto cls = vm.addClass( className.c_str(), []() { return new DrawingGradientParams(); }, true /* release */ );

        cls.addVar(_SC("colorBegin") , &DrawingGradientParams::colorBegin );
        cls.addVar(_SC("colorMid")   , &DrawingGradientParams::colorMid   );
        cls.addVar(_SC("colorEnd")   , &DrawingGradientParams::colorEnd   );
        cls.addVar(_SC("midPoint")   , &DrawingGradientParams::midPoint   );

        return cls;
    }

}; // struct DrawingGradientParams

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawingPenParams
{
    float         width  ;
    int           endcaps;
    int           join   ;

    operator marty_draw_context::PenParams() const
    {
        marty_draw_context::PenParams pp;
        pp.width   = (marty_draw_context::DrawCoord::value_type)width  ;
        pp.endcaps = (LineEndcapStyle)endcaps;
        pp.join    = (LineJoinStyle)join   ;
        return pp;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("PenParams"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object w, ssq::Object ecaps, ssq::Object j )
                                {
                                    float         width_     = fromObjectConvertHelper<float>(w, _SC("width"));
                                    int           endcaps_   = fromObjectConvertHelper<int>(ecaps, _SC("endcaps"));
                                    int           join_      = fromObjectConvertHelper<int>(j, _SC("join"));

                                    return new DrawingPenParams{width_, endcaps_, join_ };
                                }
                              , true // release
                              );


        // auto cls = vm.addClass( className.c_str(), []() { return new DrawingPenParams(); }, true /* release */ );

        cls.addVar(_SC("width")   , &DrawingPenParams::width   );
        cls.addVar(_SC("endcaps") , &DrawingPenParams::endcaps );
        cls.addVar(_SC("join")    , &DrawingPenParams::join    );

        return cls;
    }


}; // struct DrawingPenParams

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
struct DrawingContext
{
    IDrawContext *pDc = 0;

    DrawingContext() {}
    DrawingContext(IDrawContext *pDc_) : pDc(pDc_) {}


    bool setCollectMarkers(bool cmMode) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->setCollectMarkers(cmMode);
    }

    bool getCollectMarkers() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->getCollectMarkers();
    }

    bool markerAdd( const DrawCoord &pos ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->markerAdd(pos);
    }

    bool markerAddEx( const DrawCoord &pos, float size ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->markerAdd(pos, (DrawCoord::value_type)size);
    }

    bool markersClear() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        pDc->markersClear();
        return true;
    }

    bool markersDraw() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        pDc->markersDraw(-1);
        return true;
    }

    bool markersDrawEx(int penId) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        pDc->markersDraw(penId);
        return true;
    }

    float markerSetDefSize( float size ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return floatToFloat((pDc->markerSetDefSize((DrawCoord::value_type)size)));
    }

    float markerGetDefSize( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return floatToFloat((pDc->markerGetDefSize()));
    }


    // virtual bool setCollectMarkers( bool cmMode ) = 0;
    // virtual bool getCollectMarkers( ) = 0;
    // virtual bool markerAdd( const DrawCoord &pos, const DrawCoord::value_type sz ) = 0;
    // virtual bool markerAdd( const DrawCoord &pos ) = 0;
    // virtual void markersClear( ) = 0;
    // virtual void markersDraw( int penId ) = 0;
    //  
    // virtual DrawCoord::value_type markerSetDefSize( const DrawCoord::value_type &sz ) = 0;
    // virtual DrawCoord::value_type markerGetDefSize( ) = 0;


    int setSmoothingMode( int m ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return (int)SmoothingMode::invalid;
        return (int)pDc->setSmoothingMode((SmoothingMode)m);
    }

    int getSmoothingMode() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return (int)SmoothingMode::invalid;
        return (int)pDc->getSmoothingMode();
    }
    

    DrawingColor setTextColor(DrawingColor clr) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingColor();
        return pDc->setTextColor(clr);
    }

    DrawingColor getTextColor( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingColor();
        return pDc->getTextColor();
    }

    DrawingColor setBkColor(DrawingColor clr) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingColor();
        return pDc->setBkColor(clr);
    }

    int setBkMode(int mode) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return (int)pDc->setBkMode((BkMode)mode);
    }

    DrawingCoords getDialigBaseUnits() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->getDialigBaseUnits();
    }

    DrawingCoords mapRawToLogicPos ( DrawingCoords c ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->mapRawToLogicPos(c);
    }

    DrawingCoords mapRawToLogicSize( DrawingCoords c ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->mapRawToLogicSize(c);
    }

    DrawingCoords getScaledPos ( DrawingCoords c ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->getScaledPos(c);
    }

    DrawingCoords getScaledSize( DrawingCoords c ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->getScaledSize(c);
    }

    DrawingCoords setOffset( DrawingCoords c ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->setOffset(c);
    }

    DrawingCoords getOffset( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->getOffset();
    }

    DrawingCoords setScale( DrawingCoords c ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->setScale(c);
    }

    DrawingCoords getScale( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->getScale();
    }

    float setPenScale( ssq::Object scale ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return 0.0f;
        auto fScale = fromObjectConvertHelper<float>(scale, _SC("scale"));
        return floatToFloat(pDc->setPenScale(fScale));
    }

    float getPenScale( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return 0.0f;
        return floatToFloat(pDc->getPenScale());
    }


    int createSolidPen( DrawingPenParams penParams, DrawingColor colorRef ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->createSolidPen( penParams, colorRef );
    }

    int selectPen( int penId ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->selectPen( penId );
    }

    int selectNewSolidPen( PenParams penParams, DrawingColor colorRef ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->selectNewSolidPen( penParams, colorRef );
    }

    int getCurPen() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->getCurPen();     
    }

    ColorRef getPenColor(int penId) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return ColorRef();
        return pDc->getPenColor(penId);     
    }

    int setDefaultCosmeticPen( int penId ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->setDefaultCosmeticPen(penId);     
    }

    int getDefaultCosmeticPen( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->getDefaultCosmeticPen();     
    }


    int createSolidBrush( DrawingColor rgb ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->createSolidBrush(rgb);     
    }
    
    int selectBrush( int brushId ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->selectBrush(brushId);     
    }

    int selectNewSolidBrush( DrawingColor rgb ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->selectNewSolidBrush(rgb);     
    }

    int getCurBrush() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->getCurPen();     
    }

    //DrawingFontParams(const FontParamsT<ssq::sqstring> &fp)

    int createFont(DrawingFontParams dfp) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->createFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int createFontEx(DrawingFontParams dfp, float height) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.height = height;
        return pDc->createFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int createOrFindFont(DrawingFontParams dfp) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->makeFontByParams(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int createOrFindFontEx(DrawingFontParams dfp, float height) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.height = height;
        return pDc->makeFontByParams(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int selectFont( int fontId ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->selectFont( fontId );
    }

    int selectNewFont(DrawingFontParams dfp) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->selectNewFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int selectNewFontEx(DrawingFontParams dfp, float height) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.height = height;
        return pDc->selectNewFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int  getCurFont() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->getCurFont();
    }

    // virtual bool getFontParamsById( int id, FontParamsA &fp ) = 0;
    DrawingFontParams getFontParamsById(int id) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingFontParams();

        FontParamsT<ssq::sqstring> fp;
        pDc->getFontParamsById(id, fp);
        return static_cast<DrawingFontParams>(fp);
    }

    bool beginPath() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->beginPath();
    }

    bool beginPathFrom(DrawingCoords c) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->beginPath(c);
    }

    bool endPath( bool bStroke, bool bFill ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->endPath(bStroke, bFill);
    }

    bool closeFigure() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->closeFigure();
    }

    bool isPathStarted() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->isPathStarted();
    }


    bool moveTo( DrawingCoords to ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->moveTo(to);     
    }

    bool lineTo( DrawingCoords to ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->lineTo(to);     
    }


    bool ellipticArcTo( DrawingCoords leftTop
                      , DrawingCoords rightBottom
                      , DrawingCoords arcStartRefPoint
                      , DrawingCoords arcEndRefPoint
                      , bool          directionCounterclockwise
                      ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->ellipticArcTo(leftTop, rightBottom, arcStartRefPoint, arcEndRefPoint, directionCounterclockwise);
    }

    mutable DrawingCoords lastArcEndPos;

    DrawingCoords getLastArcEndPos() const
    {
        return lastArcEndPos;
    }

    bool arcToPos(DrawingCoords centerPos, DrawingCoords endPos, bool directionCounterclockwise) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        DrawCoord calculatedEndPos;
        bool res = pDc->arcTo(centerPos, endPos, directionCounterclockwise, &calculatedEndPos);
        if (res)
        {
            lastArcEndPos = static_cast<DrawingCoords>(calculatedEndPos);
        }

        return res;
    }

    bool arcByAngleDeg(DrawingCoords centerPos, float angle) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        DrawCoord calculatedEndPos;
        bool res = pDc->arcTo(centerPos, (DrawCoord::value_type)angle, &calculatedEndPos);
        if (res)
        {
            lastArcEndPos = calculatedEndPos;
        }

        return res;
    }

    // //! Рисует набор горизонтальных и вертикальных линий, если две точки задают диагональную линию - это ошибка
    // virtual bool roundRectFigure( const DrawCoord::value_type &cornersR
    //                             , std::size_t numPoints
    //                             , const DrawCoord             *pPoints
    //                             ) = 0;

    bool roundRect(float r, DrawingCoords leftTop, DrawingCoords rightBottom) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->roundRect((DrawCoord::value_type)r, leftTop, rightBottom);
    }

    bool rect(DrawingCoords leftTop, DrawingCoords rightBottom) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->rect(leftTop, rightBottom);
    }

    bool fillRect(DrawingCoords leftTop, DrawingCoords rightBottom) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillRect(leftTop, rightBottom);
    }

    bool fillGradientRect(DrawingCoords leftTop, DrawingCoords rightBottom, DrawingGradientParams gradientParams, int gradientType, bool excludeFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillGradientRect( leftTop, rightBottom, gradientParams.colorBegin, gradientParams.colorMid, gradientParams.colorEnd
                                    , (DrawCoord::value_type)gradientParams.midPoint, (GradientType)gradientType, excludeFrame
                                    );
    }

    bool fillGradientRoundRect( float r, DrawingCoords leftTop, DrawingCoords rightBottom, DrawingGradientParams gradientParams, int gradientType, bool excludeFrame
                              , float fillBreakPos, int fillFlags) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillGradientRoundRect( (DrawCoord::value_type)r
                                    , leftTop, rightBottom, gradientParams.colorBegin, gradientParams.colorMid, gradientParams.colorEnd
                                    , (DrawCoord::value_type)gradientParams.midPoint, (GradientType)gradientType, excludeFrame
                                    , (DrawCoord::value_type)fillBreakPos, (GradientRoundRectFillFlags)fillFlags
                                    );
    }

    bool fillGradientCircle(DrawingCoords pos, float r, DrawingGradientParams gradientParams, bool excludeFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillGradientCircle( pos, (DrawCoord::value_type)r, gradientParams.colorBegin, gradientParams.colorMid, gradientParams.colorEnd
                                    , (DrawCoord::value_type)gradientParams.midPoint, excludeFrame
                                    );
    }







    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Context"))
    {
        auto cls = vm.addClass( className.c_str(), []() { return new DrawingContext(); }, true /* release */ );

        cls.addFunc( _SC("setCollectMarkers")      , &DrawingContext::setCollectMarkers    );
        cls.addFunc( _SC("getCollectMarkers")      , &DrawingContext::getCollectMarkers    );
        cls.addFunc( _SC("markerAdd")              , &DrawingContext::markerAdd            );
        cls.addFunc( _SC("markerAddEx")            , &DrawingContext::markerAddEx          );
        cls.addFunc( _SC("markersClear")           , &DrawingContext::markersClear         );
        cls.addFunc( _SC("markersDraw")            , &DrawingContext::markersDraw          );
        cls.addFunc( _SC("markersDrawEx")          , &DrawingContext::markersDrawEx        );
        cls.addFunc( _SC("markerSetDefSize")       , &DrawingContext::markerSetDefSize     );
        cls.addFunc( _SC("markerGetDefSize")       , &DrawingContext::markerGetDefSize     );

        cls.addFunc( _SC("setSmoothingMode")       , &DrawingContext::setSmoothingMode     );
        cls.addFunc( _SC("getSmoothingMode")       , &DrawingContext::getSmoothingMode     );
        cls.addFunc( _SC("setTextColor")           , &DrawingContext::setTextColor         );
        cls.addFunc( _SC("getTextColor")           , &DrawingContext::getTextColor         );
        cls.addFunc( _SC("setBkColor")             , &DrawingContext::setBkColor           );
        //TODO: !!! Надо реализовать getBkColor
        cls.addFunc( _SC("setBkMode")              , &DrawingContext::setBkMode            );
        //TODO: !!! Надо реализовать getBkMode
        cls.addFunc( _SC("setTextColor")           , &DrawingContext::setTextColor         );
        cls.addFunc( _SC("getTextColor")           , &DrawingContext::getTextColor         );
        cls.addFunc( _SC("getDialigBaseUnits")     , &DrawingContext::getDialigBaseUnits   );
        cls.addFunc( _SC("mapRawToLogicPos")       , &DrawingContext::mapRawToLogicPos     );
        cls.addFunc( _SC("mapRawToLogicSize")      , &DrawingContext::mapRawToLogicSize    );
        cls.addFunc( _SC("getScaledPos")           , &DrawingContext::getScaledPos         );
        cls.addFunc( _SC("getScaledSize")          , &DrawingContext::getScaledSize        );
        cls.addFunc( _SC("setOffset")              , &DrawingContext::setOffset            );
        cls.addFunc( _SC("getOffset")              , &DrawingContext::getOffset            );
        cls.addFunc( _SC("setScale")               , &DrawingContext::setScale             );
        cls.addFunc( _SC("getScale")               , &DrawingContext::getScale             );
        cls.addFunc( _SC("setPenScale")            , &DrawingContext::setPenScale          );
        cls.addFunc( _SC("getPenScale")            , &DrawingContext::getPenScale          );
        cls.addFunc( _SC("createSolidPen")         , &DrawingContext::createSolidPen       );
        cls.addFunc( _SC("selectPen")              , &DrawingContext::selectPen            );
        cls.addFunc( _SC("selectNewSolidPen")      , &DrawingContext::selectNewSolidPen    );
        cls.addFunc( _SC("getCurPen")              , &DrawingContext::getCurPen            );
        cls.addFunc( _SC("getPenColor")            , &DrawingContext::getPenColor          );
        cls.addFunc( _SC("setDefaultCosmeticPen")  , &DrawingContext::setDefaultCosmeticPen);
        cls.addFunc( _SC("getDefaultCosmeticPen")  , &DrawingContext::getDefaultCosmeticPen);
        cls.addFunc( _SC("moveTo")                 , &DrawingContext::moveTo               );
        cls.addFunc( _SC("lineTo")                 , &DrawingContext::lineTo               );
        cls.addFunc( _SC("createSolidBrush")       , &DrawingContext::createSolidBrush     );
        cls.addFunc( _SC("selectBrush")            , &DrawingContext::selectBrush          );
        cls.addFunc( _SC("selectNewSolidBrush")    , &DrawingContext::selectNewSolidBrush  );
        cls.addFunc( _SC("getCurBrush")            , &DrawingContext::getCurBrush          );
        cls.addFunc( _SC("createFont")             , &DrawingContext::createFont           );
        cls.addFunc( _SC("createFontEx")           , &DrawingContext::createFontEx         );
        cls.addFunc( _SC("createOrFindFont")       , &DrawingContext::createOrFindFont     );
        cls.addFunc( _SC("createOrFindFontEx")     , &DrawingContext::createOrFindFontEx   );
        cls.addFunc( _SC("selectFont")             , &DrawingContext::selectFont           );
        cls.addFunc( _SC("selectNewFont")          , &DrawingContext::selectNewFont        );
        cls.addFunc( _SC("selectNewFontEx")        , &DrawingContext::selectNewFontEx      );
        cls.addFunc( _SC("getCurFont")             , &DrawingContext::getCurFont           );
        cls.addFunc( _SC("getFontParamsById")      , &DrawingContext::getFontParamsById    );
        cls.addFunc( _SC("beginPath")              , &DrawingContext::beginPath            );
        cls.addFunc( _SC("beginPathFrom")          , &DrawingContext::beginPathFrom        );
        cls.addFunc( _SC("endPath")                , &DrawingContext::endPath              );
        cls.addFunc( _SC("closeFigure")            , &DrawingContext::closeFigure          );
        cls.addFunc( _SC("isPathStarted")          , &DrawingContext::isPathStarted        );
        cls.addFunc( _SC("ellipticArcTo")          , &DrawingContext::ellipticArcTo        );
        cls.addFunc( _SC("getLastArcEndPos")       , &DrawingContext::getLastArcEndPos     );
        cls.addFunc( _SC("arcToPos")               , &DrawingContext::arcToPos             );
        cls.addFunc( _SC("arcByAngleDeg")          , &DrawingContext::arcByAngleDeg        );
        cls.addFunc( _SC("roundRect")              , &DrawingContext::roundRect            );
        cls.addFunc( _SC("rect")                   , &DrawingContext::rect                 );
        cls.addFunc( _SC("fillRect")               , &DrawingContext::fillRect             );
        cls.addFunc( _SC("fillGradientRect")       , &DrawingContext::fillGradientRect     );
        cls.addFunc( _SC("fillGradientRoundRect")  , &DrawingContext::fillGradientRoundRect);
        cls.addFunc( _SC("fillGradientCircle")     , &DrawingContext::fillGradientCircle   );
        //cls.addFunc( _SC("")  , &DrawingContext::);
        //cls.addFunc( _SC("")  , &DrawingContext::);
        //cls.addFunc( _SC("")  , &DrawingContext::);


        return cls;
    }

}; // struct DrawingContext


//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// https://learn.microsoft.com/ru-ru/cpp/cpp/ellipses-and-variadic-templates?view=msvc-170

inline
void makeEnumValuesVectorHelper( std::vector< std::pair<std::string, int> > &vec)
{
    (void)vec;
}

template<typename EnumVal> inline
void makeEnumValuesVectorHelper( std::vector< std::pair<std::string, int> > &vec, EnumVal val)
{
    auto strVal = enum_serialize(val);
    if (strVal.empty() || strVal=="0")
    {
        strVal = "None";
    }
    vec.emplace_back(strVal, (int)val);
}

template<typename First, typename... EnumVal> inline
void makeEnumValuesVectorHelper( std::vector< std::pair<std::string, int> > &vec, First first, EnumVal... vals)
{
    makeEnumValuesVectorHelper(vec, first);
    makeEnumValuesVectorHelper(vec, vals...);
}

template<typename... EnumVal> inline
std::vector< std::pair<std::string, int> > makeEnumValuesVector( EnumVal... vals )
{
    std::vector< std::pair<std::string, int> > vec;
    makeEnumValuesVectorHelper(vec, vals...);
    return vec;
}

template<typename First, typename... EnumVal> inline
std::vector< std::pair<std::string, int> > makeEnumValuesVector( First first, EnumVal... vals )
{
    std::vector< std::pair<std::string, int> > vec;
    makeEnumValuesVectorHelper(vec, first);
    makeEnumValuesVectorHelper(vec, vals...);
    return vec;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template<typename... EnumVal> inline
ssq::sqstring makeEnumScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
{
    known.insert(utils::to_sqstring(enumNameOnly));

    std::string enumName = enumPrefix+enumNameOnly;

    std::vector< std::pair<std::string, int> > valNameVec = makeEnumValuesVector(vals...);

    std::string res = "enum " + enumName + "{";

    for(auto p: valNameVec)
    {
        res.append(p.first);
        res.append("=");
        res.append(std::to_string(p.second));
        res.append(1, itemSep );
    }

    res.append("}");
    res.append(1, enumSep );

    return utils::to_sqstring(res);
}

//----------------------------------------------------------------------------
template<typename... EnumVal> inline
ssq::sqstring makeFlagScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
{
    known.insert(utils::to_sqstring(enumNameOnly));

    std::string enumName = enumPrefix+enumNameOnly;

    std::vector< std::pair<std::string, int> > valNameVec = makeFlagValuesVector(vals...);

    std::string res = "enum " + enumName + "{";

    for(auto p: valNameVec)
    {
        res.append(p.first);
        res.append("=");
        res.append(std::to_string(p.second));
        res.append(1, itemSep );
    }

    res.append("}");
    res.append(1, enumSep );

    return utils::to_sqstring(res);
}

//----------------------------------------------------------------------------
template<typename... EnumVal> inline
ssq::sqstring makeEnumClassScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, const std::string &itemTypeString, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
{
    //known.insert(utils::to_sqstring(enumNameOnly));
    (void)known;

    std::string enumName = enumPrefix+enumNameOnly;

    std::vector< std::pair<std::string, int> > valNameVec = makeEnumValuesVector(vals...);

    std::string res = "class " + enumName + "{";

    for(auto p: valNameVec)
    {
        res.append("static ");
        res.append(p.first);
        //res.append("<-");
        res.append("=");
        res.append(itemTypeString);
        res.append("(");
        res.append(std::to_string(p.second));
        res.append(")");
        res.append(1, itemSep );
    }

    res.append("}");
    res.append(1, enumSep );

    return utils::to_sqstring(res);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
ssq::sqstring enumsExposeMakeScript(char itemSep, char enumSep, std::set<ssq::sqstring> *pKnownEnumNames = 0, const std::string &prefix = "Drawing")
{

    // auto strVal = enum_serialize_flags(FontStyleFlags::italic);
    // //auto strVal = enum_serialize(val);
    // (void)strVal;

    std::set<ssq::sqstring> knownEnumNames;

    // ssq::sqstring makeEnumClassScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, const std::string &itemTypeString, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
    ssq::sqstring scriptText = 
                      //makeEnumScriptString( prefix, "Colors"   , itemSep, enumSep, knownEnumNames
                      makeEnumClassScriptString( prefix+".", "Colors", prefix+".Color"   , enumSep /* itemSep */ , enumSep, knownEnumNames
                                          , EColorRawEnum::AliceBlue       , EColorRawEnum::AntiqueWhite   , EColorRawEnum::Aqua             , EColorRawEnum::Aquamarine          
                                          , EColorRawEnum::Azure           , EColorRawEnum::Beige          , EColorRawEnum::Bisque           , EColorRawEnum::Black               
                                          , EColorRawEnum::BlanchedAlmond  , EColorRawEnum::Blue           , EColorRawEnum::BlueViolet       , EColorRawEnum::Brown               
                                          , EColorRawEnum::BurlyWood       , EColorRawEnum::CadetBlue      , EColorRawEnum::Chartreuse       , EColorRawEnum::Chocolate           
                                          , EColorRawEnum::Coral           , EColorRawEnum::CornflowerBlue , EColorRawEnum::Cornsilk         , EColorRawEnum::DarkCyan            
                                          , EColorRawEnum::DarkGoldenRod   , EColorRawEnum::DarkGray       , EColorRawEnum::DarkGrey         , EColorRawEnum::DarkGreen           
                                          , EColorRawEnum::DarkKhaki       , EColorRawEnum::DarkMagenta    , EColorRawEnum::DarkOliveGreen   , EColorRawEnum::DarkOrange          
                                          , EColorRawEnum::DarkOrchid      , EColorRawEnum::DarkRed        , EColorRawEnum::DarkSalmon       , EColorRawEnum::DarkSeaGreen        
                                          , EColorRawEnum::DarkSlateBlue   , EColorRawEnum::DarkSlateGray  , EColorRawEnum::DarkSlateGrey    , EColorRawEnum::DarkTurquoise       
                                          , EColorRawEnum::DarkViolet      , EColorRawEnum::DeepPink       , EColorRawEnum::DeepSkyBlue      , EColorRawEnum::DimGray             
                                          , EColorRawEnum::DimGrey         , EColorRawEnum::DodgerBlue     , EColorRawEnum::FireBrick        , EColorRawEnum::FloralWhite         
                                          , EColorRawEnum::ForestGreen     , EColorRawEnum::Fuchsia        , EColorRawEnum::Gainsboro        , EColorRawEnum::GhostWhite          
                                          , EColorRawEnum::Gold            , EColorRawEnum::GoldenRod      , EColorRawEnum::Gray             , EColorRawEnum::Grey                
                                          , EColorRawEnum::Green           , EColorRawEnum::GreenYellow    , EColorRawEnum::HoneyDew         , EColorRawEnum::HotPink             
                                          , EColorRawEnum::IndianRed       , EColorRawEnum::Indigo         , EColorRawEnum::Ivory            , EColorRawEnum::Khaki               
                                          , EColorRawEnum::Lavender        , EColorRawEnum::LavenderBlush  , EColorRawEnum::LawnGreen        , EColorRawEnum::LemonChiffon        
                                          , EColorRawEnum::LightBlue       , EColorRawEnum::LightCoral     , EColorRawEnum::LightCyan        , EColorRawEnum::LightGoldenRodYellow
                                          , EColorRawEnum::LightGray       , EColorRawEnum::LightGrey      , EColorRawEnum::LightGreen       , EColorRawEnum::LightPink           
                                          , EColorRawEnum::LightSalmon     , EColorRawEnum::LightSeaGreen  , EColorRawEnum::LightSkyBlue     , EColorRawEnum::LightSlateGray      
                                          , EColorRawEnum::LightSlateGrey  , EColorRawEnum::LightSteelBlue , EColorRawEnum::LightYellow      , EColorRawEnum::Lime                
                                          , EColorRawEnum::LimeGreen       , EColorRawEnum::Linen          , EColorRawEnum::Magenta          , EColorRawEnum::Maroon              
                                          , EColorRawEnum::MediumAquaMarine, EColorRawEnum::MediumBlue     , EColorRawEnum::MediumOrchid     , EColorRawEnum::MediumPurple        
                                          , EColorRawEnum::MediumSeaGreen  , EColorRawEnum::MediumSlateBlue, EColorRawEnum::MediumSpringGreen, EColorRawEnum::MediumTurquoise     
                                          , EColorRawEnum::MediumVioletRed , EColorRawEnum::MidnightBlue   , EColorRawEnum::MintCream        , EColorRawEnum::MistyRose           
                                          , EColorRawEnum::Moccasin        , EColorRawEnum::NavajoWhite    , EColorRawEnum::Navy             , EColorRawEnum::OldLace             
                                          , EColorRawEnum::Olive           , EColorRawEnum::OliveDrab      , EColorRawEnum::Orange           , EColorRawEnum::OrangeRed           
                                          , EColorRawEnum::Orchid          , EColorRawEnum::PaleGoldenRod  , EColorRawEnum::PaleGreen        , EColorRawEnum::PaleTurquoise       
                                          , EColorRawEnum::PaleVioletRed   , EColorRawEnum::PapayaWhip     , EColorRawEnum::PeachPuff        , EColorRawEnum::Peru                
                                          , EColorRawEnum::Pink            , EColorRawEnum::Plum           , EColorRawEnum::PowderBlue       , EColorRawEnum::Purple              
                                          , EColorRawEnum::RebeccaPurple   , EColorRawEnum::Red            , EColorRawEnum::RosyBrown        , EColorRawEnum::RoyalBlue           
                                          , EColorRawEnum::SaddleBrown     , EColorRawEnum::Salmon         , EColorRawEnum::SandyBrown       , EColorRawEnum::SeaGreen            
                                          , EColorRawEnum::SeaShell        , EColorRawEnum::Sienna         , EColorRawEnum::Silver           , EColorRawEnum::SkyBlue             
                                          , EColorRawEnum::SlateBlue       , EColorRawEnum::SlateGray      , EColorRawEnum::SlateGrey        , EColorRawEnum::Snow                
                                          , EColorRawEnum::SpringGreen     , EColorRawEnum::SteelBlue      , EColorRawEnum::Tan              , EColorRawEnum::Teal                
                                          , EColorRawEnum::Thistle         , EColorRawEnum::Tomato         , EColorRawEnum::Turquoise        , EColorRawEnum::Violet
                                          , EColorRawEnum::Wheat           , EColorRawEnum::White          , EColorRawEnum::WhiteSmoke       , EColorRawEnum::Yellow
                                          , EColorRawEnum::YellowGreen         
                                          );

    scriptText.append(makeEnumScriptString( prefix, "HorAlign"       , itemSep, enumSep, knownEnumNames
                                          , HorAlign::left, HorAlign::center, HorAlign::right
                                          )
                      );

    scriptText.append(makeEnumScriptString( prefix, "FontStyleFlags" , itemSep, enumSep, knownEnumNames
                                          , FontStyleFlags::normal, FontStyleFlags::italic, FontStyleFlags::underlined, FontStyleFlags::strikeout // , FontStyleFlags::italic|FontStyleFlags::strikeout
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "GradientRoundRectFillFlags" , itemSep, enumSep, knownEnumNames
                                          , GradientRoundRectFillFlags::round
                                          , GradientRoundRectFillFlags::squareBegin
                                          , GradientRoundRectFillFlags::squareEnd
                                          , GradientRoundRectFillFlags::noFillBegin
                                          , GradientRoundRectFillFlags::noFillEnd
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "FontWeight"     , itemSep, enumSep, knownEnumNames
                                          , FontWeight::thin, FontWeight::extralight, FontWeight::light, FontWeight::normal
                                          , FontWeight::semibold, FontWeight::bold, FontWeight::extrabold, FontWeight::heavy
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "GradientType"   , itemSep, enumSep, knownEnumNames
                                          , GradientType::vertical, GradientType::horizontal
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "LineType"   , itemSep, enumSep, knownEnumNames
                                          , LineType::diagonal, LineType::vertical, LineType::horizontal
                                          )
                     );

    // Автоматом в алиасы генератор не умеет, запилил руцами
    scriptText.append(_SC("enum LineDirection{FromLeftToRight=0 FromTopToBottom=0 FromRightToLeft=1 FromBottomToTop=1};"));
    // scriptText.append(makeEnumScriptString( prefix, "LineDirection"   , itemSep, enumSep, knownEnumNames
    //                                       , LineDirection::fromLeftToRight, LineDirection::fromRightToLeft
    //                                       )
    //                  );

    scriptText.append(makeEnumScriptString( prefix, "LineEndcapStyle"   , itemSep, enumSep, knownEnumNames
                                          , LineEndcapStyle::round, LineEndcapStyle::square, LineEndcapStyle::flat
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "LineJoinStyle"   , itemSep, enumSep, knownEnumNames
                                          , LineJoinStyle::bevel, LineJoinStyle::mitter, LineJoinStyle::round
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "BkMode"   , itemSep, enumSep, knownEnumNames
                                          , BkMode::opaque, BkMode::transparent
                                          )
                     );

    // Автоматом в алиасы генератор не умеет, запилил руцами
    scriptText.append(_SC("enum ArcDirection{Cw=0 Clockwise=0 Ccw=1 CounterClockwise=1};"));
    // scriptText.append(makeEnumScriptString( prefix, "ArcDirectionEnum"   , itemSep, enumSep, knownEnumNames
    //                                       , ArcDirectionEnum::Cw, ArcDirectionEnum::Cсw
    //                                       )
    //                  );

    scriptText.append(makeEnumScriptString( prefix, "SmoothingMode"   , itemSep, enumSep, knownEnumNames
                                          , SmoothingMode::defMode, SmoothingMode::highSpeed, SmoothingMode::highQuality, SmoothingMode::noSmoothing, SmoothingMode::antiAlias
                                          )
                     );


    if (pKnownEnumNames)
    {
        *pKnownEnumNames = knownEnumNames;
    }

    return scriptText;
}

//----------------------------------------------------------------------------
inline
void exposeEnums(ssq::VM &vm, const std::string &prefix = "Drawing")
{
    ssq::sqstring scriptText = enumsExposeMakeScript('\n', '\n', 0, prefix);
    ssq::Script script = vm.compileSource(scriptText.c_str());
    vm.run(script);
}

//----------------------------------------------------------------------------
// first - индекс текст. фрагмента, second - найденное положение
inline
std::vector< std::pair<std::size_t, std::size_t> > findAllOccurencies(const ssq::sqstring &text, const ssq::sqstring &item, std::size_t itemIndex)
{
    std::vector< std::pair<std::size_t, std::size_t> > resVec;

    std::size_t pos = text.find(item, 0);
    while(pos!=text.npos)
    {
        resVec.emplace_back(itemIndex, pos);
        pos = text.find(item, pos+item.size());
    }

    return resVec;
}

//----------------------------------------------------------------------------
inline
std::vector< std::pair<std::size_t, std::size_t> > mergeOccurenciesVectors( const std::vector< std::pair<std::size_t, std::size_t> > &v1
                                                                          , const std::vector< std::pair<std::size_t, std::size_t> > &v2
                                                                          )
{
    std::vector< std::pair<std::size_t, std::size_t> > resVec; resVec.reserve(v1.size()+v2.size());

    std::vector< std::pair<std::size_t, std::size_t> >::const_iterator it1 = v1.begin();
    std::vector< std::pair<std::size_t, std::size_t> >::const_iterator it2 = v2.begin();

    // Основной цикл - пока оба итератора не дошли до конца - так мы можем обращаться по любому из них
    while(it1!=v1.end() && it2!=v2.end())
    {
        if (it1->second < it2->second)
        {
            resVec.emplace_back(*it1);
            ++it1;
        }
        else
        {
            resVec.emplace_back(*it2);
            ++it2;
        }
    }

    // Добавляем хвосты, если есть

    resVec.insert(resVec.end(), it1, v1.end());
    resVec.insert(resVec.end(), it2, v2.end());

    return resVec;
}

//----------------------------------------------------------------------------
//! Производит переименование enum'ов, также может добавлять в начало скрипта скрипт задания enum'ов
/*!
Мы можем обращаться с enum'ам только через "namespace" DrawContext.EnumName.value
Или, мы сделали алиас таблицы:
local dc = DrawContext

Используем так
... = dc.EnumName.value

Или с полным именем namespace:
... = DrawContext.EnumName.value


Других вариантов вроде нет

Когда обращаемся по имени голобального enum, это выглядит так:
... = DrawContextEnumName.value
... = DrawContext_EnumName.value

Enum'ы у нас зарегистрированы как DrawContextEnumName (или DrawContext_EnumName?)
При обращении к EnumName через namespace перед EnumName должна быть точка.
Если точки нет - то это ображение через глобальное имя, ничего не делаем.
Если точка есть - то идем к началу строки, допустимые символы A-Zaz0-9 и символ подчеркивания, 
останавливаемся, если достигли начало строки, или встретили недопустимый символ.
После этого заменяем подстроку xxx.EnumName.value на DrawContext_EnumName.value

Замену производим с конца, так как, если менять с начала, то "поедут" последующие индексы

!!! Могут быть проблемы, если где-то в строковых литералах будут встречаться строки вида xxx.EnumName.
Но это довольно маловероятная ситуация


//TODO: !!! Попробовать переделать через static поля классов - http://www.squirrel-lang.org/squirreldoc/reference/language/classes.html#static-variables
Надо будет нагенерить классов
*/
inline
ssq::sqstring prepareScriptEnums(const ssq::sqstring &scriptText, const std::string &prefix = "Drawing",  bool prependWithEnums = true)
{
    std::set<ssq::sqstring> knownEnumNames;
    ssq::sqstring scriptEnumsStr = enumsExposeMakeScript(' ', ';', &knownEnumNames, prefix);

    ssq::sqstring sqPrefix = utils::to_sqstring(prefix);

    // first - индекс текст. фрагмента, second - найденное положение
    std::vector< std::pair<std::size_t, std::size_t> > allOccurencies;

    // переделываем в вектор, чтобы обращаться по индексу
    std::vector<ssq::sqstring> knownEnumNamesVec = std::vector<ssq::sqstring>(knownEnumNames.begin(), knownEnumNames.end());
    std::vector<ssq::sqstring> replaceToNamesVec; replaceToNamesVec.reserve(knownEnumNamesVec.size());
    for(const auto n: knownEnumNamesVec)
    {
        replaceToNamesVec.emplace_back(sqPrefix+n);
    }

    for( std::size_t nameIdx=0; nameIdx!=knownEnumNamesVec.size(); ++nameIdx )
    {
        //std::vector< std::pair<std::size_t, std::size_t> > tmp = findAllOccurencies(scriptText, knownEnumNamesVec[nameIdx], nameIdx);
        allOccurencies = mergeOccurenciesVectors(allOccurencies, findAllOccurencies(scriptText, knownEnumNamesVec[nameIdx], nameIdx));
    }

    // У нас тут есть вектор вхождений всех интересующих нас имён, отсортированный по возрастанию позиции
    std::reverse(allOccurencies.begin(), allOccurencies.end());
    // А теперь вектор отсортирован по убыванию позиции

    // A-Zaz0-9 и символ подчеркивания
    auto isValidNameChar = [](SQChar ch) -> bool
    {
        if ((ch>=_SC('A') && ch<=_SC('Z')) || (ch>=_SC('a') && ch<=_SC('z')) || (ch>=_SC('0') && ch<=_SC('9')) || ch==_SC('_'))
        {
            return true;
        }

        return false;
    };

    

    ssq::sqstring scriptTextResult = scriptText;

    for(std::vector< std::pair<std::size_t, std::size_t> >::const_iterator ait = allOccurencies.begin(); ait!=allOccurencies.end(); ++ait)
    {
        std::size_t nameIdx = ait->first;
        const ssq::sqstring &name = knownEnumNamesVec[nameIdx];
        std::size_t nameLen = name.size();
        std::size_t pos     = ait->second;
        std::size_t namePos = pos;

        if (pos==0)
        {
            continue; // Имя найдено в самом начале, тут ничего не заменить
        }

        --pos;
        if (scriptTextResult[pos]!=_SC('.'))
        {
            continue; // Точка не найдена перед именем enum'а
        }

        if (pos==0)
        {
            continue; // Точка найдена в самом начале, тут ничего не заменить
        }

        --pos;

        while(true)
        {
            if (!isValidNameChar(scriptTextResult[pos]))
            {
                ++pos; // Откатываемся вперёд на первый символ имени
                break;
            }

            if (pos==0)
            {
                break; // вниз двигаться больше нельзя, стоим на нулевой позиции, вперёд откат не нужен
            }

            --pos; // идём дальше "вниз"
        }

        std::size_t foundExtraLen = namePos - pos;

        if (foundExtraLen<2)
        {
            continue; // найдена только точка или вообще ничего
        }

        scriptTextResult.replace(pos, foundExtraLen+nameLen, replaceToNamesVec[nameIdx]);

    } // for

    if (prependWithEnums)
    {
        scriptTextResult = scriptEnumsStr + scriptTextResult;
    }
    
    return scriptTextResult;
}


//TODO: !!! Надо попробовать сериализацию флагов через enum_serialize, а не через enum_serialize_flags - 
// нам не нужно наборы флагов сериализовывать, а только отдельные флаги
// Заодно, если установлено несколько флагов, то по идее, должна выскочить ошибка, надо проверить

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

} // namespace simplesquirrel {

} // namespace marty_draw_context {





