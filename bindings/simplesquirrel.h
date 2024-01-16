/*! \file
    \brief Squirrel bindings for marty_draw_context types and interfaces (using al-martyn1/simplesquirrel)
*/

#pragma once



#include "marty_simplesquirrel/warnings_disable.h"
//
#include "marty_simplesquirrel/simplesquirrel.h"
//
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
// #if !defined(_SC)
//  
// #endif
//  
// #define _SC(a) L##a
// #define _SC(a) a




//----------------------------------------------------------------------------

// marty_draw_context::simplesquirrel::
namespace marty_draw_context {

namespace simplesquirrel {

//----------------------------------------------------------------------------








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

    explicit operator std::uint32_t() const
    {
        return toUnsigned();
    }

    static
    DrawingColor fromString(const ssq::Class&, const ssq::sqstring &colorName)
    {
        try
        {
            #if !defined(SQUNICODE)

                return (DrawingColor)ColorRef::deserialize(colorName);

            #else

                std::string colorNameAscii = marty_simplesquirrel::to_ascii(colorName);
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

    static
    DrawingColor fromRgb( const ssq::Class&, int r, int g, int b )
    {
        ColorRef clr;

        clr.r = (std::uint8_t)(std::uint32_t)r;
        clr.g = (std::uint8_t)(std::uint32_t)g;
        clr.b = (std::uint8_t)(std::uint32_t)b;

        clr.a = 0;

        return (DrawingColor)clr;
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


        cls.addFunc( _SC("fromRgb")     , &DrawingColor::fromRgb);

        cls.addFunc( _SC("toUnsigned")  , &DrawingColor::toUnsigned);
        cls.addFunc( _SC("fromUnsigned"), &DrawingColor::fromUnsignedBindHelper);

        cls.addFunc( _SC("toInt")       , &DrawingColor::toIntBindHelper);
        cls.addFunc( _SC("fromInt")     , &DrawingColor::fromIntBindHelper, staticMethod);

        cls.addFunc( _SC("fromString")  , &DrawingColor::fromString);
        cls.addFunc( _SC("toString")
                   , [](DrawingColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                         return marty_simplesquirrel::to_sqstring(self->serialize());
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

    DrawingCoords addImpl(DrawingCoords c)
    {
        return DrawingCoords(x+c.x, y+c.y);
    }

    DrawingCoords subImpl(DrawingCoords c)
    {
        return DrawingCoords(x-c.x, y-c.y);
    }

    DrawingCoords unmImpl()
    {
        return DrawingCoords(-x, -y);
    }

    DrawingCoords mulImpl(DrawingCoords c)
    {
        return DrawingCoords(x*c.x, y*c.y);
    }

    DrawingCoords divImpl(DrawingCoords c)
    {
        //RuntimeException(const char* msg, const char* source, const char* func, int line):Exception(msg) {
        if (c.x==0 || c.y==0)
        {
            throw ssq::RuntimeException( c.x==0 ? "division by zero (DrawingCoords.x)" : "division by zero (DrawingCoords.y)"
                                       , "somehere in '.nut' files"
                                       , "DrawingCoords._div"
                                       , 0
                                       );
        }

        return DrawingCoords(x/c.x, y/c.y);
    }

    ssq::sqstring toString() const
    {
        return marty_simplesquirrel::to_sqstring(
            marty_draw_context::floatToString(x) + 
            std::string(",")                     +
            marty_draw_context::floatToString(x) 
        );
    }

    // marty_simplesquirrel::to_sqstring
    //marty_simplesquirrel::to_sqstring


    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Coords"))
    {
        // const bool staticMethod = true ;
        // const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object ox, ssq::Object oy  /* float x, float y */  ) -> DrawingCoords*
                                {
                                    return new DrawingCoords{ marty_simplesquirrel::fromObjectConvertHelper<float>(ox, _SC("x")), marty_simplesquirrel::fromObjectConvertHelper<float>(oy, _SC("y"))};
                                }
                              , true // release
                              );

        cls.addVar(_SC("x"), &DrawingCoords::x);
        cls.addVar(_SC("y"), &DrawingCoords::y);

        // operators override
        cls.addFunc( _SC("_add") , &DrawingCoords::addImpl);
        cls.addFunc( _SC("_sub") , &DrawingCoords::subImpl);
        cls.addFunc( _SC("_unm") , &DrawingCoords::unmImpl);
        cls.addFunc( _SC("_mul") , &DrawingCoords::mulImpl);
        cls.addFunc( _SC("_div") , &DrawingCoords::divImpl);

        cls.addFunc( _SC("toString"), &DrawingCoords::toString);
        cls.addFunc( _SC("tostring"), &DrawingCoords::toString);
        cls.addFunc( _SC("_tostring"), &DrawingCoords::toString);

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
                                    float         height_         = marty_simplesquirrel::fromObjectConvertHelper<float>(h, _SC("height"));
                                    // int           escapement     = 0;
                                    // int           orientation    = 0;
                                    int           weight_         = marty_simplesquirrel::fromObjectConvertHelper<int>(w, _SC("weight"));
                                    int           fontStyleFlags_ = marty_simplesquirrel::fromObjectConvertHelper<int>(style, _SC("style"));
                                    ssq::sqstring fontFace_       = marty_simplesquirrel::fromObjectConvertHelper<ssq::sqstring>(face , _SC("face"));

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
        auto cls = vm.addClass( className.c_str()
                              , [](DrawingColor b, DrawingColor m, DrawingColor e, ssq::Object mp)
                                {
                                    float mp_         = marty_simplesquirrel::fromObjectConvertHelper<float>(mp, _SC("midPont"));
                                    return new DrawingGradientParams{b, m, e, mp_};
                                }
                              , true /* release */
                              );

        cls.addVar(_SC("colorBegin") , &DrawingGradientParams::colorBegin );
        cls.addVar(_SC("colorMid")   , &DrawingGradientParams::colorMid   );
        cls.addVar(_SC("colorEnd")   , &DrawingGradientParams::colorEnd   );
        cls.addVar(_SC("midPoint")   , &DrawingGradientParams::midPoint   );

        return cls;
    }

}; // struct DrawingGradientParams

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawingDcResourcesState
{
    int             nPens      = 0;
    int             penId      = 0;
    int             nBrushes   = 0;
    int             brushId    = 0;
    int             nFonts     = 0;
    int             fontId     = 0;
    DrawingColor    textColor;
    DrawingColor    bkColor  ;

    DrawingDcResourcesState() = default;
    DrawingDcResourcesState(const DrawingDcResourcesState &) = default;
    DrawingDcResourcesState(const DcResourcesState &rcState)
    : nPens    (rcState.nPens    )
    , penId    (rcState.penId    )
    , nBrushes (rcState.nBrushes )
    , brushId  (rcState.brushId  )
    , nFonts   (rcState.nFonts   )
    , fontId   (rcState.fontId   )
    , textColor(rcState.textColor)
    , bkColor  (rcState.bkColor  )
    {}

    operator marty_draw_context::DcResourcesState() const
    {
        DcResourcesState rcState;

        rcState.nPens     = nPens    ;
        rcState.penId     = penId    ;
        rcState.nBrushes  = nBrushes ;
        rcState.brushId   = brushId  ;
        rcState.nFonts    = nFonts   ;
        rcState.fontId    = fontId   ;
        rcState.textColor = textColor;
        rcState.bkColor   = bkColor  ;

        return rcState;
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("DcResourcesState"))
    {
        auto cls = vm.addClass( className.c_str()
                              , []() { return new DcResourcesState(); }
                              , true /* release */
                              );
        return cls;
    }

}; // struct DrawingDcResourcesState

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawingDcOffsetScale
{
    DrawingCoords    offset  ;
    DrawingCoords    scale   ;
    float            penScale;

    DrawingDcOffsetScale() = default;
    DrawingDcOffsetScale(const DrawingDcOffsetScale &) = default;
    DrawingDcOffsetScale(const DcOffsetScale &os)
    : offset  (os.offset  )
    , scale   (os.scale   )
    , penScale(floatToFloat(os.penScale))
    {}

    operator marty_draw_context::DcOffsetScale() const
    {
        DcOffsetScale os;

        os.offset   = offset  ;
        os.scale    = scale   ;
        os.penScale = penScale;

        return os;
    }

}; // struct DrawingDcOffsetScale

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawingPenParams
{
    float         width  ;
    int           endcaps;
    int           join   ;

    DrawingPenParams() : width(1.0), endcaps(0), join(0) {}
    DrawingPenParams(float width_, int endcaps_, int join_) : width(width_), endcaps(endcaps_), join(join_) {}
    DrawingPenParams(const PenParams &pp) : width(floatToFloat(pp.width)), endcaps((int)pp.endcaps), join((int)pp.join) {}
    DrawingPenParams(const DrawingPenParams &) = default;
    DrawingPenParams(DrawingPenParams &&) = default;


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
                                    float         width_     = marty_simplesquirrel::fromObjectConvertHelper<float>(w, _SC("width"));
                                    int           endcaps_   = marty_simplesquirrel::fromObjectConvertHelper<int>(ecaps, _SC("endcaps"));
                                    int           join_      = marty_simplesquirrel::fromObjectConvertHelper<int>(j, _SC("join"));

                                    return new DrawingPenParams(width_, endcaps_, join_ );
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
    ssq::Object   sqVm; // (HSQUIRRELVM vm);

    IDrawContext *pDc = 0;
    int           ctxSizeX = 0;
    int           ctxSizeY = 0;

    DrawingContext() : sqVm(0) {}
    DrawingContext(HSQUIRRELVM vm_) : sqVm(vm_), pDc(0), ctxSizeX(0), ctxSizeY(0) {}
    DrawingContext(HSQUIRRELVM vm_, IDrawContext *pDc_) : sqVm(vm_), pDc(pDc_), ctxSizeX(0), ctxSizeY(0) {}

    DrawingCoords getRawSize() const
    {
        return DrawingCoords{(float)ctxSizeX, (float)ctxSizeY};
    }

    DrawingCoords getSize() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords(0,0);

        //auto retVal = pDc->getScaledSize( DrawCoord{ctxSizeX, ctxSizeY} );
        auto retVal = pDc->mapRawToLogicSize( DrawCoord{ctxSizeX, ctxSizeY} );
        return retVal;
    }

    void flushBits() 
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return;
        pDc->flushBits();
    }
    
    int setDrawingPrecise(int p)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return (int)pDc->setDrawingPrecise((DrawingPrecise)p);
    }

    int getDrawingPrecise()
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return (int)pDc->getDrawingPrecise();
    }

