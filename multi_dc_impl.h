#pragma once

/*
Мульти DC реализация IDrawContext'а.

Делегируем вызовы различным реализациям.

Предназначена прежде всего для Win32 - для микса GDI и GDI+.

GDI работает быстро, а в части отрисовки текста - даже более качественно, чем GDI+.
Также GDI хорош в отрисовке h/v pixel size линий, и у него быстрый bit blit.

GDI+ хорошо отрисовывает всю геометрию со сглаживанием, но очень тормозит.
Также GDI+ умеет в альфаканал и хорошо - в рескалинг битмапок.

Смешивать GDI и GDI+ возможно потому, что они оба работают с HDC.
Подобное теоретически возможно и на других системах, с различными графическими API,
если они работают поверх одних и тех же низкоуровневых поверхностей/сущностей,
а различные аспекты отрисовки реализуют с разным качеством.

```
enum class DrawingPrecise : std::uint32_t
{
    invalid            = (std::uint32_t)(-1),
    unknown            = (std::uint32_t)(-1),
    defPrecise         = 0,
    pixelPrecise       = 1,
    textPrecise        = 2,
    smoothingPrecise   = 3

}; // enum class DrawingPrecise : std::uint32_t

virtual DrawingPrecise setDrawingPrecise(DrawingPrecise p) = 0;
virtual DrawingPrecise getDrawingPrecise() = 0;
```

По DrawingPrecise переключаем низлежащие указатели на IDrawContext'ы.
Но при этом переключаются и все ресурсы (pen/brush/font), созданные в DrawContext'е.
Тут может быть два варианта:
1) Очень аккуратно создаём ресурсы и используем их - в одном и том же DrawingPrecise режиме.
Но тут можно легко накосячить.
2) Создаем ресурсы во всех объектах - тут можно не беспокоится о том, в каком DrawingPrecise режиме был создан ресурс.
Но накладные расходы возрастают кратно количеству использованных низлежащих IDrawContext'ов. Пока это только 2: GDI и GDI+,
да и ресурсы (pen/brush/font) сейчас стоят копейки, чай не Win3.1 на 286ом. Только шрифты могут занимать значительное количество памяти
Ну, ещё можно говорить об увеличении времени на вызовы, созданиющие ресурсы - они будут производится для всех низлежащих IDrawContext'ов.
Но это тоже крошки, в общем-то.


 */


#include "i_draw_context.h"
#include "assert.h"

#include <exception>
#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>



namespace marty_draw_context {




struct MultiDrawContext : public IDrawContext
{

    typedef DrawCoord::value_type                 float_t;


    std::string                                   engineName;

    std::shared_ptr<IDrawContext>                 defDc       = 0;
    std::shared_ptr<IDrawContext>                 pixelDc     = 0;
    std::shared_ptr<IDrawContext>                 textDc      = 0;
    std::shared_ptr<IDrawContext>                 smoothingDc = 0;


protected:

    std::vector< std::shared_ptr<IDrawContext> >  m_preciseHandlers;

    std::vector< std::shared_ptr<IDrawContext> >  m_allUniques;
    std::shared_ptr<IDrawContext>                 m_firstImpl ;

    DrawingPrecise                                m_drawingPrecise = DrawingPrecise::defPrecise;



public:

    MultiDrawContext()
    : defDc      (0)
    , pixelDc    (0)
    , textDc     (0)
    , smoothingDc(0)
    , m_preciseHandlers()
    , m_allUniques()
    , m_firstImpl(0)
    , m_drawingPrecise(DrawingPrecise::defPrecise)
    {}

    virtual ~MultiDrawContext() override
    {
    
    }



protected:

    bool checkIsAddedToUnique(std::shared_ptr<IDrawContext> pDc) const
    {
        std::vector< std::shared_ptr<IDrawContext> >::const_iterator it = m_allUniques.begin();
        for(; it!=m_allUniques.end(); ++it)
        {
            if (it->get()==pDc.get())
            {
                return true;
            }
        }

        return false;
    }

    bool addToUnique(std::shared_ptr<IDrawContext> pDc)
    {
        if (checkIsAddedToUnique(pDc))
        {
            return false; // already exist
        }

        m_allUniques.emplace_back(pDc);

        return true;
    }


public:

    void init()
    {
        m_preciseHandlers.clear();
        m_allUniques.clear();

        m_preciseHandlers.emplace_back(defDc      ); // defPrecise         = 0,
        m_preciseHandlers.emplace_back(pixelDc    ); // pixelPrecise       = 1,
        m_preciseHandlers.emplace_back(textDc     ); // textPrecise        = 2,
        m_preciseHandlers.emplace_back(smoothingDc); // smoothingPrecise   = 3 

        std::shared_ptr<IDrawContext> nonNullDc = 0;

        // Находим первый ненулевой
        for(auto &&p : m_preciseHandlers)
        {
            if (p.get()!=0)
            {
                nonNullDc = p;
                break;
            }
        }

        MARTY_IDC_ASSERT(nonNullDc.get()!=0);
        if (nonNullDc.get()==0)
        {
            throw std::runtime_error("MultiDrawContext::init: no valid pDc found");
        }

        // Задаём все нулевые ненулевым
        for(auto &&p : m_preciseHandlers)
        {
            if (p.get()==0)
            {
                p = nonNullDc;
            }
        }

        // Получаем уникальные
        for(auto &&p : m_preciseHandlers)
        {
            addToUnique(p);
        }

        MARTY_IDC_ASSERT(!m_allUniques.empty());
        if (m_allUniques.empty())
        {
            throw std::runtime_error("MultiDrawContext::init: no valid unique pDc found");
        }

        // Извлекаем первый
        m_firstImpl = m_allUniques[0];
        m_allUniques.erase(m_allUniques.begin());
    }

    
protected:

