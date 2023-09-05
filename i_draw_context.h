#pragma once


//#include <stdint>

#include <cstddef>
#include <utility>

#include "marty_decimal/marty_decimal.h"

#include "dc_debug/uw_log.h"

#include "draw_context_types.h"


//----------------------------------------------------------------------------
#ifndef IDC_ARG_USED

    //! Подавление варнинга о неиспользованном аргументе
    #define IDC_ARG_USED(x)                   (void)(x)

#endif

//----------------------------------------------------------------------------




namespace marty_draw_context {




/*
    Win32 - https://docs.microsoft.com/en-us/windows/win32/gdi/windows-gdi

    MoveToEx    - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-movetoex
    LineTo      - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-lineto

    DrawText    - https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawtext
    TextOutA    - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-textouta

    Arc         - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-arc
    ArcTo       - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-arcto
                  ArcTo is similar to the Arc function, except that the current position is updated.
    SetArcDirection - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setarcdirection

    RoundRect   - https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-roundrect
                  The rectangle is outlined by using the current pen and filled by using the current brush.

    Path Functions (Windows GDI) - https://docs.microsoft.com/en-us/windows/win32/gdi/path-functions
    BeginPath
    EndPath
    FillPath
    StrokePath
    StrokeAndFillPath
     CloseFigure

    Antialiasing Using Windows GDI - https://www.codeproject.com/Articles/21520/Antialiasing-Using-Windows-GDI

    GDI+ - https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-antialiasing-with-lines-and-curves-about


    Qt
    QPainter - https://doc.qt.io/qt-6/qpainter.html

    drawPath - https://doc.qt.io/qt-6/qpainter.html#drawPath
               Draws the given painter path using the current pen for outline and the current brush for filling.
    drawText

    void QPainterPath::moveTo(const QPointF &point) - https://doc.qt.io/qt-6/qpainterpath.html#moveTo
    void QPainterPath::closeSubpath() - https://doc.qt.io/qt-6/qpainterpath.html#closeSubpath


    QPainterPath - https://doc.qt.io/qt-6/qpainterpath.html
    arcTo - https://doc.qt.io/qt-6/qpainterpath.html#arcTo
    void QPainterPath::arcTo(const QRectF &rectangle, qreal startAngle, qreal sweepLength)

    setBrush
    setBackgroundMode - Qt::TransparentMode (the default) draws stippled lines and text without setting the background pixels.



 */


#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif






//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct IDrawContext
{

    typedef DrawCoord::value_type  float_t;


    virtual ~IDrawContext() {}

    virtual void setStringEncoding(const std::string &encName) = 0;
    virtual std::string getStringEncoding() = 0;

    virtual void logFontsInfo() = 0;

    virtual void freeAllocatedRc() = 0;

    virtual SmoothingMode setSmoothingMode( SmoothingMode m ) = 0;
    virtual SmoothingMode getSmoothingMode( ) = 0;

    virtual bool setCollectMarkers( bool cmMode ) = 0;
    virtual bool getCollectMarkers( ) = 0;
    virtual bool markerAdd( const DrawCoord &pos, const DrawCoord::value_type sz ) = 0;
    virtual bool markerAdd( const DrawCoord &pos ) = 0;
    virtual void markersClear( ) = 0;
    virtual void markersDraw( int penId ) = 0;

    virtual DrawCoord::value_type markerSetDefSize( const DrawCoord::value_type &sz ) = 0;
    virtual DrawCoord::value_type markerGetDefSize( ) = 0;


    virtual float_t getFitFontHeight(const DrawSize &boxSize) = 0;
    virtual float_t getAwgFontWidth(const FontParamsA &fp) = 0;
    virtual float_t getAwgFontWidth(const FontParamsW &fp) = 0;
    virtual float_t getFitMarginWidth(const FontParamsA &fp) = 0;
    virtual float_t getFitMarginWidth(const FontParamsW &fp) = 0;

    virtual DrawSize getDialigBaseUnits() = 0;

    virtual DrawCoord mapRawToLogicPos( const DrawCoord &c  ) = 0;
    virtual DrawCoord mapRawToLogicSize( const DrawCoord &c ) = 0;

    virtual DrawCoord getScaledPos( const DrawCoord &c  ) const = 0;
    virtual DrawCoord getScaledSize( const DrawCoord &c ) const = 0;


    virtual DrawCoord setOffset( const DrawCoord &c ) = 0;
    virtual DrawCoord getOffset( ) = 0;

    virtual DrawScale setScale( const DrawScale &scale ) = 0;
    virtual DrawScale getScale( ) = 0;

    virtual float_t setPenScale( float_t scale ) = 0;
    virtual float_t getPenScale( ) = 0;

    virtual DrawCoord getCurPos( ) = 0;

    virtual int createSolidBrush( const ColorRef &rgb ) = 0;
    virtual int createSolidBrush( std::uint8_t r, std::uint8_t g, std::uint8_t b ) = 0;
    virtual int selectBrush( int brushId ) = 0;

    // returns new brushId, not prev
    virtual int selectNewSolidBrush( std::uint8_t r, std::uint8_t g, std::uint8_t b ) = 0;
    virtual int selectNewSolidBrush( const ColorRef &rgb ) = 0;

    virtual int getCurBrush() = 0;


    virtual int  createFont( float_t height, int escapement, int orientation, FontWeight weight, FontStyleFlags fontStyleFlags, const char    *fontFace ) = 0;
    virtual int  createFont( float_t height, int escapement, int orientation, FontWeight weight, FontStyleFlags fontStyleFlags, const wchar_t *fontFace ) = 0;
    virtual int  createFont( const FontParamsA &fp ) = 0;
    virtual int  createFont( const FontParamsW &fp ) = 0;
    virtual int  createFont( FontParamsA fp, const FontParamsA::string_type &fontFace ) = 0;
    virtual int  createFont( FontParamsW fp, const FontParamsW::string_type &fontFace ) = 0;

    virtual int  makeFontByParams( const FontParamsA &fp ) = 0;
    virtual int  makeFontByParams( const FontParamsW &fp ) = 0;
    virtual int  makeFontByParams( FontParamsA fp, float_t height ) = 0;
    virtual int  makeFontByParams( FontParamsW fp, float_t height ) = 0;

    virtual int  selectFont( int fontId ) = 0;

    // returns new fontId, not prev
    virtual int  selectNewFont( const FontParamsA &fp ) = 0;
    virtual int  selectNewFont( const FontParamsW &fp ) = 0;

    virtual int  getCurFont() = 0;

    virtual std::wstring decodeString( const std::string &str ) = 0;
    virtual bool textOut( const DrawCoord &pos, const std::string &text ) = 0;
    virtual bool textOut( const DrawCoord &pos, const std::wstring &text ) = 0;
    virtual bool textOut( const DrawCoord &pos, int fontId, const ColorRef &rgb, const std::string &text ) = 0;
    virtual bool textOut( const DrawCoord &pos, int fontId, const ColorRef &rgb, const std::wstring &text ) = 0;


    // virtual DrawCoord::value_type getFonSizeFitHeigh( const FontParamsA &fp, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text /* , const std::string  &fontFace="Courier New"  */ , HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) = 0;

    virtual bool getFontParamsById( int id, FontParamsA &fp ) = 0;
    virtual bool getFontParamsById( int id, FontParamsW &fp ) = 0;

    virtual int getMonospacedFontCharWidthApprox(const FontParamsA &fp) = 0;
    virtual int getMonospacedFontCharWidthApprox(const FontParamsW &fp) = 0;
    virtual int getMonospacedFontCharWidthApprox(int id) = 0;

    virtual int getProportionalFontCharWidthScaleApprox(const FontParamsA &fp) = 0;
    virtual int getProportionalFontCharWidthScaleApprox(const FontParamsW &fp) = 0;

    virtual bool drawTextFitHeigh( const FontParamsA &fp, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text /* , const std::string  &fontFace="Courier New"  */ , HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) = 0;
    virtual bool drawTextFitHeigh( const FontParamsW &fp, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::wstring &text /* , const std::wstring &fontFace=L"Courier New" */ , HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) = 0;

    virtual bool drawTextFitHeighEx( const FontParamsA &fp, DrawCoord::value_type fontHeightScale, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text /* , const std::string  &fontFace="Courier New"  */ , HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) = 0;
    virtual bool drawTextFitHeighEx( const FontParamsW &fp, DrawCoord::value_type fontHeightScale, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::wstring &text /* , const std::wstring &fontFace=L"Courier New" */ , HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) = 0;

    // !!! TODO нужно сделать версии получения ширины символа для FontParamsA/W/id и для char/wchar_t - всего 6 штук
    // Только латинские символы (потом, может, добавлю национальные)
    // Фонт не принципиален
    // Нужно для реализации calcDrawnTextWidthApprox
    virtual int getProportionalFontCharWidthApprox(const FontParamsA &fp, char    ch) = 0;
    virtual int getProportionalFontCharWidthApprox(const FontParamsA &fp, wchar_t ch) = 0;

    virtual int getProportionalFontCharWidthApprox(const FontParamsW &fp, char    ch) = 0;
    virtual int getProportionalFontCharWidthApprox(const FontParamsW &fp, wchar_t ch) = 0;

    virtual int getFontCharWidthApprox(int fontId, char    ch, int scale = 100) = 0;
    virtual int getFontCharWidthApprox(int fontId, wchar_t ch, int scale = 100) = 0;

    virtual int getFontCharWidthApprox(const FontParamsA &fp, char    ch, int scale = 100) = 0;
    virtual int getFontCharWidthApprox(const FontParamsA &fp, wchar_t ch, int scale = 100) = 0;

    virtual int getFontCharWidthApprox(const FontParamsW &fp, char    ch, int scale = 100) = 0;
    virtual int getFontCharWidthApprox(const FontParamsW &fp, wchar_t ch, int scale = 100) = 0;


    virtual float_t calcDrawnTextWidthApprox(const FontParamsA &fp, const char*    text, std::size_t nChars, int widthScale = 100) = 0;
    virtual float_t calcDrawnTextWidthApprox(const FontParamsW &fp, const char*    text, std::size_t nChars, int widthScale = 100) = 0;
    virtual float_t calcDrawnTextWidthApprox(const FontParamsA &fp, const wchar_t* text, std::size_t nChars, int widthScale = 100) = 0;
    virtual float_t calcDrawnTextWidthApprox(const FontParamsW &fp, const wchar_t* text, std::size_t nChars, int widthScale = 100) = 0;

    virtual float_t calcDrawnTextWidthApprox(int   fontId         , const char*    text, std::size_t nChars, int widthScale = 100) = 0;
    virtual float_t calcDrawnTextWidthApprox(int   fontId         , const wchar_t* text, std::size_t nChars, int widthScale = 100) = 0;

    virtual DrawSize calcDrawnTextSizeExact (int   fontId         , const char*    text, std::size_t nChars) = 0;
    virtual DrawSize calcDrawnTextSizeExact (int   fontId         , const wchar_t* text, std::size_t nChars) = 0;

    virtual ColorRef setTextColor( const ColorRef &rgb ) = 0;
    virtual ColorRef getTextColor( ) = 0;
    virtual ColorRef setTextColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) = 0;
    virtual ColorRef setBkColor( const ColorRef &rgb ) = 0;
    virtual ColorRef setBkColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) = 0;

    virtual BkMode setBkMode( BkMode mode ) = 0;
    //virtual BkMode getBkMode() = 0;

    virtual int setDefaultCosmeticPen( int penId ) = 0;
    virtual int getDefaultCosmeticPen( ) = 0;

    virtual int createSolidPen( float_t width, LineEndcapStyle endcaps, LineJoinStyle join
                              , std::uint8_t r, std::uint8_t g, std::uint8_t b
                              ) = 0;
    virtual int createSolidPen( float_t width, LineEndcapStyle endcaps, LineJoinStyle join
                              , const ColorRef &rgb
                              ) = 0;
    virtual int createSolidPen( const PenParams &penParams, const ColorRef &colorRef ) = 0;
    virtual int createSolidPen( const PenParamsWithColor &penParams ) = 0;
    virtual int selectPen( int penId ) = 0;

    // returns newly created penId, not previously selected penId
    virtual int selectNewSolidPen( const PenParams &penParams, const ColorRef &colorRef ) = 0;
    virtual int selectNewSolidPen( const PenParamsWithColor &penParams ) = 0;
    //virtual void setPenColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) = 0;

    virtual int getCurPen() = 0;

    virtual ColorRef getPenColor(int penId) = 0;


    virtual bool beginPath()                                = 0;
    virtual bool beginPath( const DrawCoord &to )           = 0;
    virtual bool endPath( bool bStroke = true, bool bFill = false ) = 0;
    virtual bool closeFigure()                              = 0;
    virtual bool isPathStarted() = 0;

    virtual bool moveTo( const DrawCoord &to ) = 0;
    virtual bool lineTo( const DrawCoord &to ) = 0;

    virtual bool ellipticArcTo( const DrawCoord &leftTop
                              , const DrawCoord &rightBottom
                              , const DrawCoord &arcStartRefPoint
                              , const DrawCoord &arcEndRefPoint
                              , bool             directionCounterclockwise
                              ) = 0;

    virtual bool arcTo(const DrawCoord &centerPos, const DrawCoord &endPos, bool directionCounterclockwise, DrawCoord *pResEndPos = 0 ) = 0;
    virtual bool arcTo(const DrawCoord &centerPos, const DrawCoord::value_type angleGradus, DrawCoord *pResEndPos = 0 ) = 0;

    //! Рисует набор горизонтальных и вертикальных линий, если две точки задают диагональную линию - это ошибка
    virtual bool roundRectFigure( const DrawCoord::value_type &cornersR
                                , std::size_t numPoints
                                , const DrawCoord             *pPoints
                                ) = 0;

    //! Implemented offten with serios of the lineTo and ellipticArcTo calls
    virtual bool roundRect( const DrawCoord::value_type &cornersR
                          , const DrawCoord             &leftTop
                          , const DrawCoord             &rightBottom
                          ) = 0;

    virtual bool rect( const DrawCoord             &leftTop
                     , const DrawCoord             &rightBottom
                     ) = 0;

    virtual  bool fillRect( const DrawCoord             &leftTop
                     , const DrawCoord             &rightBottom
                     ) = 0;

    virtual bool fillGradientRect( const DrawCoord             &leftTop
                                 , const DrawCoord             &rightBottom
                                 , const ColorRef              &gradientColorBegin
                                 , const ColorRef              &gradientColorMid
                                 , const ColorRef              &gradientColorEnd
                                 , const DrawCoord::value_type &gradientMidPoint
                                 , GradientType                gradientType
                                 , bool                        excludeFrame
                                 ) = 0;

    virtual bool fillGradientRect( const DrawCoord             &leftTop
                                 , const DrawCoord             &rightBottom
                                 , const GradientParams        &gradientParams
                                 , GradientType                gradientType
                                 , bool                        excludeFrame
                                 ) = 0;

    virtual bool fillGradientRoundRect( DrawCoord::value_type       cornersR
                                      , const DrawCoord             &leftTop
                                      , const DrawCoord             &rightBottom
                                      , const ColorRef              &gradientColorBegin
                                      , const ColorRef              &gradientColorMid
                                      , const ColorRef              &gradientColorEnd
                                      , const DrawCoord::value_type &gradientMidPoint
                                      , GradientType                gradientType
                                      , bool                        excludeFrame
                                      , DrawCoord::value_type       fillBreakPos
                                      , GradientRoundRectFillFlags  fillFlags // = GradientRoundRectFillFlags::roundBoth | GradientRoundRectFillFlags::fillFull
                                      ) = 0;

    virtual bool fillGradientRoundRect( DrawCoord::value_type       cornersR
                                      , const DrawCoord             &leftTop
                                      , const DrawCoord             &rightBottom
                                      , const GradientParams        &gradientParams
                                      , GradientType                gradientType
                                      , bool                        excludeFrame
                                      , DrawCoord::value_type       fillBreakPos
                                      , GradientRoundRectFillFlags  fillFlags // = GradientRoundRectFillFlags::roundBoth | GradientRoundRectFillFlags::fillFull
                                      ) = 0;

    virtual bool fillGradientCircle( const DrawCoord             &pos
                                   , const DrawCoord::value_type &r
                                   , const ColorRef              &gradientColorBegin
                                   , const ColorRef              &gradientColorMid
                                   , const ColorRef              &gradientColorEnd
                                   , const DrawCoord::value_type &gradientMidPoint
                                   , bool                        excludeFrame
                                   ) = 0;

    virtual bool fillGradientCircle( const DrawCoord             &pos
                                   , const DrawCoord::value_type &r
                                   , const GradientParams        &gradientParams
                                   , bool                        excludeFrame
                                   ) = 0;