    DrawingDcResourcesState getResourcesState() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingDcResourcesState();
        return pDc->getResourcesState();
    }

    void restoreResourcesState(const DcResourcesState &rcState) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return;
        pDc->restoreResourcesState(rcState);
    }

    DcOffsetScale getOffsetScale() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DcOffsetScale();
        return pDc->getOffsetScale();
    }

    void restoreOffsetScale(const DcOffsetScale &dcOs) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return;
        return pDc->restoreOffsetScale(dcOs);
    }


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

    bool markerAdd( DrawingCoords pos ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->markerAdd(pos);
    }

    bool markerAddEx( DrawingCoords pos, ssq::Object size ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->markerAdd(pos, (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(size, _SC("size")));
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

    float markerSetDefSize( ssq::Object size ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return floatToFloat((pDc->markerSetDefSize((DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(size, _SC("size")))));
    }

    float markerGetDefSize( ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return floatToFloat((pDc->markerGetDefSize()));
    }


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

    DrawingColor getBkColor() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingColor();
        return pDc->getBkColor();
    }

    int getBkMode() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return (int)pDc->getBkMode();
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

    DrawingCoords getPixelSize() const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords();
        return pDc->getPixelSize();
    }

    // virtual DrawCoord::value_type getPixelSizeX() const = 0;
    // virtual DrawCoord::value_type getPixelSizeY() const = 0;


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
        auto fScale = marty_simplesquirrel::fromObjectConvertHelper<float>(scale, _SC("scale"));
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

    int selectNewSolidPen( DrawingPenParams penParams, DrawingColor colorRef ) const
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

    DrawingPenParams getPenParams(int penId) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingPenParams();
        return PenParams(pDc->getPenParams(penId));
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

    int createFontEx(DrawingFontParams dfp, ssq::Object height) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.height = marty_simplesquirrel::fromObjectConvertHelper<float>(height, _SC("height"));
        return pDc->createFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int createOrFindFont(DrawingFontParams dfp) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        return pDc->makeFontByParams(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int createOrFindFontEx(DrawingFontParams dfp, ssq::Object height) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.height = marty_simplesquirrel::fromObjectConvertHelper<float>(height, _SC("height")); // ssq::Object
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

    int selectNewFontEx(DrawingFontParams dfp, ssq::Object height) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.height = marty_simplesquirrel::fromObjectConvertHelper<float>(height, _SC("height")); // ssq::Object
        return pDc->selectNewFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    //---
    int createFontWithFace(DrawingFontParams dfp, ssq::sqstring face) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.fontFace = face;
        return pDc->createFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }

    int createOrFindFontWithFace(DrawingFontParams dfp, ssq::sqstring face) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return -1;
        dfp.fontFace = face;
        return pDc->makeFontByParams(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    }
    //---

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

        if (pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.beginPath: path already started (endPath not called for previous beginPath)"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        return pDc->beginPath();
    }

    bool beginPathFrom(DrawingCoords c) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        if (pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.beginPath: path already started (endPath not called for previous beginPath)"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        return pDc->beginPath(c);
    }

    bool endPath( bool bStroke, bool bFill ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        if (!pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.endPath: path not started (beginPath not called)"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        // typedef struct tagSQStackInfos{
        //     const SQChar* funcname;
        //     const SQChar* source;
        //     SQInteger line;
        // }SQStackInfos;

        //SQStackInfos getStackInfos() const

        // RuntimeException(const char* msg):Exception(msg) {
        //     message = std::string(msg);
        // }
        //  
        // RuntimeException(const char* msg, const char* source, const char* func, int line):Exception(msg) {


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

    bool ellipse    (DrawingCoords leftTop, DrawingCoords rightBottom) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->ellipse(leftTop, rightBottom);
    }

    bool fillEllipse(DrawingCoords leftTop, DrawingCoords rightBottom, bool drawFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillEllipse(leftTop, rightBottom, drawFrame);
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

    bool arcByAngleDeg(DrawingCoords centerPos, ssq::Object angle) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        DrawCoord calculatedEndPos; // 
        bool res = pDc->arcTo(centerPos, (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(angle, _SC("angle")), &calculatedEndPos);
        if (res)
        {
            lastArcEndPos = calculatedEndPos;
        }

        return res;
    }

    // //! Рисует набор горизонтальных и вертикальных линий, если две точки задают диагональную линию - это ошибка
    bool roundRectFigure( ssq::Object cornersR, ssq::Object points ) const
    {
        if (points.isNull() || points.isEmpty())
        {
            return true;
        }

        ssq::Type t = points.getType();
        if (t!=ssq::Type::ARRAY)
        {
            return false;
        }

        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;


        ssq::Array a = points.toArray();

        std::size_t size = a.size();

        std::vector<DrawCoord> drawCoordPoints;

        for(std::size_t i=0; i!=size; ++i)
        {
            DrawingCoords drawingCoords = a.get<DrawingCoords>(i);
            drawCoordPoints.emplace_back(static_cast<DrawCoord>(drawingCoords));
        }


        //std::vector<Object> Array::convertRaw() {

        // template<typename T>
        // T get(size_t index) {

        if (drawCoordPoints.empty())
        {
            return true;
        }

        return pDc->roundRectFigure((DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(cornersR, _SC("cornersR")), drawCoordPoints.size(), &drawCoordPoints[0]);

    }


    bool circle(DrawingCoords centerPos, ssq::Object r) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        if (pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.circle: function can't be used within the path"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        return pDc->circle(centerPos, (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("R")));
    }

    bool fillCircle(DrawingCoords centerPos, ssq::Object r, bool drawFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        if (pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.fillCircle: function can't be used within the path"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        return pDc->fillCircle(centerPos, (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("R")), drawFrame);
    }

    bool roundRect(ssq::Object r, DrawingCoords leftTop, DrawingCoords rightBottom) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        if (pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.roundRect: function can't be used within the path"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        return pDc->roundRect((DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("cornersR")), leftTop, rightBottom);
    }

    bool fillRoundRect(ssq::Object r, DrawingCoords leftTop, DrawingCoords rightBottom, bool drawFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        if (pDc->isPathStarted())
        {
            SQStackInfos si = sqVm.getSafeStackInfos();
            throw ssq::RuntimeException("DrawContext.fillRoundRect: function can't be used within the path"
                                       , ssq::ToUtf8(si.source).c_str()
                                       , ssq::ToUtf8(si.funcname).c_str()
                                       , (int)si.line
                                       );
        }

        return pDc->fillRoundRect((DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("cornersR")), leftTop, rightBottom, drawFrame);
    }

    bool rect(DrawingCoords leftTop, DrawingCoords rightBottom) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->rect(leftTop, rightBottom);
    }

    bool fillRect(DrawingCoords leftTop, DrawingCoords rightBottom, bool drawFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillRect(leftTop, rightBottom, drawFrame);
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

    bool fillGradientRoundRect( ssq::Object r, DrawingCoords leftTop, DrawingCoords rightBottom, DrawingGradientParams gradientParams, int gradientType, bool excludeFrame
                              , ssq::Object fillBreakPos, int fillFlags) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillGradientRoundRect( (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("cornersR"))
                                    , leftTop, rightBottom, gradientParams.colorBegin, gradientParams.colorMid, gradientParams.colorEnd
                                    , (DrawCoord::value_type)gradientParams.midPoint, (GradientType)gradientType, excludeFrame
                                    , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(fillBreakPos, _SC("fillBreakPos")), (GradientRoundRectFillFlags)fillFlags
                                    );
    }

    bool fillGradientCircle(DrawingCoords pos, ssq::Object r, DrawingGradientParams gradientParams, bool excludeFrame) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->fillGradientCircle( pos, (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("radius")), gradientParams.colorBegin, gradientParams.colorMid, gradientParams.colorEnd
                                    , (DrawCoord::value_type)gradientParams.midPoint, excludeFrame
                                    );
    }


    bool textOut(DrawingCoords pos, ssq::sqstring text) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->textOut(pos, text);
    }

    bool textOutWithFontAndColor(DrawingCoords pos, int fontId, DrawingColor rgb, ssq::sqstring text) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->textOut(pos, fontId, rgb, text);
    }

    // bool textOut(DrawingCoords pos, ssq::sqstring text) const
    // {
    //     MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
    //     if (!pDc)
    //         return false;
    //     return pDc->textOut(pos, text);
    // }
    // return pDc->circle(centerPos, (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(r, _SC("R")));
    // DrawingCoords
    // int selectNewFontEx(DrawingFontParams dfp, ssq::Object height) const
    // {
    //     MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
    //     if (!pDc)
    //         return -1;
    //     dfp.height = marty_simplesquirrel::fromObjectConvertHelper<float>(height, _SC("height")); // ssq::Object
    //     return pDc->selectNewFont(static_cast< FontParamsT<ssq::sqstring> >(dfp) );
    // }
    //  
    // //---
    // int createFontWithFace(DrawingFontParams dfp, ssq::sqstring face) const


    std::vector<std::uint32_t> toUnsignedColorsVector(ssq::Object &o, const SQChar *paramName, bool allowSingleVal=false) const
    {
        #if 1

        (void)allowSingleVal;

        return marty_simplesquirrel::fromArrayObjectToClassVectorConvertEx<std::uint32_t, DrawingColor>(o, paramName /* , false */  /* allowSingleVal */ );

        #else
        std::vector<std::uint32_t>  resVec;

        if (o.isNull() || o.isEmpty())
        {
            return resVec;
        }

        ssq::Type t = o.getType();
        switch(t)
        {
            case ssq::Type::INTEGER:
            case ssq::Type::FLOAT:
            case ssq::Type::STRING:
            case ssq::Type::BOOL:
                if (allowSingleVal)
                {
                    resVec.emplace_back((std::uint32_t)marty_simplesquirrel::fromObjectConvertHelper<unsigned>(o, paramName));
                    return resVec;
                }
                break;

            case ssq::Type::ARRAY:
            {
                ssq::Array a     = o.toArray();
                std::size_t size = a.size();
        
                for(std::size_t i=0; i!=size; ++i)
                {
                    // DrawingCoords drawingCoords = a.get<DrawingCoords>(i);
    
                    auto clr = a.get<DrawingColor>(i);
                    resVec.emplace_back(clr.toUnsigned());
                }
    
                return resVec;
            }
    
            case ssq::Type::NULLPTR:
            case ssq::Type::TABLE:
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
    
        throw ssq::TypeException("bad cast", ssq::typeToStr(ssq::Type::ARRAY), ssq::typeToStr(t));
        #endif
    }
    
    std::vector<DrawCoord::value_type> toDrawCoordValueTypeVector(ssq::Object &o, const SQChar *paramName) const
    {
        return marty_simplesquirrel::fromArrayObjectToVectorConvertEx<DrawCoord::value_type, float>(o, paramName, false /* allowSingleVal */ );
    }


    bool drawTextColored( DrawingCoords    startPos
                        , ssq::Object      widthLim
                        , int              flags
                        , ssq::sqstring    text
                        , ssq::sqstring    stopChars
                        , ssq::Object      colors
                        , ssq::Object      bkColors
                        , int              fontId
                        )
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->drawTextColored( (DrawCoord)startPos
                                   , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(widthLim, _SC("widthLim"))
                                   , (DrawTextFlags)flags
                                   , text, stopChars
                                   , toUnsignedColorsVector(colors  , _SC("colors"  ), true /* allowSingleVal */ )
                                   , toUnsignedColorsVector(bkColors, _SC("bkColors"), true /* allowSingleVal */ )
                                   , fontId
                                   );
    }


    bool drawParaColored( DrawingCoords    startPos
                        , DrawingCoords    limits
                        , ssq::Object      lineSpacing
                        , ssq::Object      paraIndent
                        , ssq::Object      tabSize
                        , int              flags
                        , int              horAlign
                        , int              vertAlign
                        , ssq::sqstring    text
                        , ssq::Object      colors
                        , ssq::Object      bkColors
                        , ssq::Object      tabStopPositions
                        , int              fontId
                        )
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->drawParaColored( (DrawCoord)startPos
                                   , (DrawCoord)limits
                                   , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(lineSpacing, _SC("lineSpacing"))
                                   , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(paraIndent , _SC("paraIndent" ))
                                   , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(tabSize    , _SC("tabSize"    ))
                                   , (DrawTextFlags)flags
                                   , (HorAlign) horAlign 
                                   , (VertAlign)vertAlign
                                   , text
                                   , toUnsignedColorsVector(colors  , _SC("colors"  ), true /* allowSingleVal */ )
                                   , toUnsignedColorsVector(bkColors, _SC("bkColors"), true /* allowSingleVal */ )
                                   , toDrawCoordValueTypeVector(tabStopPositions, _SC("tabStopPositions"))
                                   , fontId
                                   );
    }

    bool drawMultiParasColored( DrawingCoords    startPos
                              , DrawingCoords    limits
                              , ssq::Object      lineSpacing
                              , ssq::Object      paraSpacing
                              , ssq::Object      paraIndent
                              , ssq::Object      tabSize
                              , int              flags
                              , int              horAlign
                              , int              vertAlign
                              , ssq::sqstring    text
                              , ssq::Object      colors
                              , ssq::Object      bkColors
                              , ssq::Object      tabStopPositions
                              , ssq::Object      paraColors
                              , ssq::Object      paraBkColors
                              , int              fontId
                              )
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->drawMultiParasColored( (DrawCoord)startPos
                                         , (DrawCoord)limits
                                         , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(lineSpacing, _SC("lineSpacing"))
                                         , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(paraSpacing, _SC("paraSpacing"))
                                         , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(paraIndent , _SC("paraIndent" ))
                                         , (DrawCoord::value_type)marty_simplesquirrel::fromObjectConvertHelper<float>(tabSize    , _SC("tabSize"    ))
                                         , (DrawTextFlags)flags
                                         , (HorAlign) horAlign 
                                         , (VertAlign)vertAlign
                                         , text
                                         , toUnsignedColorsVector(colors      , _SC("colors"      ), true /* allowSingleVal */ )
                                         , toUnsignedColorsVector(bkColors    , _SC("bkColors"    ), true /* allowSingleVal */ )
                                         , toDrawCoordValueTypeVector(tabStopPositions, _SC("tabStopPositions"))
                                         , toUnsignedColorsVector(paraColors  , _SC("paraColors"  ), true /* allowSingleVal */ )
                                         , toUnsignedColorsVector(paraBkColors, _SC("paraBkColors"), true /* allowSingleVal */ )
                                         , fontId
                                         );
    }

    bool polyCubicBeziers(ssq::Object pointsArrayObj)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = marty_simplesquirrel::fromArrayObjectToClassVectorConvertEx<DrawCoord,DrawingCoords>(pointsArrayObj, _SC("points"));
        return pDc->polyCubicBezier(vec);
    }

    bool polyCubicBeziersTo(ssq::Object pointsArrayObj)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = marty_simplesquirrel::fromArrayObjectToClassVectorConvertEx<DrawCoord,DrawingCoords>(pointsArrayObj, _SC("points"));
        return pDc->polyCubicBezierTo(vec);
    }

    bool polyQuadraticBeziers(ssq::Object pointsArrayObj)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = marty_simplesquirrel::fromArrayObjectToClassVectorConvertEx<DrawCoord,DrawingCoords>(pointsArrayObj, _SC("points"));
        return pDc->polyQuadraticBezier(vec);
    }

    bool polyQuadraticBeziersTo(ssq::Object pointsArrayObj)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = marty_simplesquirrel::fromArrayObjectToClassVectorConvertEx<DrawCoord,DrawingCoords>(pointsArrayObj, _SC("points"));
        return pDc->polyQuadraticBezierTo(vec);
    }


    bool polyCubicBezier(DrawingCoords cp1, DrawingCoords cp2, DrawingCoords cp3, DrawingCoords cp4)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = { DrawCoord(cp1), DrawCoord(cp2), DrawCoord(cp3), DrawCoord(cp4) };
        return pDc->polyCubicBezier(vec);
    }

    bool polyCubicBezierTo(DrawingCoords cp2, DrawingCoords cp3, DrawingCoords cp4)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = { DrawCoord(cp2), DrawCoord(cp3), DrawCoord(cp4) };
        return pDc->polyCubicBezierTo(vec);
    }

    bool polyQuadraticBezier(DrawingCoords cp1, DrawingCoords cp2, DrawingCoords cp3)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = { DrawCoord(cp1), DrawCoord(cp2), DrawCoord(cp3) };
        return pDc->polyQuadraticBezier(vec);
    }

    bool polyQuadraticBezierTo(DrawingCoords cp2, DrawingCoords cp3)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        std::vector<DrawCoord> vec = { DrawCoord(cp2), DrawCoord(cp3) };
        return pDc->polyQuadraticBezierTo(vec);
    }

    float distanceBetween( DrawingCoords pos1, DrawingCoords pos2)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return 0.0;

        return (float)pDc->distanceBetween(pos1,pos2);
    }

    DrawingCoords reflectPoint( DrawingCoords pos, DrawingCoords relativeTo)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return DrawingCoords(0,0);

        return DrawingCoords(pDc->reflectPoint(pos,relativeTo));
    }

    // std::vector<DrawCoord> toDrawCoordsVector(ssq::Object &o, const SQChar *paramName) const
    // virtual bool checkPolyCubicBezierNumPoints  (std::size_t numPoints) = 0;
    // virtual bool checkPolyCubicBezierToNumPoints(std::size_t numPoints) = 0;
    // virtual bool polyCubicBezier  (const DrawCoord * pPoints, std::size_t numPoints) = 0;
    // virtual bool polyCubicBezierTo(const DrawCoord * pPoints, std::size_t numPoints) = 0;
    // virtual bool polyCubicBezier  (const std::vector<DrawCoord> &points) = 0;
    // virtual bool polyCubicBezierTo(const std::vector<DrawCoord> &points) = 0;
    //  
    // virtual bool checkPolyQuadraticBezierNumPoints  (std::size_t numPoints) = 0;
    // virtual bool checkPolyQuadraticBezierToNumPoints(std::size_t numPoints) = 0;
    // virtual bool polyQuadraticBezier  (const DrawCoord * pPoints, std::size_t numPoints) = 0;
    // virtual bool polyQuadraticBezierTo(const DrawCoord * pPoints, std::size_t numPoints) = 0;
    // virtual bool polyQuadraticBezier  (const std::vector<DrawCoord> &points) = 0;
    // virtual bool polyQuadraticBezierTo(const std::vector<DrawCoord> &points) = 0;



    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("Context"))
    {
        auto cls = vm.addClass( className.c_str(), [&]() { return new DrawingContext(vm.getHandle()); }, true /* release */ );

        cls.addFunc( _SC("flushBits")              , &DrawingContext::flushBits             );

        cls.addFunc( _SC("setDrawingPrecise")      , &DrawingContext::setDrawingPrecise     );
        cls.addFunc( _SC("getDrawingPrecise")      , &DrawingContext::getDrawingPrecise     );

        cls.addFunc( _SC("getRawSize")             , &DrawingContext::getRawSize            );
        cls.addFunc( _SC("getSize")                , &DrawingContext::getSize               );

        cls.addFunc( _SC("distanceBetween")        , &DrawingContext::distanceBetween       );
        cls.addFunc( _SC("reflectPoint")           , &DrawingContext::reflectPoint          );

        cls.addFunc( _SC("getResourcesState")      , &DrawingContext::getResourcesState     );
        cls.addFunc( _SC("restoreResourcesState")  , &DrawingContext::restoreResourcesState );
        cls.addFunc( _SC("getOffsetScale")         , &DrawingContext::getOffsetScale        );
        cls.addFunc( _SC("restoreOffsetScale")     , &DrawingContext::restoreOffsetScale    );

        cls.addFunc( _SC("setCollectMarkers")      , &DrawingContext::setCollectMarkers     );
        cls.addFunc( _SC("getCollectMarkers")      , &DrawingContext::getCollectMarkers     );
        cls.addFunc( _SC("markerAdd")              , &DrawingContext::markerAdd             );
        cls.addFunc( _SC("markerAddEx")            , &DrawingContext::markerAddEx           );
        cls.addFunc( _SC("markersClear")           , &DrawingContext::markersClear          );
        cls.addFunc( _SC("markersDraw")            , &DrawingContext::markersDraw           );
        cls.addFunc( _SC("markersDrawEx")          , &DrawingContext::markersDrawEx         );
        cls.addFunc( _SC("markerSetDefSize")       , &DrawingContext::markerSetDefSize      );
        cls.addFunc( _SC("markerGetDefSize")       , &DrawingContext::markerGetDefSize      );

        cls.addFunc( _SC("setSmoothingMode")       , &DrawingContext::setSmoothingMode      );
        cls.addFunc( _SC("getSmoothingMode")       , &DrawingContext::getSmoothingMode      );
        cls.addFunc( _SC("setTextColor")           , &DrawingContext::setTextColor          );
        cls.addFunc( _SC("getTextColor")           , &DrawingContext::getTextColor          );
        cls.addFunc( _SC("setBkColor")             , &DrawingContext::setBkColor            );
        cls.addFunc( _SC("getBkColor")             , &DrawingContext::getBkColor            );
        cls.addFunc( _SC("setBkMode")              , &DrawingContext::setBkMode             );
        cls.addFunc( _SC("getBkMode")              , &DrawingContext::getBkMode             );
        cls.addFunc( _SC("setTextColor")           , &DrawingContext::setTextColor          );
        cls.addFunc( _SC("getTextColor")           , &DrawingContext::getTextColor          );

        cls.addFunc( _SC("getDialigBaseUnits")     , &DrawingContext::getDialigBaseUnits    );

        cls.addFunc( _SC("mapRawToLogicPos")       , &DrawingContext::mapRawToLogicPos      );
        cls.addFunc( _SC("mapRawToLogicSize")      , &DrawingContext::mapRawToLogicSize     );
        cls.addFunc( _SC("getPixelSize")           , &DrawingContext::getPixelSize          );

        cls.addFunc( _SC("getScaledPos")           , &DrawingContext::getScaledPos          );
        cls.addFunc( _SC("getScaledSize")          , &DrawingContext::getScaledSize         );
        cls.addFunc( _SC("setOffset")              , &DrawingContext::setOffset             );
        cls.addFunc( _SC("getOffset")              , &DrawingContext::getOffset             );
        cls.addFunc( _SC("setScale")               , &DrawingContext::setScale              );
        cls.addFunc( _SC("getScale")               , &DrawingContext::getScale              );
        cls.addFunc( _SC("setPenScale")            , &DrawingContext::setPenScale           );
        cls.addFunc( _SC("getPenScale")            , &DrawingContext::getPenScale           );

        cls.addFunc( _SC("createSolidPen")         , &DrawingContext::createSolidPen        );
        cls.addFunc( _SC("selectPen")              , &DrawingContext::selectPen             );
        cls.addFunc( _SC("selectNewSolidPen")      , &DrawingContext::selectNewSolidPen     );
        cls.addFunc( _SC("getCurPen")              , &DrawingContext::getCurPen             );
        cls.addFunc( _SC("getPenColor")            , &DrawingContext::getPenColor           );
        cls.addFunc( _SC("getPenParams")           , &DrawingContext::getPenParams          );
        
        cls.addFunc( _SC("setDefaultCosmeticPen")  , &DrawingContext::setDefaultCosmeticPen );
        cls.addFunc( _SC("getDefaultCosmeticPen")  , &DrawingContext::getDefaultCosmeticPen );

        cls.addFunc( _SC("createSolidBrush")       , &DrawingContext::createSolidBrush      );
        cls.addFunc( _SC("selectBrush")            , &DrawingContext::selectBrush           );
        cls.addFunc( _SC("selectNewSolidBrush")    , &DrawingContext::selectNewSolidBrush   );
        cls.addFunc( _SC("getCurBrush")            , &DrawingContext::getCurBrush           );

        cls.addFunc( _SC("createFont")             , &DrawingContext::createFont            );
        cls.addFunc( _SC("createFontEx")           , &DrawingContext::createFontEx          );
        cls.addFunc( _SC("createOrFindFont")       , &DrawingContext::createOrFindFont      );
        cls.addFunc( _SC("createOrFindFontEx")     , &DrawingContext::createOrFindFontEx    );
        cls.addFunc( _SC("createFontWithFace")      ,&DrawingContext::createFontWithFace      );
        cls.addFunc( _SC("createOrFindFontWithFace"),&DrawingContext::createOrFindFontWithFace);
        cls.addFunc( _SC("selectFont")             , &DrawingContext::selectFont              );
        cls.addFunc( _SC("selectNewFont")          , &DrawingContext::selectNewFont           );
        cls.addFunc( _SC("selectNewFontEx")        , &DrawingContext::selectNewFontEx         );
        cls.addFunc( _SC("getCurFont")             , &DrawingContext::getCurFont              );
        cls.addFunc( _SC("getFontParamsById")      , &DrawingContext::getFontParamsById       );

        cls.addFunc( _SC("beginPath")              , &DrawingContext::beginPath               );
        cls.addFunc( _SC("beginPathFrom")          , &DrawingContext::beginPathFrom           );
        cls.addFunc( _SC("endPath")                , &DrawingContext::endPath                 );
        cls.addFunc( _SC("closeFigure")            , &DrawingContext::closeFigure             );
        cls.addFunc( _SC("isPathStarted")          , &DrawingContext::isPathStarted           );

        cls.addFunc( _SC("moveTo")                 , &DrawingContext::moveTo                  );
        cls.addFunc( _SC("lineTo")                 , &DrawingContext::lineTo                  );
        cls.addFunc( _SC("circle")                 , &DrawingContext::circle                  );
        cls.addFunc( _SC("fillCircle")             , &DrawingContext::fillCircle              );
        cls.addFunc( _SC("ellipse")                , &DrawingContext::ellipse                 );
        cls.addFunc( _SC("fillEllipse")            , &DrawingContext::fillEllipse             );
        cls.addFunc( _SC("ellipticArcTo")          , &DrawingContext::ellipticArcTo           );
        cls.addFunc( _SC("getLastArcEndPos")       , &DrawingContext::getLastArcEndPos        );
        cls.addFunc( _SC("arcToPos")               , &DrawingContext::arcToPos                );
        cls.addFunc( _SC("arcByAngleDeg")          , &DrawingContext::arcByAngleDeg           );
        cls.addFunc( _SC("roundRectFigure")        , &DrawingContext::roundRectFigure         );
        cls.addFunc( _SC("roundRect")              , &DrawingContext::roundRect               );
        cls.addFunc( _SC("rect")                   , &DrawingContext::rect                    );
        cls.addFunc( _SC("fillRoundRect")          , &DrawingContext::fillRoundRect           );
        cls.addFunc( _SC("fillRect")               , &DrawingContext::fillRect                );
        cls.addFunc( _SC("fillGradientRect")       , &DrawingContext::fillGradientRect        );
        cls.addFunc( _SC("fillGradientRoundRect")  , &DrawingContext::fillGradientRoundRect   );
        cls.addFunc( _SC("fillGradientCircle")     , &DrawingContext::fillGradientCircle      );

        cls.addFunc( _SC("textOut")                , &DrawingContext::textOut                 );
        cls.addFunc( _SC("textOutWithFontAndColor"), &DrawingContext::textOutWithFontAndColor );
        cls.addFunc( _SC("drawTextColored")        , &DrawingContext::drawTextColored         );
        cls.addFunc( _SC("drawParaColored")        , &DrawingContext::drawParaColored         );
        cls.addFunc( _SC("drawMultiParasColored")  , &DrawingContext::drawMultiParasColored   );
        //cls.addFunc( _SC("")  , &DrawingContext::);
        //cls.addFunc( _SC("")  , &DrawingContext::);


        // polyCubicBeziers/polyCubicBeziersTo/polyQuadraticBeziers/polyQuadraticBeziersTo
        cls.addFunc( _SC("polyCubicBeziers")       , &DrawingContext::polyCubicBeziers);
        cls.addFunc( _SC("polyCubicBeziersTo")     , &DrawingContext::polyCubicBeziersTo);
        cls.addFunc( _SC("polyQuadraticBeziers")   , &DrawingContext::polyQuadraticBeziers);
        cls.addFunc( _SC("polyQuadraticBeziersTo") , &DrawingContext::polyQuadraticBeziersTo);

        // polyCubicBezier/polyCubicBezierTo/polyQuadraticBezier/polyQuadraticBezierTo
        cls.addFunc( _SC("polyCubicBezier")        , &DrawingContext::polyCubicBezier      );
        cls.addFunc( _SC("polyCubicBezierTo")      , &DrawingContext::polyCubicBezierTo    );
        cls.addFunc( _SC("polyQuadraticBezier")    , &DrawingContext::polyQuadraticBezier  );
        cls.addFunc( _SC("polyQuadraticBezierTo")  , &DrawingContext::polyQuadraticBezierTo);


        return cls;
    }

}; // struct DrawingContext