    bool isValidDrawingPrecise(DrawingPrecise p) const
    {
        if ( p==DrawingPrecise::defPrecise      
          || p==DrawingPrecise::pixelPrecise    
          || p==DrawingPrecise::textPrecise     
          || p==DrawingPrecise::smoothingPrecise
           )
        {
            return true;
        }

        return false;
    }

    DrawingPrecise getActualDrawingPrecise(DrawingPrecise p) const
    {
        if (!isValidDrawingPrecise(p))
        {
            return DrawingPrecise::defPrecise;
        }

        return p;
    }

    DrawingPrecise getActualDrawingPrecise() const
    {
        return getActualDrawingPrecise(m_drawingPrecise);
    }

    std::shared_ptr<IDrawContext> getActiveDc(DrawingPrecise p) const
    {
        return m_preciseHandlers[(std::size_t)getActualDrawingPrecise(p)];
    }

    std::shared_ptr<IDrawContext> getActiveDc() const
    {
        return m_preciseHandlers[(std::size_t)getActualDrawingPrecise()];
    }


    struct AtScopeExit
    {
        std::function<void()> guard;
        ~AtScopeExit() { guard(); }
    };

    template <typename F>
    decltype(auto) delegateCallAll(F&& f)
    {
       const AtScopeExit callTail
       { [&]
         {
            for (auto&& impl : m_allUniques)
            {
               f(*impl);
            }
         }
       };

       return f(*m_firstImpl);
    }


    typedef IDrawContext I;
    // { return doDelegate([&](I& i) { return i.getter(); }); }

public:

    std::string getEngineName() override
    {
        return engineName;
    }


    DrawingPrecise setDrawingPrecise(DrawingPrecise p) override
    {
        if (m_drawingPrecise==p)
        {
            return p;
        }

        if (!isValidDrawingPrecise(p))
        {
            return DrawingPrecise::invalid;
        }

        getActiveDc()->flushBits();

        auto drawingPrecisePrev = m_drawingPrecise;
        m_drawingPrecise = p;

        // Тут для нового активного pDc нужно вызвать что-то типа activeDrawContextChanged и передать туда указатель на предыдущий DC (1)
        // Или для предыдущего активного pDc нужно вызвать activeDrawContextChanged и передать туда указатель на новый DC             (2)
        // При разрушении MultiDrawContext нужно вызвать для активного DC с нулем в качестве параметра. Это лучше соотносится с (2)

        return drawingPrecisePrev;
    }

    DrawingPrecise getDrawingPrecise() override
    {
        return m_drawingPrecise;
    }

    void flushBits() override { return getActiveDc()->flushBits(); }

    void setStringEncoding(const std::string &encName) override { return delegateCallAll([&](I& i) { return i.setStringEncoding(encName); }); }
    std::string getStringEncoding() override                    { return getActiveDc()->getStringEncoding(); }
    void logFontsInfo() override                                { getActiveDc()->logFontsInfo(); }
    void freeAllocatedRc() override                             { return delegateCallAll([&](I& i) { return i.freeAllocatedRc(); }); }
    SmoothingMode setSmoothingMode( SmoothingMode m ) override  { return delegateCallAll([&](I& i) { return i.setSmoothingMode(m); }); }
    SmoothingMode getSmoothingMode( ) override                  { return getActiveDc()->getSmoothingMode(); }
    bool setCollectMarkers( bool cmMode ) override              { return delegateCallAll([&](I& i) { return i.setCollectMarkers(cmMode); }); }
    bool getCollectMarkers( ) override                          { return getActiveDc()->getCollectMarkers(); }
    bool markerAdd( const DrawCoord &pos, const DrawCoord::value_type sz ) override { return delegateCallAll([&](I& i) { return i.markerAdd(pos, sz); }); }
    bool markerAdd( const DrawCoord &pos ) override             { return delegateCallAll([&](I& i) { return i.markerAdd(pos); }); }
    void markersClear( ) override                               { return delegateCallAll([&](I& i) { return i.markersClear(); }); }
    void markersDraw( int penId ) override                      { getActiveDc()->markersDraw(penId); }
    DrawCoord::value_type markerSetDefSize( const DrawCoord::value_type &sz ) override { return delegateCallAll([&](I& i) { return i.markerSetDefSize(sz); }); }
    DrawCoord::value_type markerGetDefSize( ) override          { return getActiveDc()->markerGetDefSize(); }

    DcResourcesState getResourcesState() override               { return getActiveDc()->getResourcesState(); }
    void restoreResourcesState(const DcResourcesState &rcState) override { return delegateCallAll([&](I& i) { return i.restoreResourcesState(rcState); }); }