// struct GradientParams
// {
//     ColorRef                 colorBegin;
//     ColorRef                 colorMid  ;
//     ColorRef                 colorEnd  ;
//  
//     DrawCoord::value_type    midPoint  = (DrawCoord::value_type)0.5;
//  
// }; // struct GradientParams

    // GradientType
    // vertical  ,
    // horizontal


    #if 0
    // Arc center is in the middle of the bounding rectangle (br)
    virtual bool arcTo ( const DrawCoord &brLeftTop
                       , const DrawCoord &brRightBottom
                       , const DrawCoord &brRightBottom
                       , const DrawCoord &centerPos ) = 0;

    // left, top, right, bottom of bounding rectangle

                    [in] int xr1,      // The x-coordinate, in logical units, of the endpoint of the radial defining the starting point of the arc.
                    [in] int yr1,      // The y-coordinate, in logical units, of the endpoint of the radial defining the starting point of the arc.

                    [in] int xr2,      // The x-coordinate, in logical units, of the endpoint of the radial defining the ending point of the arc.
                    [in] int yr2       // The y-coordinate, in logical units, of the endpoint of the radial defining the ending point of the arc.

    virtual bool arcTo ( const DrawCoord &to, const DrawCoord &centerPos ) = 0;
    virtual bool arcTo ( const DrawCoord &to, const DrawCoord &centerPos ) = 0;
    #endif


    //bool drawPath()


    class BkModeSaver
    {
        IDrawContext  *pDc;
        BkMode        prev;

        BkModeSaver();
        BkModeSaver(const BkModeSaver&);
        BkModeSaver(BkModeSaver&&);
        BkModeSaver& operator=(const BkModeSaver&);
        BkModeSaver& operator=(BkModeSaver&&);

    public:

        BkModeSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->setBkMode(BkMode::transparent))
        {
            pDc->setBkMode(prev);
        }

        BkModeSaver(IDrawContext *pDc_, BkMode newBkMode) : pDc(pDc_), prev(pDc_->setBkMode(newBkMode))
        {
        }

        ~BkModeSaver()
        {
            pDc->setBkMode(prev);
        }

    };


    class TextColorSaver
    {
        IDrawContext  *pDc;
        ColorRef      prev;

        TextColorSaver();
        TextColorSaver(const TextColorSaver&);
        TextColorSaver(TextColorSaver&&);
        TextColorSaver& operator=(const TextColorSaver&);
        TextColorSaver& operator=(TextColorSaver&&);

    public:

        TextColorSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getTextColor())
        {
        }

        TextColorSaver(IDrawContext *pDc_, ColorRef newColor) : pDc(pDc_), prev(pDc_->setTextColor(newColor))
        {
        }

        ~TextColorSaver()
        {
            pDc->setTextColor(prev);
        }

    };


    class FontSaver
    {
        IDrawContext  *pDc;
        int           prev;

        FontSaver();
        FontSaver(const FontSaver&);
        FontSaver(FontSaver&&);
        FontSaver& operator=(const FontSaver&);
        FontSaver& operator=(FontSaver&&);

    public:

        FontSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getCurFont())
        {
        }

        FontSaver(IDrawContext *pDc_, int newId) : pDc(pDc_), prev(pDc_->selectFont(newId))
        {
        }

        ~FontSaver()
        {
            pDc->selectFont(prev);
        }

    };


    class PenSaver
    {
        IDrawContext  *pDc;
        int           prev;

        PenSaver();
        PenSaver(const PenSaver&);
        PenSaver(PenSaver&&);
        PenSaver& operator=(const PenSaver&);
        PenSaver& operator=(PenSaver&&);

    public:

        PenSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getCurPen())
        {
        }

        PenSaver(IDrawContext *pDc_, int newId) : pDc(pDc_), prev(pDc_->selectPen(newId))
        {
        }

        ~PenSaver()
        {
            pDc->selectPen(prev);
        }

    };


    class BrushSaver
    {
        IDrawContext  *pDc;
        int           prev;

        BrushSaver();
        BrushSaver(const BrushSaver&);
        BrushSaver(BrushSaver&&);
        BrushSaver& operator=(const BrushSaver&);
        BrushSaver& operator=(BrushSaver&&);

    public:

        BrushSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getCurBrush())
        {
        }

        BrushSaver(IDrawContext *pDc_, int newId) : pDc(pDc_), prev(pDc_->selectBrush(newId))
        {
        }

        ~BrushSaver()
        {
            pDc->selectBrush(prev);
        }

    };


    class ScaleSaver
    {
        IDrawContext  *pDc;
        DrawScale     prev;

        ScaleSaver();
        ScaleSaver(const ScaleSaver&);
        ScaleSaver(ScaleSaver&&);
        ScaleSaver& operator=(const ScaleSaver&);
        ScaleSaver& operator=(ScaleSaver&&);

    public:

        ScaleSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getScale())
        {
        }

        ScaleSaver(IDrawContext *pDc_, const DrawScale &sc) : pDc(pDc_), prev(pDc_->setScale(sc))
        {
        }

        ~ScaleSaver()
        {
            pDc->setScale(prev);
        }

    };



    class OffsetSaver
    {
        IDrawContext  *pDc;
        DrawCoord     prev;

        OffsetSaver();
        OffsetSaver(const OffsetSaver&);
        OffsetSaver(OffsetSaver&&);
        OffsetSaver& operator=(const OffsetSaver&);
        OffsetSaver& operator=(OffsetSaver&&);

    public:

        OffsetSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getOffset())
        {
        }

        OffsetSaver(IDrawContext *pDc_, const DrawCoord &c ) : pDc(pDc_), prev(pDc_->setOffset(c))
        {
        }

        ~OffsetSaver()
        {
            pDc->setOffset(prev);
        }

    };


    class PenScaleSaver
    {
        IDrawContext  *pDc;
        float_t        prev;

        PenScaleSaver();
        PenScaleSaver(const PenScaleSaver&);
        PenScaleSaver(PenScaleSaver&&);
        PenScaleSaver& operator=(const PenScaleSaver&);
        PenScaleSaver& operator=(PenScaleSaver&&);

    public:

        PenScaleSaver(IDrawContext *pDc_) : pDc(pDc_), prev(pDc_->getPenScale())
        {
        }

        PenScaleSaver(IDrawContext *pDc_, float_t psc) : pDc(pDc_), prev(pDc_->setPenScale(psc))
        {
        }

        ~PenScaleSaver()
        {
            pDc->setPenScale(prev);
        }

    };

    // offset вычисляется по текущему scale
    // Обычно это и нужно. Масштаб, если меняется, задаётся позже
    class OffsetScaleSaver
    {
        OffsetSaver    offsetSaver  ;
        ScaleSaver     scaleSaver   ;
        PenScaleSaver  penScaleSaver;

        OffsetScaleSaver();
        OffsetScaleSaver(const OffsetScaleSaver&);
        OffsetScaleSaver(OffsetScaleSaver&&);
        OffsetScaleSaver& operator=(const OffsetScaleSaver&);
        OffsetScaleSaver& operator=(OffsetScaleSaver&&);

    public:

        OffsetScaleSaver(IDrawContext *pDc_)
        : offsetSaver(pDc_), scaleSaver(pDc_), penScaleSaver(pDc_)
        {
        }

        OffsetScaleSaver(IDrawContext *pDc_, const DrawCoord &c, const DrawScale &sc, float_t psc)
        : offsetSaver(pDc_, c), scaleSaver(pDc_, sc), penScaleSaver(pDc_, psc)
        {
        }

        OffsetScaleSaver(IDrawContext *pDc_, const DrawCoord &c, const DrawScale &sc)
        : offsetSaver(pDc_, c), scaleSaver(pDc_, sc), penScaleSaver(pDc_, sc.x)
        {
        }

        ~OffsetScaleSaver()
        {
        }

    };



    class DcObjectsSaver
    {
        FontSaver        fontSaver       ;
        PenSaver         penSaver        ;
        BrushSaver       brushSaver      ;
        BkModeSaver      bkModeSaver     ;
        TextColorSaver   textColorSaver  ;

        DcObjectsSaver();
        DcObjectsSaver(const DcObjectsSaver&);
        DcObjectsSaver(DcObjectsSaver&&);
        DcObjectsSaver& operator=(const DcObjectsSaver&);
        DcObjectsSaver& operator=(DcObjectsSaver&&);

    public:

        DcObjectsSaver(IDrawContext *pDc_)
        : fontSaver       (pDc_)
        , penSaver        (pDc_)
        , brushSaver      (pDc_)
        , bkModeSaver     (pDc_)
        , textColorSaver  (pDc_)
        {
        }

        ~DcObjectsSaver()
        {
        }

    };


    class DcResourceLiberator // Cleaner?
    {
        IDrawContext  *pDc;

        DcResourceLiberator();
        DcResourceLiberator(const DcResourceLiberator&);
        DcResourceLiberator(DcResourceLiberator&&);
        DcResourceLiberator& operator=(const DcResourceLiberator&);
        DcResourceLiberator& operator=(DcResourceLiberator&&);

    public:

        DcResourceLiberator(IDrawContext *pDc_) : pDc(pDc_)
        {
        }

        ~DcResourceLiberator()
        {
            pDc->freeAllocatedRc();
        }

    };



}; // struct IDrawContext






    // virtual ColorRef getTextColor( ) override
    // {
    //     auto prevColor = SetTextColor(m_hdc, RGB(0,0,0) ); // get prev color
    //     SetTextColor(m_hdc, prevColor ); // restore color
    //     return ColorRef{GetRValue(prevColor), GetGValue(prevColor), GetBValue(prevColor)};
    // }
    //
    //
    //
    // virtual BkMode setBkMode( BkMode mode ) override





} // namespace marty_draw_context