//----------------------------------------------------------------------------







//----------------------------------------------------------------------------
inline
ssq::sqstring enumsExposeMakeScript( marty_simplesquirrel::EnumScriptGenerationOptions generationOptions /* char itemSep, char enumSep */
                                   //, std::set<ssq::sqstring> *pKnownEnumNames = 0
                                   , const std::string &prefix = "Drawing"
                                   )
{

    // auto strVal = enum_serialize_flags(FontStyleFlags::italic);
    // //auto strVal = enum_serialize(val);
    // (void)strVal;

    //std::set<ssq::sqstring> knownEnumNames;

    // itemSep = enumSep;

    // ssq::sqstring makeEnumClassScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, const std::string &itemTypeString, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
    ssq::sqstring scriptText; // = 
                      //makeEnumScriptString( prefix, "Colors"   , itemSep, enumSep, knownEnumNames


    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "CallbackResultFlags", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , CallbackResultFlags::none               , CallbackResultFlags::repaint       
                                          , CallbackResultFlags::captureMouse       , CallbackResultFlags::releaseCapture
                                          , CallbackResultFlags::disableTimerUpdate , CallbackResultFlags::enableTimerUpdate
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseButtonEvent", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseButtonEvent::released   , MouseButtonEvent::pressed    , MouseButtonEvent::doubleClick
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseButton", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseButton::none
                                          , MouseButton::leftButton   , MouseButton::rightButton  
                                          , MouseButton::middleButton , MouseButton::midButton    
                                          , MouseButton::xButton1     , MouseButton::xButton2
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseButtonStateFlags", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseButtonStateFlags::none
                                          , MouseButtonStateFlags::leftButtonPressed   , MouseButtonStateFlags::rightButtonPressed  
                                          , MouseButtonStateFlags::shiftPressed        , MouseButtonStateFlags::controlPressed      
                                          , MouseButtonStateFlags::middleButtonPressed , MouseButtonStateFlags::midButtonPressed    
                                          , MouseButtonStateFlags::xButton1Pressed     , MouseButtonStateFlags::xButton2Pressed     
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseMoveEventType", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseMoveEventType::move , MouseMoveEventType::hover, MouseMoveEventType::leave //, MouseMoveEventType::enter
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "WindowSizingEventEdge", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , WindowSizingEventEdge::none       , WindowSizingEventEdge::left       , WindowSizingEventEdge::right
                                          , WindowSizingEventEdge::top        , WindowSizingEventEdge::topLeft    , WindowSizingEventEdge::topRigh
                                          , WindowSizingEventEdge::bottom     , WindowSizingEventEdge::bottomLeft , WindowSizingEventEdge::bottomRight
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "WindowSizeRequestType", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , WindowSizeRequestType::restored , WindowSizeRequestType::minimized, WindowSizeRequestType::maximized, WindowSizeRequestType::maxShow, WindowSizeRequestType::maxHide
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "HorAlign", ""       , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , HorAlign::left, HorAlign::center, HorAlign::right
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "VertAlign", ""       , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , VertAlign::top, VertAlign::center, VertAlign::bottom
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "FontStyleFlags", "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , FontStyleFlags::normal, FontStyleFlags::italic, FontStyleFlags::underlined, FontStyleFlags::strikeout // , FontStyleFlags::italic|FontStyleFlags::strikeout
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "GradientRoundRectFillFlags" , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , GradientRoundRectFillFlags::round
                                          , GradientRoundRectFillFlags::squareBegin
                                          , GradientRoundRectFillFlags::squareEnd
                                          , GradientRoundRectFillFlags::noFillBegin
                                          , GradientRoundRectFillFlags::noFillEnd
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "FontWeight"     , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , FontWeight::thin, FontWeight::extralight, FontWeight::light, FontWeight::normal
                                          , FontWeight::semibold, FontWeight::bold, FontWeight::extrabold, FontWeight::heavy
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "GradientType"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , GradientType::vertical, GradientType::horizontal
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "LineType"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , LineType::diagonal, LineType::vertical, LineType::horizontal
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "DrawTextFlags" , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , DrawTextFlags::none                     , DrawTextFlags::calcOnly                 , DrawTextFlags::fitGlyphStartPos
                                          , DrawTextFlags::fitWidthDisable          , DrawTextFlags::fitHeightStartPos        , DrawTextFlags::fitHeightDisable
                                          , DrawTextFlags::endEllipsis              , DrawTextFlags::pathEllipsis             , DrawTextFlags::wordEllipsis
                                          , DrawTextFlags::dontExpandTabs           , DrawTextFlags::kerningDisable           , DrawTextFlags::combiningAsSeparateGlyph
                                          , DrawTextFlags::forceSpacesColoring      , DrawTextFlags::skipEmptyParas           , DrawTextFlags::stopOnLineBreaks
                                          , DrawTextFlags::stopOnTabs               , DrawTextFlags::keepLtSpaces             , DrawTextFlags::noLastLineSpacing
                                          , DrawTextFlags::coloringResetOnPara      , DrawTextFlags::coloringWords
                                          )
                     );


    // Автоматом в алиасы генератор не умеет, запилил руцами
    //scriptText.append(_SC("enum LineDirection{FromLeftToRight=0 FromTopToBottom=0 FromRightToLeft=1 FromBottomToTop=1};"));
    scriptText.append(_SC("class "));
    scriptText.append(marty_simplesquirrel::to_sqstring(prefix));
    scriptText.append(_SC(".LineDirection{static FromLeftToRight=0; static FromTopToBottom=0; static FromRightToLeft=1; static FromBottomToTop=1; };"));
    // scriptText.append(makeEnumScriptString( prefix, "LineDirection"   , itemSep, enumSep, knownEnumNames
    //                                       , LineDirection::fromLeftToRight, LineDirection::fromRightToLeft
    //                                       )
    //                  );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "LineEndcapStyle"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , LineEndcapStyle::round, LineEndcapStyle::square, LineEndcapStyle::flat
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "LineJoinStyle"   , "", generationOptions // itemSep, enumSep// , knownEnumNames
                                          , LineJoinStyle::bevel, LineJoinStyle::mitter, LineJoinStyle::round
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "BkMode"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , BkMode::opaque, BkMode::transparent
                                          )
                     );

    // Автоматом в алиасы генератор не умеет, запилил руцами
    //scriptText.append(_SC("enum ArcDirection{Cw=0 Clockwise=0 Ccw=1 CounterClockwise=1};"));
    scriptText.append(_SC("class "));
    scriptText.append(marty_simplesquirrel::to_sqstring(prefix));
    scriptText.append(_SC(".ArcDirection{static Cw=0; static Clockwise=0; static Ccw=1; static CounterClockwise=1; };"));
    // scriptText.append(makeEnumScriptString( prefix, "ArcDirectionEnum"   , itemSep, enumSep, knownEnumNames
    //                                       , ArcDirectionEnum::Cw, ArcDirectionEnum::Cсw
    //                                       )
    //                  );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "SmoothingMode"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , SmoothingMode::defMode, SmoothingMode::highSpeed, SmoothingMode::highQuality, SmoothingMode::noSmoothing, SmoothingMode::antiAlias
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "DrawingPrecise"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , DrawingPrecise::defPrecise, DrawingPrecise::pixelPrecise, DrawingPrecise::textPrecise, DrawingPrecise::smoothingPrecise
                                          )
                     );

    scriptText.append(
                      marty_simplesquirrel::makeEnumClassScriptString( prefix+".", "Colors", prefix+".Color"   , generationOptions // enumSep /* itemSep */ , enumSep // , knownEnumNames
                                          , EColorRawEnum::AliceBlue       , EColorRawEnum::AntiqueWhite   , EColorRawEnum::Aqua             , EColorRawEnum::Aquamarine          
                                          , EColorRawEnum::Azure           , EColorRawEnum::Beige          , EColorRawEnum::Bisque           , EColorRawEnum::Black               
                                          , EColorRawEnum::BlanchedAlmond  , EColorRawEnum::Blue           , EColorRawEnum::BlueViolet       , EColorRawEnum::Brown               
                                          , EColorRawEnum::BurlyWood       , EColorRawEnum::CadetBlue      , EColorRawEnum::Chartreuse       , EColorRawEnum::Chocolate           
                                          , EColorRawEnum::Cyan            , EColorRawEnum::MediumCyan
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
                                          )
                     );



    // if (pKnownEnumNames)
    // {
    //     *pKnownEnumNames = knownEnumNames;
    // }

    return scriptText;
}