    std::size_t getCharLen     (const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override { return getActiveDc()->getCharLen(text, textSize); }
    std::size_t getTextCharsLen(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override { return getActiveDc()->getTextCharsLen(text, textSize); }
    std::size_t getTextCharsLenEx(DrawTextFlags flags, const wchar_t *text, std::size_t textSize=(std::size_t)-1, const wchar_t *skipChars=0) const override { return getActiveDc()->getTextCharsLenEx(flags, text, textSize, skipChars); }
    std::uint32_t getChar32(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override     { return getActiveDc()->getChar32(text, textSize); }
    bool getCharWidths(std::vector<float_t> &widths, const wchar_t *text, std::size_t textSize=(std::size_t)-1, int fontId=-1 /* use current font */ ) const override { return getActiveDc()->getCharWidths(widths, text, textSize, fontId); }

    DrawCoord::value_type mapRawToLogicSizeX( const DrawCoord::value_type &c ) const override { return getActiveDc()->mapRawToLogicSizeX(c); }
    DrawCoord::value_type mapRawToLogicSizeY( const DrawCoord::value_type &c ) const override { return getActiveDc()->mapRawToLogicSizeY(c); }
    DrawCoord::value_type getScaledSizeX( const DrawCoord::value_type &c ) const override     { return getActiveDc()->getScaledSizeX(c); }
    DrawCoord::value_type getScaledSizeY( const DrawCoord::value_type &c ) const override     { return getActiveDc()->getScaledSizeY(c); }

    DrawCoord             getPixelSize () const override     { return getActiveDc()->getPixelSize (); }
    DrawCoord::value_type getPixelSizeX() const override     { return getActiveDc()->getPixelSizeX(); }
    DrawCoord::value_type getPixelSizeY() const override     { return getActiveDc()->getPixelSizeY(); }


    float_t getFitFontHeight(const DrawSize &boxSize) override  { return getActiveDc()->getFitFontHeight(boxSize); }
    float_t getAwgFontWidth(const FontParamsA &fp) override     { return getActiveDc()->getAwgFontWidth(fp); }
    float_t getAwgFontWidth(const FontParamsW &fp) override     { return getActiveDc()->getAwgFontWidth(fp); }
    float_t getFitMarginWidth(const FontParamsA &fp) override   { return getActiveDc()->getFitMarginWidth(fp); }
    float_t getFitMarginWidth(const FontParamsW &fp) override   { return getActiveDc()->getFitMarginWidth(fp); }

    DrawSize getDialigBaseUnits() override                      { return getActiveDc()->getDialigBaseUnits(); }

    DrawCoord mapRawToLogicPos( const DrawCoord &c  ) const override  { return getActiveDc()->mapRawToLogicPos (c); }
    DrawCoord mapRawToLogicSize( const DrawCoord &c ) const override  { return getActiveDc()->mapRawToLogicSize(c); }

    DrawCoord getScaledPos( const DrawCoord &c  ) const override { return getActiveDc()->getScaledPos (c); }
    DrawCoord getScaledSize( const DrawCoord &c ) const override { return getActiveDc()->getScaledSize(c); }


    DrawCoord setOffset( const DrawCoord &c ) override           { return delegateCallAll([&](I& i) { return i.setOffset(c); }); }
    DrawCoord getOffset( ) override                              { return getActiveDc()->getOffset(); }

    DrawScale setScale( const DrawScale &scale ) override        { return delegateCallAll([&](I& i) { return i.setScale(scale); }); }
    DrawScale getScale( ) override                               { return getActiveDc()->getScale(); }

    float_t setPenScale( float_t scale ) override                { return delegateCallAll([&](I& i) { return i.setPenScale(scale); }); }
    float_t getPenScale( ) override                              { return getActiveDc()->getPenScale(); }

    DcOffsetScale getOffsetScale() override                      { return getActiveDc()->getOffsetScale(); }
    void restoreOffsetScale(const DcOffsetScale &dcOs) override  { return delegateCallAll([&](I& i) { return i.restoreOffsetScale(dcOs); }); }


    DrawCoord getCurPos( ) override                              { return getActiveDc()->getCurPos(); }

    int createSolidBrush( const ColorRef &rgb ) override
    {
        return delegateCallAll( [&](I& i) 
                                {
                                    return i.createSolidBrush(rgb);
                                }
                              );
    }

    int createSolidBrush( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override
    {
        return delegateCallAll( [&](I& i)
                                {
                                    return i.createSolidBrush(r, g, b);
                                }
                              );
    }

    int selectBrush( int brushId ) override
    {
        return delegateCallAll( [&](I& i)
                                {
                                    return i.selectBrush(brushId);
                                }
                              );
    }

    // returns new brushId, not prev
    int selectNewSolidBrush( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override
    {
        return delegateCallAll( [&](I& i)
                                {
                                    return i.selectNewSolidBrush(r, g, b);
                                }
                              );
    }

    int selectNewSolidBrush( const ColorRef &rgb ) override
    {
        return delegateCallAll( [&](I& i)
                                {
                                    return i.selectNewSolidBrush(rgb);
                                }
                              );
    }

    int getCurBrush() override                                   { return getActiveDc()->getCurBrush(); }


    int  createFont( float_t height, int escapement, int orientation, FontWeight weight, FontStyleFlags fontStyleFlags, const char    *fontFace ) override
         { return delegateCallAll([&](I& i) { return i.createFont(height, escapement, orientation, weight, fontStyleFlags, fontFace); }); }
    int  createFont( float_t height, int escapement, int orientation, FontWeight weight, FontStyleFlags fontStyleFlags, const wchar_t *fontFace ) override
         { return delegateCallAll([&](I& i) { return i.createFont(height, escapement, orientation, weight, fontStyleFlags, fontFace); }); }
    int  createFont( const FontParamsA &fp ) override            { return delegateCallAll([&](I& i) { return i.createFont(fp); }); }
    int  createFont( const FontParamsW &fp ) override            { return delegateCallAll([&](I& i) { return i.createFont(fp); }); }
    int  createFont( FontParamsA fp, const FontParamsA::string_type &fontFace ) override { return delegateCallAll([&](I& i) { return i.createFont(fp, fontFace); }); }
    int  createFont( FontParamsW fp, const FontParamsW::string_type &fontFace ) override { return delegateCallAll([&](I& i) { return i.createFont(fp, fontFace); }); }

    int  makeFontByParams( const FontParamsA &fp ) override      { return delegateCallAll([&](I& i) { return i.makeFontByParams(fp); }); }
    int  makeFontByParams( const FontParamsW &fp ) override      { return delegateCallAll([&](I& i) { return i.makeFontByParams(fp); }); }
    int  makeFontByParams( FontParamsA fp, float_t height ) override { return delegateCallAll([&](I& i) { return i.makeFontByParams(fp, height); }); }
    int  makeFontByParams( FontParamsW fp, float_t height ) override { return delegateCallAll([&](I& i) { return i.makeFontByParams(fp, height); }); }

    int  selectFont( int fontId ) override                       { return delegateCallAll([&](I& i) { return i.selectFont(fontId); }); }

    // returns new fontId, not prev
    int  selectNewFont( const FontParamsA &fp ) override         { return delegateCallAll([&](I& i) { return i.selectNewFont(fp); }); }
    int  selectNewFont( const FontParamsW &fp ) override         { return delegateCallAll([&](I& i) { return i.selectNewFont(fp); }); }

    virtual int  getCurFont() override                           { return getActiveDc()->getCurFont(); }

    std::wstring decodeString( const std::string &str ) override { return getActiveDc()->decodeString(str); }
    bool textOut( const DrawCoord &pos, const wchar_t *text, size_t textSize) override  { return getActiveDc()->textOut(pos, text, textSize); }
    bool textOut( const DrawCoord &pos, const char    *text, size_t textSize) override  { return getActiveDc()->textOut(pos, text, textSize); }
    bool textOut( const DrawCoord &pos, const std::string &text ) override  { return getActiveDc()->textOut(pos, text); }
    bool textOut( const DrawCoord &pos, const std::wstring &text ) override { return getActiveDc()->textOut(pos, text); }
    bool textOut( const DrawCoord &pos, int fontId, const ColorRef &rgb, const std::string &text ) override  { return getActiveDc()->textOut(pos, fontId, rgb, text); }
    bool textOut( const DrawCoord &pos, int fontId, const ColorRef &rgb, const std::wstring &text ) override { return getActiveDc()->textOut(pos, fontId, rgb, text); }

    bool drawTextColoredEx( const DrawCoord               &startPos
                          , const DrawCoord::value_type   &widthLim
                          , DrawCoord::value_type         *pNextPosX //!< OUT, Положение вывода для символа, следующего за последним выведенным
                          , DrawCoord::value_type         *pOverhang //!< OUT, Вынос элементов символа за пределы NextPosX - актуально, как минимум, для iatalic стиля шрифта
                          , DrawTextFlags                 flags
                          , const wchar_t                 *text
                          , std::size_t                   textSize=(std::size_t)-1
                          , std::uint32_t                 *pLastCharProcessed = 0 //!< IN/OUT last drawn char, for kerning calculation
                          , std::size_t                   *pCharsProcessed=0 //!< OUT Num chars, not symbols/glyphs
                          , const std::uint32_t           *pColors=0
                          , std::size_t                   nColors=0
                          , std::size_t                   *pSymbolsDrawn=0
                          , const wchar_t                 *stopChars=0
                          , int                           fontId=-1
                          ) override
    {
        return getActiveDc()->drawTextColoredEx(startPos, widthLim, pNextPosX, pOverhang, flags, text, textSize, pLastCharProcessed, pCharsProcessed, pColors, nColors, pSymbolsDrawn, stopChars, fontId);
    }

    // bool drawTextColored( const DrawCoord               &startPos
    //                     , const DrawCoord::value_type   &xPosMax
    //                     , DrawCoord::value_type         *pNextPosX //!< OUT, Положение вывода для символа, следующего за последним выведенным
    //                     , DrawCoord::value_type         *pOverhang //!< OUT, Вынос элементов символа за пределы NextPosX - актуально, как минимум, для iatalic стиля шрифта
    //                     , DrawTextFlags                 flags
    //                     , const char                    *text
    //                     , std::size_t                   textSize=(std::size_t)-1
    //                     , std::size_t                   *pCharsProcessed=0 //!< OUT Num chars, not symbols/glyphs
    //                     , const std::uint32_t           *pColors=0
    //                     , std::size_t                   nColors=0
    //                     , std::size_t                   *pSymbolsDrawn=0
    //                     , const char                    *stopChars=0
    //                     , int                           fontId=-1
    //                     ) override
    // {
    //     return getActiveDc()->drawTextColored(startPos, xPosMax, pNextPosX, pOverhang, flags, text, textSize, pCharsProcessed, pColors, nColors, pSymbolsDrawn, stopChars, fontId);
    // }

    bool drawTextColored  ( const DrawCoord               &startPos
                          , const DrawCoord::value_type   &widthLim
                          , DrawTextFlags                 flags
                          , const wchar_t                 *text
                          , std::size_t                   textSize=(std::size_t)-1
                          , const std::uint32_t           *pColors=0
                          , std::size_t                   nColors=0
                          , const wchar_t                 *stopChars=0
                          , int                           fontId=-1
                          ) override
    {
        return getActiveDc()->drawTextColored(startPos, widthLim, flags, text, textSize, pColors, nColors, stopChars, fontId);
    }

    bool drawParaColoredEx( const DrawCoord                       &startPos
                          , const DrawCoord                       &limits       //!< Limits, vertical and horizontal, relative to start pos
                          , DrawCoord::value_type                 *pNextPosY    //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                          bool                                    *pVerticalDone
                          , const DrawCoord::value_type           &lineSpacing  //!< Extra space between lines of text
                          , const DrawCoord::value_type           &paraIndent   //!< Indent on the first line
                          , const DrawCoord::value_type           &tabSize      //!< Size used for tabs if tabStops are over
                          , DrawTextFlags                         flags
                          , HorAlign                              horAlign
                          , VertAlign                             vertAlign
                          , const wchar_t                         *text
                          , std::size_t                           textSize=(std::size_t)-1
                          , std::size_t                           *pCharsProcessed=0 //!< OUT Num chars, not symbols/glyphs
                          , const std::uint32_t                   *pColors=0
                          , std::size_t                           nColors=0
                          , const DrawCoord::value_type           *pTabStopPositions=0        //!< Relative to start pos X coord
                          , std::size_t                           nTabStopPositions=0
                          , int                                   fontId=-1
                          ) override
    {
        return getActiveDc()->drawParaColoredEx( startPos, limits, pNextPosY, pVerticalDone, lineSpacing, paraIndent, tabSize, flags
                                               , horAlign, vertAlign, text, textSize, pCharsProcessed
                                               , pColors, nColors, pTabStopPositions, nTabStopPositions
                                               , fontId
                                               );
    }

    bool getSimpleFontMetrics(SimpleFontMetrics &m, int fontId=-1) const override { return getActiveDc()->getSimpleFontMetrics(m, fontId); }
    bool getKerningPairs(std::vector<KerningPair> &pairs, int fontId=-1) const override { return getActiveDc()->getKerningPairs(pairs, fontId); }
    float_t getKerningValue( const std::unordered_set<KerningPair> &pairs, std::uint32_t chFirst, std::uint32_t chSecond) const override { return getActiveDc()->getKerningValue(pairs, chFirst, chSecond); }

    bool getCharWidth (std::uint32_t ch, float_t &w) const override                        { return getActiveDc()->getCharWidth(ch, w); }
    bool getCharWidth (std::uint32_t ch, float_t &w, int fontId /* =-1 */ ) const override { return getActiveDc()->getCharWidth(ch, w, fontId); }


    bool isArabicDigitChar(std::uint32_t ch) const override          { return getActiveDc()->isArabicDigitChar(ch); }
    bool isLatinLetterChar(std::uint32_t ch) const override          { return getActiveDc()->isLatinLetterChar(ch); }
    bool isAnySpaceChar(std::uint32_t ch) const override             { return getActiveDc()->isAnySpaceChar(ch); }
    bool isAnyNonBreakingSpaceChar(std::uint32_t ch) const override  { return getActiveDc()->isAnyNonBreakingSpaceChar(ch); }
    bool isAnyBreakingSpaceChar(std::uint32_t ch) const override     { return getActiveDc()->isAnyBreakingSpaceChar(ch); }
    bool isAnyNonBreakingDashChar(std::uint32_t ch) const override   { return getActiveDc()->isAnyNonBreakingDashChar(ch); }
    bool isAnyBreakingDashChar(std::uint32_t ch) const override      { return getActiveDc()->isAnyBreakingDashChar(ch); }
    bool isAnyDashChar(std::uint32_t ch) const override              { return getActiveDc()->isAnyDashChar(ch); }
    bool isAnyTabChar(std::uint32_t ch) const override               { return getActiveDc()->isAnyTabChar(ch); }
    bool isAnyLineBreakChar(std::uint32_t ch) const override         { return getActiveDc()->isAnyLineBreakChar(ch); }
    bool isAnyWhiteSpaceChar(std::uint32_t ch) const override        { return getActiveDc()->isAnyWhiteSpaceChar(ch); }
    bool isLineBreak(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override            { return getActiveDc()->isLineBreak(text, textSize); }
    std::size_t getLineBreakLen(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override { return getActiveDc()->getLineBreakLen(text, textSize); }

    // virtual DrawCoord::value_type getFonSizeFitHeigh( const FontParamsA &fp, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text /* , const std::string  &fontFace="Courier New"  */ , HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override

    bool getFontParamsById( int id, FontParamsA &fp ) override   { return getActiveDc()->getFontParamsById(id, fp); }
    bool getFontParamsById( int id, FontParamsW &fp ) override   { return getActiveDc()->getFontParamsById(id, fp); }

    int getMonospacedFontCharWidthApprox(const FontParamsA &fp) override { return getActiveDc()->getMonospacedFontCharWidthApprox(fp); }
    int getMonospacedFontCharWidthApprox(const FontParamsW &fp) override { return getActiveDc()->getMonospacedFontCharWidthApprox(fp); }
    int getMonospacedFontCharWidthApprox(int fontId) override            { return getActiveDc()->getMonospacedFontCharWidthApprox(fontId); }

    int getProportionalFontCharWidthScaleApprox(const FontParamsA &fp) override { return getActiveDc()->getProportionalFontCharWidthScaleApprox(fp); }
    int getProportionalFontCharWidthScaleApprox(const FontParamsW &fp) override { return getActiveDc()->getProportionalFontCharWidthScaleApprox(fp); }

    bool drawTextFitHeigh  ( const FontParamsA &fp,                                        const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override { return getActiveDc()->drawTextFitHeigh  (fp,                  rectPos, rectSize, text, a, xMarginScale, pTextPos, pTextSize); }
    bool drawTextFitHeigh  ( const FontParamsW &fp,                                        const DrawCoord &rectPos, const DrawCoord &rectSize, const std::wstring &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override { return getActiveDc()->drawTextFitHeigh  (fp,                  rectPos, rectSize, text, a, xMarginScale, pTextPos, pTextSize); }
    bool drawTextFitHeighEx( const FontParamsA &fp, DrawCoord::value_type fontHeightScale, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override { return getActiveDc()->drawTextFitHeighEx(fp, fontHeightScale, rectPos, rectSize, text, a, xMarginScale, pTextPos, pTextSize); }
    bool drawTextFitHeighEx( const FontParamsW &fp, DrawCoord::value_type fontHeightScale, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::wstring &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override { return getActiveDc()->drawTextFitHeighEx(fp, fontHeightScale, rectPos, rectSize, text, a, xMarginScale, pTextPos, pTextSize); }

    // !!! TODO нужно сделать версии получения ширины символа для FontParamsA/W/id и для char/wchar_t - всего 6 штук
    // Только латинские символы (потом, может, добавлю национальные)
    // Фонт не принципиален
    // Нужно для реализации calcDrawnTextWidthApprox
    int getProportionalFontCharWidthApprox(const FontParamsA &fp, char    ch) override      { return getActiveDc()->getProportionalFontCharWidthApprox(fp, ch); }
    int getProportionalFontCharWidthApprox(const FontParamsA &fp, wchar_t ch) override      { return getActiveDc()->getProportionalFontCharWidthApprox(fp, ch); }

    int getProportionalFontCharWidthApprox(const FontParamsW &fp, char    ch) override      { return getActiveDc()->getProportionalFontCharWidthApprox(fp, ch); }
    int getProportionalFontCharWidthApprox(const FontParamsW &fp, wchar_t ch) override      { return getActiveDc()->getProportionalFontCharWidthApprox(fp, ch); }

    int getFontCharWidthApprox(int fontId, char    ch, int scale = 100) override            { return getActiveDc()->getFontCharWidthApprox(fontId, ch, scale); }
    int getFontCharWidthApprox(int fontId, wchar_t ch, int scale = 100) override            { return getActiveDc()->getFontCharWidthApprox(fontId, ch, scale); }

    int getFontCharWidthApprox(const FontParamsA &fp, char    ch, int scale = 100) override { return getActiveDc()->getFontCharWidthApprox(fp, ch, scale); }
    int getFontCharWidthApprox(const FontParamsA &fp, wchar_t ch, int scale = 100) override { return getActiveDc()->getFontCharWidthApprox(fp, ch, scale); }

    int getFontCharWidthApprox(const FontParamsW &fp, char    ch, int scale = 100) override { return getActiveDc()->getFontCharWidthApprox(fp, ch, scale); }
    int getFontCharWidthApprox(const FontParamsW &fp, wchar_t ch, int scale = 100) override { return getActiveDc()->getFontCharWidthApprox(fp, ch, scale); }


    float_t calcDrawnTextWidthApprox(const FontParamsA &fp, const char*    text, std::size_t nChars, int widthScale = 100) override { return getActiveDc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale); }
    float_t calcDrawnTextWidthApprox(const FontParamsW &fp, const char*    text, std::size_t nChars, int widthScale = 100) override { return getActiveDc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale); }
    float_t calcDrawnTextWidthApprox(const FontParamsA &fp, const wchar_t* text, std::size_t nChars, int widthScale = 100) override { return getActiveDc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale); }
    float_t calcDrawnTextWidthApprox(const FontParamsW &fp, const wchar_t* text, std::size_t nChars, int widthScale = 100) override { return getActiveDc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale); }

    float_t calcDrawnTextWidthApprox(int   fontId         , const char*    text, std::size_t nChars, int widthScale = 100) override { return getActiveDc()->calcDrawnTextWidthApprox(fontId, text, nChars, widthScale); }
    float_t calcDrawnTextWidthApprox(int   fontId         , const wchar_t* text, std::size_t nChars, int widthScale = 100) override { return getActiveDc()->calcDrawnTextWidthApprox(fontId, text, nChars, widthScale); }

    DrawSize calcDrawnTextSizeExact (int   fontId         , const char*    text, std::size_t nChars) override { return getActiveDc()->calcDrawnTextSizeExact(fontId, text, nChars); }
    DrawSize calcDrawnTextSizeExact (int   fontId         , const wchar_t* text, std::size_t nChars) override { return getActiveDc()->calcDrawnTextSizeExact(fontId, text, nChars); }

    ColorRef setTextColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override { return delegateCallAll([&](I& i) { return i.setTextColor(r,g,b); }); }
    ColorRef setBkColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override   { return delegateCallAll([&](I& i) { return i.setBkColor(r,g,b); }); }
    ColorRef setTextColor( const ColorRef &rgb ) override { return delegateCallAll([&](I& i) { return i.setTextColor(rgb); }); }
    ColorRef setBkColor( const ColorRef &rgb ) override   { return delegateCallAll([&](I& i) { return i.setBkColor(rgb); }); }
    ColorRef getTextColor( ) override                     { return getActiveDc()->getTextColor(); }
    ColorRef getBkColor() override                        { return getActiveDc()->getBkColor(); }

    BkMode setBkMode( BkMode mode ) override              { return delegateCallAll([&](I& i) { return i.setBkMode(mode); }); }
    BkMode getBkMode() override                           { return getActiveDc()->getBkMode(); }

    int setDefaultCosmeticPen( int penId ) override       { return delegateCallAll([&](I& i) { return i.setDefaultCosmeticPen(penId); }); }
    int getDefaultCosmeticPen( ) override                 { return getActiveDc()->getDefaultCosmeticPen(); }

    int createSolidPen( float_t width, LineEndcapStyle endcaps, LineJoinStyle join
                      , std::uint8_t r, std::uint8_t g, std::uint8_t b
                      ) override
        { return delegateCallAll([&](I& i) { return i.createSolidPen(width, endcaps, join, r, g, b); }); }

    int createSolidPen( float_t width, LineEndcapStyle endcaps, LineJoinStyle join
                      , const ColorRef &rgb
                      ) override
        { return delegateCallAll([&](I& i) { return i.createSolidPen(width, endcaps, join, rgb); }); }

    int createSolidPen( const PenParams &penParams, const ColorRef &colorRef ) override    { return delegateCallAll([&](I& i) { return i.createSolidPen(penParams, colorRef); }); }
    int createSolidPen( const PenParamsWithColor &penParams ) override                     { return delegateCallAll([&](I& i) { return i.createSolidPen(penParams); }); }
    int selectPen( int penId ) override                                                    { return delegateCallAll([&](I& i) { return i.selectPen(penId); }); }

    // returns newly created penId, not previously selected penId
    int selectNewSolidPen( const PenParams &penParams, const ColorRef &colorRef ) override { return delegateCallAll([&](I& i) { return i.selectNewSolidPen(penParams, colorRef); }); }
    int selectNewSolidPen( const PenParamsWithColor &penParams ) override                  { return delegateCallAll([&](I& i) { return i.selectNewSolidPen(penParams); }); }          

    int getCurPen() override                 { return getActiveDc()->getCurPen(); }

    ColorRef  getPenColor (int penId) override { return getActiveDc()->getPenColor(penId); }
    PenParams getPenParams(int penId) override { return getActiveDc()->getPenParams(penId); }


    bool beginPath()                                override         { return getActiveDc()->beginPath(); }
    bool beginPath( const DrawCoord &to )           override         { return getActiveDc()->beginPath(to); }
    bool endPath( bool bStroke = true, bool bFill = false ) override { return getActiveDc()->endPath(bStroke, bFill); }
    bool closeFigure()                              override         { return getActiveDc()->closeFigure(); }
    bool isPathStarted() override                                    { return getActiveDc()->isPathStarted(); }

    bool moveTo( const DrawCoord &to ) override                      { return getActiveDc()->moveTo(to); }
    bool lineTo( const DrawCoord &to ) override                      { return getActiveDc()->lineTo(to); }

    bool ellipticArcTo( const DrawCoord &leftTop
                      , const DrawCoord &rightBottom
                      , const DrawCoord &arcStartRefPoint
                      , const DrawCoord &arcEndRefPoint
                      , bool             directionCounterclockwise
                      ) override
                      { return getActiveDc()->ellipticArcTo(leftTop, rightBottom, arcStartRefPoint, arcEndRefPoint, directionCounterclockwise); }

    bool arcTo(const DrawCoord &centerPos, const DrawCoord &endPos, bool directionCounterclockwise, DrawCoord *pResEndPos = 0 ) override { return getActiveDc()->arcTo(centerPos, endPos, directionCounterclockwise, pResEndPos); }
    bool arcTo(const DrawCoord &centerPos, const DrawCoord::value_type angleGradus, DrawCoord *pResEndPos = 0 ) override                 { return getActiveDc()->arcTo(centerPos, angleGradus, pResEndPos); }

    bool ellipse    (const DrawCoord &leftTop, const DrawCoord &rightBottom) override                    { return getActiveDc()->ellipse(leftTop, rightBottom); }
    bool fillEllipse(const DrawCoord &leftTop, const DrawCoord &rightBottom, bool drawFrame) override    { return getActiveDc()->fillEllipse(leftTop, rightBottom, drawFrame); }
    
    bool circle    (const DrawCoord &centerPos, const DrawCoord::value_type &r) override                 { return getActiveDc()->circle(centerPos, r); }
    bool fillCircle(const DrawCoord &centerPos, const DrawCoord::value_type &r, bool drawFrame) override { return getActiveDc()->fillCircle(centerPos, r, drawFrame); }

    //! Рисует набор горизонтальных и вертикальных линий, если две точки задают диагональную линию - это ошибка
    bool roundRectFigure( const DrawCoord::value_type &cornersR
                        , std::size_t numPoints
                        , const DrawCoord             *pPoints
                        ) override
                        { return getActiveDc()->roundRectFigure(cornersR, numPoints, pPoints); }

    //! Implemented offten with serios of the lineTo and ellipticArcTo calls
    bool roundRect( const DrawCoord::value_type &cornersR
                  , const DrawCoord             &leftTop
                  , const DrawCoord             &rightBottom
                  ) override
                  { return getActiveDc()->roundRect(cornersR, leftTop, rightBottom); }

    bool fillRoundRect( const DrawCoord::value_type &cornersR
                  , const DrawCoord             &leftTop
                  , const DrawCoord             &rightBottom
                  , bool                         drawFrame
                  ) override
                  { return getActiveDc()->fillRoundRect(cornersR, leftTop, rightBottom, drawFrame); }

    bool rect( const DrawCoord             &leftTop
             , const DrawCoord             &rightBottom
             ) override
             { return getActiveDc()->rect(leftTop, rightBottom); }

    bool fillRect( const DrawCoord             &leftTop
             , const DrawCoord             &rightBottom
             , bool                         drawFrame
             ) override
             { return getActiveDc()->fillRect(leftTop, rightBottom, drawFrame); }

    bool fillGradientRect( const DrawCoord             &leftTop
                         , const DrawCoord             &rightBottom
                         , const ColorRef              &gradientColorBegin
                         , const ColorRef              &gradientColorMid
                         , const ColorRef              &gradientColorEnd
                         , const DrawCoord::value_type &gradientMidPoint
                         , GradientType                gradientType
                         , bool                        excludeFrame
                         ) override
             { return getActiveDc()->fillGradientRect(leftTop, rightBottom, gradientColorBegin, gradientColorMid, gradientColorEnd, gradientMidPoint, gradientType, excludeFrame); }

    bool fillGradientRect( const DrawCoord             &leftTop
                         , const DrawCoord             &rightBottom
                         , const GradientParams        &gradientParams
                         , GradientType                gradientType
                         , bool                        excludeFrame
                         ) override
             { return getActiveDc()->fillGradientRect(leftTop, rightBottom, gradientParams, gradientType, excludeFrame); }

    bool fillGradientRoundRect( DrawCoord::value_type       cornersR
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
                              ) override
             { return getActiveDc()->fillGradientRoundRect(cornersR, leftTop, rightBottom, gradientColorBegin, gradientColorMid, gradientColorEnd, gradientMidPoint, gradientType, excludeFrame, fillBreakPos, fillFlags); }

    bool fillGradientRoundRect( DrawCoord::value_type       cornersR
                              , const DrawCoord             &leftTop
                              , const DrawCoord             &rightBottom
                              , const GradientParams        &gradientParams
                              , GradientType                gradientType
                              , bool                        excludeFrame
                              , DrawCoord::value_type       fillBreakPos
                              , GradientRoundRectFillFlags  fillFlags // = GradientRoundRectFillFlags::roundBoth | GradientRoundRectFillFlags::fillFull
                              ) override
             { return getActiveDc()->fillGradientRoundRect(cornersR, leftTop, rightBottom, gradientParams, gradientType, excludeFrame, fillBreakPos, fillFlags); }

    bool fillGradientCircle( const DrawCoord             &pos
                           , const DrawCoord::value_type &r
                           , const ColorRef              &gradientColorBegin
                           , const ColorRef              &gradientColorMid
                           , const ColorRef              &gradientColorEnd
                           , const DrawCoord::value_type &gradientMidPoint
                           , bool                        excludeFrame
                           ) override
             { return getActiveDc()->fillGradientCircle(pos, r, gradientColorBegin, gradientColorMid, gradientColorEnd, gradientMidPoint, excludeFrame); }

    bool fillGradientCircle( const DrawCoord             &pos
                           , const DrawCoord::value_type &r
                           , const GradientParams        &gradientParams
                           , bool                        excludeFrame
                           ) override
             { return getActiveDc()->fillGradientCircle(pos, r, gradientParams, excludeFrame); }


}; // struct MultiDrawContext





} // namespace marty_draw_context