//----------------------------------------------------------------------------
inline
void exposeEnums(ssq::VM &vm, const marty_simplesquirrel::EnumScriptGenerationOptions& generationOptions, const std::string &prefix = "Drawing")
{
    //ssq::sqstring scriptText = enumsExposeMakeScript('\n', '\n', 0, prefix);
    ssq::sqstring scriptText = enumsExposeMakeScript(generationOptions, prefix);
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
#if 0
inline
ssq::sqstring prepareScriptEnums(const ssq::sqstring &scriptText, const std::string &prefix = "Drawing",  bool prependWithEnums = true)
{
    std::set<ssq::sqstring> knownEnumNames;
    ssq::sqstring scriptEnumsStr = enumsExposeMakeScript(' ', ';', &knownEnumNames, prefix);

    ssq::sqstring sqPrefix = marty_simplesquirrel::to_sqstring(prefix);

    // first - индекс текст. фрагмента, second - найденное положение
    std::vector< std::pair<std::size_t, std::size_t> > allOccurencies;

    // переделываем в вектор, чтобы обращаться по индексу
    std::vector<ssq::sqstring> knownEnumNamesVec = std::vector<ssq::sqstring>(knownEnumNames.begin(), knownEnumNames.end());
    std::vector<ssq::sqstring> replaceToNamesVec; replaceToNamesVec.reserve(knownEnumNamesVec.size());
    for(const auto &n: knownEnumNamesVec)
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
#endif


//TODO: !!! Надо попробовать сериализацию флагов через enum_serialize, а не через enum_serialize_flags - 
// нам не нужно наборы флагов сериализовывать, а только отдельные флаги
// Заодно, если установлено несколько флагов, то по идее, должна выскочить ошибка, надо проверить

//----------------------------------------------------------------------------





//----------------------------------------------------------------------------
template<typename TVM>
ssq::sqstring performBinding(TVM &vm, const ssq::sqstring &scriptText, const std::string &ns, const marty_simplesquirrel::EnumScriptGenerationOptions &generationOptions)
{
    //ssq::sqstring preparedScriptText1 = marty_draw_context::simplesquirrel::prepareScriptEnums(scriptText, ns, true);
    std::set<ssq::sqstring> knownEnumNames;
    ssq::sqstring preparedScriptText1 = enumsExposeMakeScript( generationOptions
                                                             //, &knownEnumNames
                                                             , ns /* prefix */
                                                             );
    preparedScriptText1 += scriptText;

    ssq::sqstring sqNs = marty_simplesquirrel::to_sqstring(ns);

    // lout << encoding::toUtf8(preparedScriptText1);
    // lout << "\n----------\n\n";

    ssq::Table tDraw = 
    vm.addTable(sqNs.c_str());
    marty_draw_context::simplesquirrel::DrawingCoords          ::expose(tDraw /*vm*/, _SC("Coords"));
    marty_draw_context::simplesquirrel::DrawingCoords          ::expose(tDraw /*vm*/, _SC("Scale"));
    //marty_draw_context::simplesquirrel::DrawingCoords          ::expose(tDraw /*vm*/, _SC(""));
    marty_draw_context::simplesquirrel::DrawingFontParams      ::expose(tDraw /*vm*/, _SC("FontParams"));
    marty_draw_context::simplesquirrel::DrawingGradientParams  ::expose(tDraw /*vm*/, _SC("GradientParams"));
    marty_draw_context::simplesquirrel::DrawingPenParams       ::expose(tDraw /*vm*/, _SC("PenParams"));
    marty_draw_context::simplesquirrel::DrawingContext         ::expose(tDraw /*vm*/, _SC("Context"));
    marty_draw_context::simplesquirrel::DrawingColor           ::expose(tDraw /*vm*/, _SC("Color"));

    return preparedScriptText1;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

} // namespace simplesquirrel {

} // namespace marty_draw_context {



#include "marty_simplesquirrel/warnings_restore.h"




