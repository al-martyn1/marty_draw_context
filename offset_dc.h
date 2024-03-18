#pragma once

#include "i_draw_context.h"




//----------------------------------------------------------------------------
namespace marty_draw_context {



//----------------------------------------------------------------------------
//! Враппер, форвардит все вызовы в оригинальный DC, добавляя смещение. Используются координаты DrawContext'а.
/*! В базовом IDrawContext также есть смещение, но там оно задаётся в пикселях и без учета масштабирования. 
    Там есть проблема в том, что кроме смещения в базовом IDrawContext есть также и масштабирование, и не очень понятно,
    в каких единицах задавать смещение, учитывать ли при этом масштабирование, и тп. С этим всем как ни сделай, можно запутаться,
    поэтому в базовом DrawContext'е смещение всегда в пикселях относительно низлежащего системного канваса.

    Данный же класс оперирует сугубо координатами низлежащего уже DrawContext'а, и позволяет задавать смещения в координатах уже 
    DrawContext'а. Это удобно при отрисовке каких-либо изображений, состоящих из примитивов - там не надо будет
    вручную вычислять все координаты относительно базовой точки изображения, это будет сделано в данном классе.

    Можно было бы всё же возложить функцию смещения на низлежащий бекэнд, благо, такая возможность есть почти везде на 
    современных канвасах, но тут такой нюанс, 

 */
struct OffsetDc : public IDrawContext
{

    //typedef DrawCoord::value_type  float_t;
    typedef IDrawContext::float_t    float_t;

protected:

    IDrawContext    *m_pdc = 0;
    DrawCoord        m_offset;

    IDrawContext* safedc() const
    {
        if (!m_pdc)
        {
            throw std::runtime_error("OffsetDc: DrawContext not initialized");
        }

        return m_pdc;
    }

    IDrawContext* safedc()
    {
        if (!m_pdc)
        {
            throw std::runtime_error("OffsetDc: DrawContext not initialized");
        }

        return m_pdc;
    }

public:

    OffsetDc() = delete; // default;
    OffsetDc(const OffsetDc &) = default;
    OffsetDc& operator=(const OffsetDc &) = default;
    OffsetDc(OffsetDc &&) = default;
    OffsetDc& operator=(OffsetDc &&) = default;

    OffsetDc(IDrawContext *pdc, const DrawCoord &offs) : m_pdc(pdc), m_offset(offs) {}


    // Utility methods
    virtual std::string getEngineName() override
    {
        return safedc()->getEngineName();
    }

    virtual std::uint8_t* swapByteOrder(std::uint8_t *pData, std::size_t dataSize) const override
    {
        return safedc()->swapByteOrder(pData, dataSize);
    }

    virtual Endianness    getHostEndianness() const override
    {
        return safedc()->getHostEndianness();
    }

    virtual std::uint8_t* convertEndiannessToHost  (std::uint8_t *pData, std::size_t dataSize, Endianness srcEndianness) const override
    {
        return safedc()->convertEndiannessToHost(pData, dataSize, srcEndianness);
    }

    virtual std::uint8_t* convertEndiannessFromHost(std::uint8_t *pData, std::size_t dataSize, Endianness dstEndianness) const override
    {
        return safedc()->convertEndiannessFromHost(pData, dataSize, dstEndianness);
    }


    // char strings encoding
    virtual void setStringEncoding(const std::string &encName) override
    {
        safedc()->setStringEncoding(encName);
    }

    virtual std::string getStringEncoding() override
    {
        return safedc()->getStringEncoding();
    }

    virtual std::wstring decodeString( const std::string &str ) override
    {
        return safedc()->decodeString(str);
    }


    virtual void flushBits() override
    {
        safedc()->flushBits();
    }

    virtual void logFontsInfo() override
    {
        safedc()->logFontsInfo();
    }

    virtual void freeAllocatedRc() override
    {
        safedc()->freeAllocatedRc();
    }

    virtual SmoothingMode setSmoothingMode( SmoothingMode m ) override
    {
        return safedc()->setSmoothingMode(m);
    }

    virtual SmoothingMode getSmoothingMode( ) override
    {
        return safedc()->getSmoothingMode();
    }

    virtual DrawingPrecise setDrawingPrecise(DrawingPrecise p) override
    {
        return safedc()->setDrawingPrecise(p);
    }

    virtual DrawingPrecise getDrawingPrecise() override
    {
        return safedc()->getDrawingPrecise();
    }

    virtual bool setCollectMarkers( bool cmMode ) override
    {
        return safedc()->setCollectMarkers(cmMode);
    }

    virtual bool getCollectMarkers( ) override
    {
        return safedc()->getCollectMarkers();
    }

    virtual bool markerAdd( const DrawCoord &pos, const DrawCoord::value_type sz ) override
    {
        return safedc()->markerAdd(pos+m_offset, sz);
    }

    virtual bool markerAdd( const DrawCoord &pos ) override
    {
        return safedc()->markerAdd(pos+m_offset);
    }

    virtual void markersClear( ) override
    {
        safedc()->markersClear();
    }

    virtual void markersDraw( int penId ) override
    {
        safedc()->markersDraw(penId);
    }

    virtual DrawCoord::value_type markerSetDefSize( const DrawCoord::value_type &sz ) override
    {
        return safedc()->markerSetDefSize(sz);
    }

    virtual DrawCoord::value_type markerGetDefSize( ) override
    {
        return safedc()->markerGetDefSize();
    }

    virtual DcResourcesState getResourcesState() override
    {
        return safedc()->getResourcesState();
    }

    virtual void restoreResourcesState(const DcResourcesState &rcState) override
    {
        safedc()->restoreResourcesState(rcState);
    }

    virtual DrawCoord::value_type distanceBetween( const DrawCoord &pos1, const DrawCoord &pos2 ) const override
    {
        return safedc()->distanceBetween(pos1, pos2); // Тут не нужно прибавлять смещение
    }

    virtual DrawCoord             reflectPoint   ( const DrawCoord &pos , const DrawCoord &relativeTo ) const override
    {
        return safedc()->reflectPoint(pos, relativeTo) + m_offset; // Тут достаточно прибавить смещение к результату
    }

    virtual float_t getFitFontHeight(const DrawSize &boxSize) override
    {
        return safedc()->getFitFontHeight(boxSize);
    }

    virtual float_t getAwgFontWidth(const FontParamsA &fp) override
    {
        return safedc()->getAwgFontWidth(fp);
    }

    virtual float_t getAwgFontWidth(const FontParamsW &fp) override
    {
        return safedc()->getAwgFontWidth(fp);
    }

    virtual float_t getFitMarginWidth(const FontParamsA &fp) override
    {
        return safedc()->getFitMarginWidth(fp);
    }

    virtual float_t getFitMarginWidth(const FontParamsW &fp) override
    {
        return safedc()->getFitMarginWidth(fp);
    }


    virtual DrawSize getDialigBaseUnits() override
    {
        return safedc()->getDialigBaseUnits();
    }

    //! !!! Данный метод не стоит применять в обёртках высших уровней - он в основном предназначен для использования в DC первого уровня для маппинга координат мыши
    virtual DrawCoord mapRawToLogicPos( const DrawCoord &c  ) const override
    {
        return safedc()->mapRawToLogicPos(c+m_offset) - m_offset;
    }

    //! Тут нет проблем с маппингом в обёртках
    virtual DrawCoord mapRawToLogicSize( const DrawCoord &c ) const override
    {
        return safedc()->mapRawToLogicSize(c);
    }

    //! Тут нет проблем с маппингом в обёртках
    virtual DrawCoord::value_type mapRawToLogicSizeX( const DrawCoord::value_type &c ) const override
    {
        return safedc()->mapRawToLogicSizeX(c);
    }

    //! Тут нет проблем с маппингом в обёртках
    virtual DrawCoord::value_type mapRawToLogicSizeY( const DrawCoord::value_type &c ) const override
    {
        return safedc()->mapRawToLogicSizeX(c);
    }

    virtual DrawCoord             getPixelSize()  const override
    {
        return safedc()->getPixelSize();
    }

    virtual DrawCoord::value_type getPixelSizeX() const override
    {
        return safedc()->getPixelSizeX();
    }

    virtual DrawCoord::value_type getPixelSizeY() const override
    {
        return safedc()->getPixelSizeY();
    }

    //! !!! Данный метод не стоит применять в обёртках высших уровней - он в основном предназначен для использования в DC первого уровня для маппинга координат мыши
    virtual DrawCoord getScaledPos( const DrawCoord &c  ) const override
    {
        return safedc()->getScaledPos(c+m_offset) - m_offset;
    }

    virtual DrawCoord getScaledSize( const DrawCoord &c ) const override
    {
        return safedc()->getScaledSize(c);
    }

    virtual DrawCoord::value_type getScaledSizeX( const DrawCoord::value_type &c ) const override
    {
        return safedc()->getScaledSizeX(c);
    }

    virtual DrawCoord::value_type getScaledSizeY( const DrawCoord::value_type &c ) const override
    {
        return safedc()->getScaledSizeY(c);
    }

    virtual DrawCoord setOffset( const DrawCoord &c ) override
    {
        MARTY_ARG_USED(c);
        throw std::runtime_error("OffsetDc::setOffset: forbidden for usage in OffsetDc");
    }

    virtual DrawCoord getOffset( ) override
    {
        //throw std::runtime_error("OffsetDc::getOffset: forbidden for usage in OffsetDc");
        return safedc()->getOffset();
    }

    virtual DrawScale setScale( const DrawScale &scale ) override
    {
        MARTY_ARG_USED(scale);
        throw std::runtime_error("OffsetDc::setScale: forbidden for usage in OffsetDc");
    }

    virtual DrawScale getScale( ) override
    {
        //throw std::runtime_error("OffsetDc::getScale: forbidden for usage in OffsetDc");
        return safedc()->getScale();
    }

    virtual float_t setPenScale( float_t scale ) override
    {
        MARTY_ARG_USED(scale);
        throw std::runtime_error("OffsetDc::setPenScale: forbidden for usage in OffsetDc");
    }

    virtual float_t getPenScale( ) override
    {
        return safedc()->getPenScale();
    }

    virtual DcOffsetScale getOffsetScale() override
    {
        return safedc()->getOffsetScale();
    }

    virtual void restoreOffsetScale(const DcOffsetScale &dcOs) override
    {
        MARTY_ARG_USED(dcOs);
        throw std::runtime_error("OffsetDc::restoreOffsetScale: forbidden for usage in OffsetDc");
    }


    virtual DrawCoord getCurPos( ) override
    {
        // Тут плюс или минус?
        // offset у нас смещает обычно начало вправо-вниз
        // мы должны выдать координату относительно ориджина данного DC
        // Надо отнимать
        return safedc()->getCurPos() - m_offset;
    }

    virtual int createSolidBrush( const ColorRef &rgb ) override
    {
        return safedc()->createSolidBrush(rgb);
    }

    virtual int createSolidBrush( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override
    {
        return safedc()->createSolidBrush(r, g, b);
    }

    virtual int selectBrush( int brushId ) override
    {
        return safedc()->selectBrush(brushId);
    }

    // returns new brushId, not prev
    virtual int selectNewSolidBrush( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override
    {
        return safedc()->selectNewSolidBrush(r, g, b);
    }

    virtual int selectNewSolidBrush( const ColorRef &rgb ) override
    {
        return safedc()->selectNewSolidBrush(rgb);
    }

    virtual int getCurBrush() override
    {
        return safedc()->getCurBrush();
    }

    virtual std::size_t getCharLen     (const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override //!< Длина символа в wchar_t'ах - поддержка сурогатных пар, возвращает 0/1/2, 0 - достигли конца строки
    {
        return safedc()->getCharLen(text, textSize);
    }

    virtual std::size_t getTextCharsLen(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override //!< Длина текста в символах с учетом суррогатных пар
    {
        return safedc()->getTextCharsLen(text, textSize);
    }

    virtual std::size_t getTextCharsLenEx(DrawTextFlags flags, const wchar_t *text, std::size_t textSize=(std::size_t)-1, const wchar_t *skipChars=0) const override //!< Длина текста в символах с учетом суррогатных пар и с учетом (или нет) комбайнинг символов
    {
        return safedc()->getTextCharsLenEx(flags, text, textSize, skipChars);
    }

    virtual std::uint32_t getChar32(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override //!< Возвращает Unicode символ, формируя его (возможно) из суррогатной пары
    {
        return safedc()->getChar32(text, textSize);
    }

    virtual bool getCharWidth (std::uint32_t charCode, float_t &w) const override
    {
        return safedc()->getCharWidth(charCode, w);
    }

    virtual bool getCharWidth (std::uint32_t charCode, float_t &w, int fontId /* =-1 */ ) const override
    {
        return safedc()->getCharWidth(charCode, w, fontId);
    }

    virtual bool getCharWidths(std::vector<float_t> &widths, const wchar_t *text, std::size_t textSize=(std::size_t)-1, int fontId=-1 /* use current font */ ) const override
    {
        return safedc()->getCharWidths(widths, text, textSize, fontId);
    }

    //virtual bool getCharWidths(std::vector<float_t> &widths, const std::wstring &text, int fontId=-1 /* use current font */ ) override

    // Нужны ли нам тут в публичном интерфейсе версии с char/std::string?
    //virtual bool getCharWidths(const char         *text, std::vector<float_t> &widths, int fontId=-1 /* use current font */ ) override
    //virtual bool getCharWidths(const std::string  &text, std::vector<float_t> &widths, int fontId=-1 /* use current font */ ) override

    virtual bool getSimpleFontMetrics(SimpleFontMetrics &m, int fontId=-1) const override
    {
        return safedc()->getSimpleFontMetrics(m, fontId);
    }

    virtual bool getKerningPairs(std::vector<KerningPair> &pairs, int fontId=-1) const override
    {
        return safedc()->getKerningPairs(pairs, fontId);
    }

    virtual float_t getKerningValue( const std::unordered_set<KerningPair> &pairs, std::uint32_t chFirst, std::uint32_t chSecond) const override
    {
        return safedc()->getKerningValue(pairs, chFirst, chSecond);
    }

    // Про категории символов юникода - https://learn.microsoft.com/ru-ru/dotnet/api/system.globalization.unicodecategory?view=net-7.0
    virtual bool isArabicDigitChar(std::uint32_t ch) const override
    {
        return safedc()->isArabicDigitChar(ch);
    }

    virtual bool isLatinLetterChar(std::uint32_t ch) const override
    {
        return safedc()->isLatinLetterChar(ch);
    }

    virtual bool isAnySpaceChar(std::uint32_t ch) const override
    {
        return safedc()->isAnySpaceChar(ch);
    }

    virtual bool isAnyNonBreakingSpaceChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyNonBreakingSpaceChar(ch);
    }

    virtual bool isAnyBreakingSpaceChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyBreakingSpaceChar(ch);
    }

    virtual bool isAnyNonBreakingDashChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyNonBreakingDashChar(ch);
    }

    virtual bool isAnyBreakingDashChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyBreakingDashChar(ch);
    }

    virtual bool isAnyDashChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyDashChar(ch);
    }

    virtual bool isAnyTabChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyTabChar(ch);
    }

    virtual bool isAnyLineBreakChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyLineBreakChar(ch);
    }

    virtual bool isAnyWhiteSpaceChar(std::uint32_t ch) const override
    {
        return safedc()->isAnyWhiteSpaceChar(ch);
    }

    virtual bool isLineBreak(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override
    {
        return safedc()->isLineBreak(text, textSize);
    }

    virtual std::size_t getLineBreakLen(const wchar_t *text, std::size_t textSize=(std::size_t)-1) const override //!< Длина символа LineBreak в wchar_t'ах, 0 - достигли конца строки или символ не LineBreak
    {
        return safedc()->getLineBreakLen(text, textSize);
    }


    virtual bool drawTextColored( const DrawCoord                  &startPos
                                , const DrawCoord::value_type      &widthLim
                                , DrawTextFlags                    flags
                                , const wchar_t                    *text
                                , std::size_t                      textSize=(std::size_t)-1
                                , const wchar_t                    *stopChars=0
                                , const std::uint32_t              *pColors=0
                                , std::size_t                      nColors=0
                                , const std::uint32_t              *pBackColors=0
                                , std::size_t                      nBackColors=0
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosX=0          //!< OUT, Положение вывода для символа, следующего за последним выведенным
                                , DrawCoord::value_type            *pOverhang=0          //!< OUT, Вынос элементов символа за пределы NextPosX - актуально, как минимум, для iatalic стиля шрифта
                                , std::uint32_t                    *pLastCharProcessed=0 //!< IN/OUT last drawn char, for kerning calculation
                                , std::size_t                      *pCharsProcessed=0    //!< OUT Num chars, not symbols/glyphs
                                , std::size_t                      *pSymbolsDrawn=0
                                ) override
    {
        DrawCoord::value_type  NextPosX;
        DrawCoord::value_type  Overhang;
        std::uint32_t          LastCharProcessed;
        std::size_t            CharsProcessed;
        std::size_t            SymbolsDrawn;

        bool res = safedc()->drawTextColored( startPos + m_offset
                                            , widthLim
                                            , flags               
                                            , text               
                                            , textSize
                                            , stopChars
                                            , pColors
                                            , nColors
                                            , pBackColors
                                            , nBackColors
                                            , fontId
                                            , &NextPosX
                                            , &Overhang
                                            , &LastCharProcessed
                                            , &CharsProcessed
                                            , &SymbolsDrawn
                                            );
        if (res)
        {
            if (pNextPosX)
                *pNextPosX = NextPosX - m_offset.x;
    
            if (pOverhang)
                *pOverhang = Overhang - m_offset.x;
    
            if (pLastCharProcessed)
                *pLastCharProcessed = LastCharProcessed;
    
            if (pCharsProcessed)
                *pCharsProcessed = CharsProcessed;
    
            if (pSymbolsDrawn)
                *pSymbolsDrawn = SymbolsDrawn;
        }

        return res;
    }


    virtual bool drawTextColored( const DrawCoord                  &startPos
                                , const DrawCoord::value_type      &widthLim
                                , DrawTextFlags                    flags
                                , const std::wstring               &text
                                , const std::wstring               &stopChars
                                , const std::vector<std::uint32_t> &colors
                                , const std::vector<std::uint32_t> &bkColors
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosX=0          //!< OUT, Положение вывода для символа, следующего за последним выведенным
                                , DrawCoord::value_type            *pOverhang=0          //!< OUT, Вынос элементов символа за пределы NextPosX - актуально, как минимум, для iatalic стиля шрифта
                                , std::uint32_t                    *pLastCharProcessed=0 //!< IN/OUT last drawn char, for kerning calculation
                                , std::size_t                      *pCharsProcessed=0    //!< OUT Num chars, not symbols/glyphs
                                , std::size_t                      *pSymbolsDrawn=0
                                ) override
    {
        DrawCoord::value_type  NextPosX;
        DrawCoord::value_type  Overhang;
        std::uint32_t          LastCharProcessed;
        std::size_t            CharsProcessed;
        std::size_t            SymbolsDrawn;

        bool res = safedc()->drawTextColored( startPos + m_offset
                                            , widthLim
                                            , flags               
                                            , text               
                                            , stopChars
                                            , colors
                                            , bkColors
                                            , fontId
                                            , &NextPosX
                                            , &Overhang
                                            , &LastCharProcessed
                                            , &CharsProcessed
                                            , &SymbolsDrawn
                                            );
        if (res)
        {
            if (pNextPosX)
                *pNextPosX = NextPosX - m_offset.x;
    
            if (pOverhang)
                *pOverhang = Overhang - m_offset.x;
    
            if (pLastCharProcessed)
                *pLastCharProcessed = LastCharProcessed;
    
            if (pCharsProcessed)
                *pCharsProcessed = CharsProcessed;
    
            if (pSymbolsDrawn)
                *pSymbolsDrawn = SymbolsDrawn;
        }

        return res;
    }

    virtual bool drawParaColored( const DrawCoord                  &startPos
                                , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                , DrawTextFlags                    flags
                                , HorAlign                         horAlign
                                , VertAlign                        vertAlign
                                , const wchar_t                    *text
                                , std::size_t                      textSize=(std::size_t)-1
                                , const std::uint32_t              *pColors=0
                                , std::size_t                      nColors=0
                                , const std::uint32_t              *pBackColors=0
                                , std::size_t                      nBackColors=0
                                , const DrawCoord::value_type      *pTabStopPositions=0        //!< Relative to start pos X coord
                                , std::size_t                      nTabStopPositions=0
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosY=0         //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                , bool                             *pVerticalDone=0     //!< OUT All/not all lines drawn, 
                                , std::size_t                      *pSymbolsDrawn=0     //!< OUT For Next para Y start calculation
                                ) override
    {
        DrawCoord::value_type  NextPosY;
        bool                   VerticalDone;
        std::size_t            SymbolsDrawn;

        bool res = safedc()->drawParaColored( startPos + m_offset
                                            , limits
                                            , lineSpacing
                                            , paraIndent
                                            , tabSize
                                            , flags
                                            , horAlign
                                            , vertAlign
                                            , text
                                            , textSize
                                            , pColors
                                            , nColors
                                            , pBackColors
                                            , nBackColors
                                            , pTabStopPositions
                                            , nTabStopPositions
                                            , fontId
                                            , &NextPosY
                                            , &VerticalDone
                                            , &SymbolsDrawn
                                            );
        if (res)
        {
            if (pNextPosY)
                *pNextPosY = NextPosY - m_offset.y;

            if (pVerticalDone)
                *pVerticalDone = VerticalDone;

            if (pSymbolsDrawn)
                *pSymbolsDrawn = SymbolsDrawn;
        }

        return res;
    }

    virtual bool drawParaColored( const DrawCoord                  &startPos
                                , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                , DrawTextFlags                    flags
                                , HorAlign                         horAlign
                                , VertAlign                        vertAlign
                                , const std::wstring               &text
                                , const std::vector<std::uint32_t> &colors
                                , const std::vector<std::uint32_t> &bkColors
                                , const std::vector<DrawCoord::value_type> &tabStopPositions
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosY=0         //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                , bool                             *pVerticalDone=0     //!< OUT All/not all lines drawn, 
                                , std::size_t                      *pSymbolsDrawn=0     //!< OUT For Next para Y start calculation
                                ) override
    {
        DrawCoord::value_type  NextPosY;
        bool                   VerticalDone;
        std::size_t            SymbolsDrawn;

        bool res = safedc()->drawParaColored( startPos + m_offset
                                            , limits
                                            , lineSpacing
                                            , paraIndent
                                            , tabSize
                                            , flags
                                            , horAlign
                                            , vertAlign
                                            , text
                                            , colors
                                            , bkColors
                                            , tabStopPositions
                                            , fontId
                                            , &NextPosY
                                            , &VerticalDone
                                            , &SymbolsDrawn
                                            );
        if (res)
        {
            if (pNextPosY)
                *pNextPosY = NextPosY - m_offset.y;

            if (pVerticalDone)
                *pVerticalDone = VerticalDone;

            if (pSymbolsDrawn)
                *pSymbolsDrawn = SymbolsDrawn;
        }

        return res;
    }

    virtual bool drawMultiParasColored( const DrawCoord            &startPos
                                , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                , const DrawCoord::value_type      &paraSpacing  //!< Extra space between paras
                                , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                , DrawTextFlags                    flags
                                , HorAlign                         horAlign
                                , VertAlign                        vertAlign
                                , const wchar_t                    *text
                                , std::size_t                      textSize=(std::size_t)-1
                                , const std::uint32_t              *pColors=0
                                , std::size_t                      nColors=0
                                , const std::uint32_t              *pBackColors=0
                                , std::size_t                      nBackColors=0
                                , const DrawCoord::value_type      *pTabStopPositions=0        //!< Relative to start pos X coord
                                , std::size_t                      nTabStopPositions=0
                                , const std::uint32_t              *pParaColors=0
                                , std::size_t                      nParaColors=0
                                , const std::uint32_t              *pParaBackColors=0
                                , std::size_t                      nParaBackColors=0
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosY=0         //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                , bool                             *pVerticalDone=0     //!< OUT All/not all lines drawn, 
                                ) override
    {
        DrawCoord::value_type NextPosY;
        bool                  VerticalDone;

        bool res = safedc()->drawMultiParasColored( startPos + m_offset
                                                  , limits
                                                  , lineSpacing
                                                  , paraSpacing
                                                  , paraIndent
                                                  , tabSize
                                                  , flags
                                                  , horAlign
                                                  , vertAlign
                                                  , text
                                                  , textSize
                                                  , pColors
                                                  , nColors
                                                  , pBackColors
                                                  , nBackColors
                                                  , pTabStopPositions
                                                  , nTabStopPositions
                                                  , pParaColors
                                                  , nParaColors
                                                  , pParaBackColors
                                                  , nParaBackColors
                                                  , fontId
                                                  , &NextPosY
                                                  , &VerticalDone
                                                  );
        if (res)
        {
            if (pNextPosY)
                *pNextPosY = NextPosY - m_offset.y;

            if (pVerticalDone)
                *pVerticalDone = VerticalDone;
        }

        return res;
    }

    virtual bool drawMultiParasColored( const DrawCoord            &startPos
                                , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                , const DrawCoord::value_type      &paraSpacing  //!< Extra space between paras
                                , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                , DrawTextFlags                    flags
                                , HorAlign                         horAlign
                                , VertAlign                        vertAlign
                                , const std::wstring               &text
                                , const std::vector<std::uint32_t> &colors
                                , const std::vector<std::uint32_t> &bkColors
                                , const std::vector<DrawCoord::value_type> &tabStopPositions
                                , const std::vector<std::uint32_t> &paraColors
                                , const std::vector<std::uint32_t> &paraBkColors
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosY=0         //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                , bool                             *pVerticalDone=0     //!< OUT All/not all lines drawn, 
                                ) override
    {
        DrawCoord::value_type NextPosY;
        bool                  VerticalDone;

        bool res = safedc()->drawMultiParasColored( startPos + m_offset
                                                  , limits
                                                  , lineSpacing
                                                  , paraSpacing
                                                  , paraIndent
                                                  , tabSize
                                                  , flags
                                                  , horAlign
                                                  , vertAlign
                                                  , text
                                                  , colors
                                                  , bkColors
                                                  , tabStopPositions
                                                  , paraColors
                                                  , paraBkColors
                                                  , fontId
                                                  , &NextPosY
                                                  , &VerticalDone
                                                  );
        if (res)
        {
            if (pNextPosY)
                *pNextPosY = NextPosY - m_offset.y;

            if (pVerticalDone)
                *pVerticalDone = VerticalDone;
        }

        return res;
    }

    // Версии с std::string вместо std::wstring. Требуются прежде всего для биндингов. Версии с const wchar_t* не нужны
    virtual bool drawTextColored( const DrawCoord                  &startPos
                                , const DrawCoord::value_type      &widthLim
                                , DrawTextFlags                    flags
                                , const std::string                &text
                                , const std::string                &stopChars
                                , const std::vector<std::uint32_t> &colors
                                , const std::vector<std::uint32_t> &bkColors
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosX=0          //!< OUT, Положение вывода для символа, следующего за последним выведенным
                                , DrawCoord::value_type            *pOverhang=0          //!< OUT, Вынос элементов символа за пределы NextPosX - актуально, как минимум, для iatalic стиля шрифта
                                , std::uint32_t                    *pLastCharProcessed=0 //!< IN/OUT last drawn char, for kerning calculation
                                , std::size_t                      *pCharsProcessed=0    //!< OUT Num chars, not symbols/glyphs
                                , std::size_t                      *pSymbolsDrawn=0
                                ) override
    {
        DrawCoord::value_type  NextPosX;
        DrawCoord::value_type  Overhang;
        std::uint32_t          LastCharProcessed;
        std::size_t            CharsProcessed;
        std::size_t            SymbolsDrawn;

        bool res = safedc()->drawTextColored( startPos + m_offset
                                            , widthLim
                                            , flags               
                                            , text               
                                            , stopChars
                                            , colors
                                            , bkColors
                                            , fontId
                                            , &NextPosX
                                            , &Overhang
                                            , &LastCharProcessed
                                            , &CharsProcessed
                                            , &SymbolsDrawn
                                            );
        if (res)
        {
            if (pNextPosX)
                *pNextPosX = NextPosX - m_offset.x;
    
            if (pOverhang)
                *pOverhang = Overhang - m_offset.x;
    
            if (pLastCharProcessed)
                *pLastCharProcessed = LastCharProcessed;
    
            if (pCharsProcessed)
                *pCharsProcessed = CharsProcessed;
    
            if (pSymbolsDrawn)
                *pSymbolsDrawn = SymbolsDrawn;
        }

        return res;
    }

    virtual bool drawParaColored( const DrawCoord                  &startPos
                                , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                , DrawTextFlags                    flags
                                , HorAlign                         horAlign
                                , VertAlign                        vertAlign
                                , const std::string                &text
                                , const std::vector<std::uint32_t> &colors
                                , const std::vector<std::uint32_t> &bkColors
                                , const std::vector<DrawCoord::value_type> &tabStopPositions
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosY=0         //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                , bool                             *pVerticalDone=0     //!< OUT All/not all lines drawn, 
                                , std::size_t                      *pSymbolsDrawn=0     //!< OUT For Next para Y start calculation
                                ) override
    {
        DrawCoord::value_type  NextPosY;
        bool                   VerticalDone;
        std::size_t            SymbolsDrawn;

        bool res = safedc()->drawParaColored( startPos + m_offset
                                            , limits
                                            , lineSpacing
                                            , paraIndent
                                            , tabSize
                                            , flags
                                            , horAlign
                                            , vertAlign
                                            , text
                                            , colors
                                            , bkColors
                                            , tabStopPositions
                                            , fontId
                                            , &NextPosY
                                            , &VerticalDone
                                            , &SymbolsDrawn
                                            );
        if (res)
        {
            if (pNextPosY)
                *pNextPosY = NextPosY - m_offset.y;

            if (pVerticalDone)
                *pVerticalDone = VerticalDone;

            if (pSymbolsDrawn)
                *pSymbolsDrawn = SymbolsDrawn;
        }

        return res;
    }

    virtual bool drawMultiParasColored( const DrawCoord            &startPos
                                , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                , const DrawCoord::value_type      &paraSpacing  //!< Extra space between paras
                                , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                , DrawTextFlags                    flags
                                , HorAlign                         horAlign
                                , VertAlign                        vertAlign
                                , const std::string                &text
                                , const std::vector<std::uint32_t> &colors
                                , const std::vector<std::uint32_t> &bkColors
                                , const std::vector<DrawCoord::value_type> &tabStopPositions
                                , const std::vector<std::uint32_t> &paraColors
                                , const std::vector<std::uint32_t> &paraBkColors
                                , int                              fontId=-1
                                , DrawCoord::value_type            *pNextPosY=0         //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                , bool                             *pVerticalDone=0     //!< OUT All/not all lines drawn, 
                                ) override
    {
        DrawCoord::value_type NextPosY;
        bool                  VerticalDone;

        bool res = safedc()->drawMultiParasColored( startPos + m_offset
                                                  , limits
                                                  , lineSpacing
                                                  , paraSpacing
                                                  , paraIndent
                                                  , tabSize
                                                  , flags
                                                  , horAlign
                                                  , vertAlign
                                                  , text
                                                  , colors
                                                  , bkColors
                                                  , tabStopPositions
                                                  , paraColors
                                                  , paraBkColors
                                                  , fontId
                                                  , &NextPosY
                                                  , &VerticalDone
                                                  );
        if (res)
        {
            if (pNextPosY)
                *pNextPosY = NextPosY - m_offset.y;

            if (pVerticalDone)
                *pVerticalDone = VerticalDone;
        }

        return res;
    }



    #if 0
    virtual bool drawParaColoredEx( const DrawCoord                  &startPos
                                  , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                  , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                  , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                  , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                  , DrawTextFlags                    flags
                                  , HorAlign                         horAlign
                                  , VertAlign                        vertAlign
                                  , const wchar_t                    *text
                                  , std::size_t                      textSize=(std::size_t)-1
                                  , const std::vector<std::uint32_t> &colors
                                  , const std::vector<std::uint32_t> &bkColors
                                  , const std::vector<DrawCoord::value_type> &tabStopPositions  //!< Relative to start pos X coord
                                  , DrawCoord::value_type            *pNextPosY=0       //!< OUT No line spacing added cause spacing between paras can be other then lineSpacing value
                                  , bool                             *pVerticalDone=0   //!< OUT All/not all lines drawn, 
                                  , std::size_t                      *pCharsProcessed=0 //!< OUT Num chars, not symbols/glyphs
                                  , int                              fontId=-1
                                  ) override

    virtual bool drawParaColored  ( const DrawCoord                  &startPos
                                  , const DrawCoord                  &limits       //!< Limits, vertical and horizontal, relative to start pos
                                  , const DrawCoord::value_type      &lineSpacing  //!< Extra space between lines of text
                                  , const DrawCoord::value_type      &paraIndent   //!< Indent on the first line
                                  , const DrawCoord::value_type      &tabSize      //!< Size used for tabs if tabStops are over
                                  , DrawTextFlags                    flags
                                  , HorAlign                         horAlign
                                  , VertAlign                        vertAlign
                                  , const wchar_t                    *text
                                  , std::size_t                      textSize=(std::size_t)-1
                                  , const std::uint32_t              *pColors=0
                                  , std::size_t                      nColors=0
                                  , const std::uint32_t              *pBackColors=0
                                  , std::size_t                      nBackColors=0
                                  , const DrawCoord::value_type      *pTabStopPositions=0        //!< Relative to start pos X coord
                                  , std::size_t                      nTabStopPositions=0
                                  , int                              fontId=-1
                                  ) override
    #endif



    virtual int  createFont( float_t height, int escapement, int orientation, FontWeight weight, FontStyleFlags fontStyleFlags, const char    *fontFace ) override
    {
        return safedc()->createFont(height, escapement, orientation, weight, fontStyleFlags, fontFace);
    }

    virtual int  createFont( float_t height, int escapement, int orientation, FontWeight weight, FontStyleFlags fontStyleFlags, const wchar_t *fontFace ) override
    {
        return safedc()->createFont(height, escapement, orientation, weight, fontStyleFlags, fontFace);
    }

    virtual int  createFont( const FontParamsA &fp ) override
    {
        return safedc()->createFont(fp);
    }

    virtual int  createFont( const FontParamsW &fp ) override
    {
        return safedc()->createFont(fp);
    }

    virtual int  createFont( FontParamsA fp, const FontParamsA::string_type &fontFace ) override
    {
        return safedc()->createFont(fp, fontFace);
    }

    virtual int  createFont( FontParamsW fp, const FontParamsW::string_type &fontFace ) override
    {
        return safedc()->createFont(fp, fontFace);
    }

    virtual int  makeFontByParams( const FontParamsA &fp ) override
    {
        return safedc()->makeFontByParams(fp);
    }

    virtual int  makeFontByParams( const FontParamsW &fp ) override
    {
        return safedc()->makeFontByParams(fp);
    }

    virtual int  makeFontByParams( FontParamsA fp, float_t height ) override
    {
        return safedc()->makeFontByParams(fp, height);
    }

    virtual int  makeFontByParams( FontParamsW fp, float_t height ) override
    {
        return safedc()->makeFontByParams(fp, height);
    }

    virtual int  selectFont( int fontId ) override
    {
        return safedc()->selectFont(fontId);
    }

    // returns new fontId, not prev
    virtual int  selectNewFont( const FontParamsA &fp ) override
    {
        return safedc()->selectNewFont(fp);
    }

    virtual int  selectNewFont( const FontParamsW &fp ) override
    {
        return safedc()->selectNewFont(fp);
    }

    virtual int  getCurFont() override
    {
        return safedc()->getCurFont();
    }

    virtual bool textOut( const DrawCoord &pos, const char    *text, std::size_t textSize=(std::size_t)-1 ) override
    {
        return safedc()->textOut(pos+m_offset, text, textSize);
    }

    virtual bool textOut( const DrawCoord &pos, const wchar_t *text, std::size_t textSize=(std::size_t)-1 ) override
    {
        return safedc()->textOut(pos+m_offset, text, textSize);
    }

    virtual bool textOut( const DrawCoord &pos, const std::string  &text ) override
    {
        return safedc()->textOut(pos+m_offset, text);
    }

    virtual bool textOut( const DrawCoord &pos, const std::wstring &text ) override
    {
        return safedc()->textOut(pos+m_offset, text);
    }

    virtual bool textOut( const DrawCoord &pos, int fontId, const ColorRef &rgb, const std::string  &text ) override
    {
        return safedc()->textOut(pos+m_offset, fontId, rgb, text);
    }

    virtual bool textOut( const DrawCoord &pos, int fontId, const ColorRef &rgb, const std::wstring &text ) override
    {
        return safedc()->textOut(pos+m_offset, fontId, rgb, text);
    }

    virtual bool getFontParamsById( int id, FontParamsA &fp ) override
    {
        return safedc()->getFontParamsById(id, fp);
    }

    virtual bool getFontParamsById( int id, FontParamsW &fp ) override
    {
        return safedc()->getFontParamsById(id, fp);
    }

    virtual int getMonospacedFontCharWidthApprox(const FontParamsA &fp) override
    {
        return safedc()->getMonospacedFontCharWidthApprox(fp);
    }

    virtual int getMonospacedFontCharWidthApprox(const FontParamsW &fp) override
    {
        return safedc()->getMonospacedFontCharWidthApprox(fp);
    }

    virtual int getMonospacedFontCharWidthApprox(int id) override
    {
        return safedc()->getMonospacedFontCharWidthApprox(id);
    }

    virtual int getProportionalFontCharWidthScaleApprox(const FontParamsA &fp) override
    {
        return safedc()->getProportionalFontCharWidthScaleApprox(fp);
    }

    virtual int getProportionalFontCharWidthScaleApprox(const FontParamsW &fp) override
    {
        return safedc()->getProportionalFontCharWidthScaleApprox(fp);
    }

    virtual bool drawTextFitHeigh( const FontParamsA &fp, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override
    {
        DrawCoord TextPos;
        DrawCoord TextSize;
        bool res = safedc()->drawTextFitHeigh(fp, rectPos+m_offset, rectSize, text, a, xMarginScale, &TextPos, &TextSize);
        if (res)
        {
            if (pTextPos)
               *pTextPos = TextPos - m_offset;
            if (pTextSize)
               *pTextSize = TextSize;
        }
        return res;
    }

    virtual bool drawTextFitHeigh( const FontParamsW &fp, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::wstring &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override
    {
        DrawCoord TextPos;
        DrawCoord TextSize;
        bool res = safedc()->drawTextFitHeigh(fp, rectPos+m_offset, rectSize, text, a, xMarginScale, &TextPos, &TextSize);
        if (res)
        {
            if (pTextPos)
               *pTextPos = TextPos - m_offset;
            if (pTextSize)
               *pTextSize = TextSize;
        }
        return res;
    }

    virtual bool drawTextFitHeighEx( const FontParamsA &fp, DrawCoord::value_type fontHeightScale, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::string  &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override
    {
        DrawCoord TextPos;
        DrawCoord TextSize;
        bool res = safedc()->drawTextFitHeighEx(fp, fontHeightScale, rectPos+m_offset, rectSize, text, a, xMarginScale, &TextPos, &TextSize);
        if (res)
        {
            if (pTextPos)
               *pTextPos = TextPos - m_offset;
            if (pTextSize)
               *pTextSize = TextSize;
        }
        return res;
    }

    virtual bool drawTextFitHeighEx( const FontParamsW &fp, DrawCoord::value_type fontHeightScale, const DrawCoord &rectPos, const DrawCoord &rectSize, const std::wstring &text, HorAlign a = HorAlign::left, float_t xMarginScale = 0, DrawCoord *pTextPos = 0, DrawCoord *pTextSize = 0 ) override
    {
        DrawCoord TextPos;
        DrawCoord TextSize;
        bool res = safedc()->drawTextFitHeighEx(fp, fontHeightScale, rectPos+m_offset, rectSize, text, a,xMarginScale, &TextPos, &TextSize );
        if (res)
        {
            if (pTextPos)
               *pTextPos = TextPos - m_offset;
            if (pTextSize)
               *pTextSize = TextSize;
        }
        return res;
    }

    // !!! TODO нужно сделать версии получения ширины символа для FontParamsA/W/id и для char/wchar_t - всего 6 штук
    // Только латинские символы (потом, может, добавлю национальные)
    // Фонт не принципиален
    // Нужно для реализации calcDrawnTextWidthApprox
    virtual int getProportionalFontCharWidthApprox(const FontParamsA &fp, char    ch) override
    {
        return safedc()->getProportionalFontCharWidthApprox(fp, ch);
    }

    virtual int getProportionalFontCharWidthApprox(const FontParamsA &fp, wchar_t ch) override
    {
        return safedc()->getProportionalFontCharWidthApprox(fp, ch);
    }

    virtual int getProportionalFontCharWidthApprox(const FontParamsW &fp, char    ch) override
    {
        return safedc()->getProportionalFontCharWidthApprox(fp, ch);
    }

    virtual int getProportionalFontCharWidthApprox(const FontParamsW &fp, wchar_t ch) override
    {
        return safedc()->getProportionalFontCharWidthApprox(fp, ch);
    }

    virtual int getFontCharWidthApprox(int fontId, char    ch, int scale = 100) override
    {
        return safedc()->getFontCharWidthApprox(fontId, ch, scale);
    }

    virtual int getFontCharWidthApprox(int fontId, wchar_t ch, int scale = 100) override
    {
        return safedc()->getFontCharWidthApprox(fontId, ch, scale);
    }

    virtual int getFontCharWidthApprox(const FontParamsA &fp, char    ch, int scale = 100) override
    {
        return safedc()->getFontCharWidthApprox(fp, ch, scale);
    }

    virtual int getFontCharWidthApprox(const FontParamsA &fp, wchar_t ch, int scale = 100) override
    {
        return safedc()->getFontCharWidthApprox(fp, ch, scale);
    }

    virtual int getFontCharWidthApprox(const FontParamsW &fp, char    ch, int scale = 100) override
    {
        return safedc()->getFontCharWidthApprox(fp, ch, scale);
    }

    virtual int getFontCharWidthApprox(const FontParamsW &fp, wchar_t ch, int scale = 100) override
    {
        return safedc()->getFontCharWidthApprox(fp, ch, scale);
    }

    virtual float_t calcDrawnTextWidthApprox(const FontParamsA &fp, const char*    text, std::size_t nChars, int widthScale = 100) override
    {
        return safedc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale);
    }

    virtual float_t calcDrawnTextWidthApprox(const FontParamsW &fp, const char*    text, std::size_t nChars, int widthScale = 100) override
    {
        return safedc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale);
    }

    virtual float_t calcDrawnTextWidthApprox(const FontParamsA &fp, const wchar_t* text, std::size_t nChars, int widthScale = 100) override
    {
        return safedc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale);
    }

    virtual float_t calcDrawnTextWidthApprox(const FontParamsW &fp, const wchar_t* text, std::size_t nChars, int widthScale = 100) override
    {
        return safedc()->calcDrawnTextWidthApprox(fp, text, nChars, widthScale);
    }

    virtual float_t calcDrawnTextWidthApprox(int   fontId         , const char*    text, std::size_t nChars, int widthScale = 100) override
    {
        return safedc()->calcDrawnTextWidthApprox(fontId, text, nChars, widthScale);
    }

    virtual float_t calcDrawnTextWidthApprox(int   fontId         , const wchar_t* text, std::size_t nChars, int widthScale = 100) override
    {
        return safedc()->calcDrawnTextWidthApprox(fontId, text, nChars, widthScale);
    }

    virtual DrawSize calcDrawnTextSizeExact (int   fontId         , const char*    text, std::size_t nChars) override
    {
        return safedc()->calcDrawnTextSizeExact (fontId, text, nChars);
    }

    virtual DrawSize calcDrawnTextSizeExact (int   fontId         , const wchar_t* text, std::size_t nChars) override
    {
        return safedc()->calcDrawnTextSizeExact (fontId, text, nChars);
    }

    virtual ColorRef setTextColor( const ColorRef &rgb ) override
    {
        return safedc()->setTextColor(rgb);
    }

    virtual ColorRef getTextColor( ) override
    {
        return safedc()->getTextColor( );
    }

    virtual ColorRef setTextColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override
    {
        return safedc()->setTextColor(r, g, b);
    }

    virtual ColorRef setBkColor( const ColorRef &rgb ) override
    {
        return safedc()->setTextColor(rgb);
    }

    virtual ColorRef setBkColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override
    {
        return safedc()->setBkColor(r, g, b);
    }

    virtual ColorRef getBkColor() override
    {
        return safedc()->getBkColor();
    }

    virtual BkMode setBkMode( BkMode mode ) override
    {
        return safedc()->setBkMode(mode);
    }

    virtual BkMode getBkMode() override
    {
        return safedc()->getBkMode();
    }

    virtual int setDefaultCosmeticPen( int penId ) override
    {
        return safedc()->setDefaultCosmeticPen(penId);
    }

    virtual int getDefaultCosmeticPen( ) override
    {
        return safedc()->getDefaultCosmeticPen();
    }

    virtual int createSolidPen( float_t width, LineEndcapStyle endcaps, LineJoinStyle join
                              , std::uint8_t r, std::uint8_t g, std::uint8_t b
                              ) override
    {
        return safedc()->createSolidPen(width, endcaps, join, r, g, b);
    }

    virtual int createSolidPen( float_t width, LineEndcapStyle endcaps, LineJoinStyle join
                              , const ColorRef &rgb
                              ) override
    {
        return safedc()->createSolidPen(width, endcaps, join, rgb);
    }

    virtual int createSolidPen( const PenParams &penParams, const ColorRef &colorRef ) override
    {
        return safedc()->createSolidPen(penParams, colorRef);
    }

    virtual int createSolidPen( const PenParamsWithColor &penParams ) override
    {
        return safedc()->createSolidPen(penParams);
    }

    virtual int selectPen( int penId ) override
    {
        return safedc()->selectPen(penId);
    }

    // returns newly created penId, not previously selected penId
    virtual int selectNewSolidPen( const PenParams &penParams, const ColorRef &colorRef ) override
    {
        return safedc()->selectNewSolidPen(penParams, colorRef);
    }

    virtual int selectNewSolidPen( const PenParamsWithColor &penParams ) override
    {
        return safedc()->selectNewSolidPen(penParams);
    }
    //virtual void setPenColor( std::uint8_t r, std::uint8_t g, std::uint8_t b ) override

    virtual int getCurPen() override
    {
        return safedc()->getCurPen();
    }

    virtual ColorRef  getPenColor (int penId) override
    {
        return safedc()->getPenColor(penId);
    }

    virtual PenParams getPenParams(int penId) override
    {
        return safedc()->getPenParams(penId);
    }

    virtual bool beginPath()                                override
    {
        return safedc()->beginPath();
    }

    virtual bool beginPath( const DrawCoord &to )           override
    {
        return safedc()->beginPath(to+m_offset);
    }

    virtual bool endPath( bool bStroke = true, bool bFill = false ) override
    {
        return safedc()->endPath(bStroke, bFill);
    }

    virtual bool closeFigure()                              override
    {
        return safedc()->closeFigure();
    }

    virtual bool isPathStarted() override
    {
        return safedc()->isPathStarted();
    }

    virtual bool moveTo( const DrawCoord &to ) override
    {
        return safedc()->moveTo(to+m_offset);
    }

    virtual bool lineTo( const DrawCoord &to ) override
    {
        return safedc()->lineTo(to+m_offset);
    }

    virtual bool ellipticArcTo( const DrawCoord &leftTop
                              , const DrawCoord &rightBottom
                              , const DrawCoord &arcStartRefPoint
                              , const DrawCoord &arcEndRefPoint
                              , bool             directionCounterclockwise
                              ) override
    {
        return safedc()->ellipticArcTo(leftTop+m_offset, rightBottom+m_offset, arcStartRefPoint+m_offset, arcEndRefPoint+m_offset, directionCounterclockwise);
    }

    virtual bool arcTo(const DrawCoord &centerPos, const DrawCoord &endPos, bool directionCounterclockwise, DrawCoord *pResEndPos = 0 ) override
    {
        DrawCoord ResEndPos;
        bool res = safedc()->arcTo(centerPos+m_offset, endPos+m_offset, directionCounterclockwise, &ResEndPos);
        if (res)
        {
            if (pResEndPos)
               *pResEndPos = ResEndPos-m_offset;
        }

        return res;
    }

    virtual bool arcTo(const DrawCoord &centerPos, const DrawCoord::value_type angleGradus, DrawCoord *pResEndPos = 0 ) override
    {
        DrawCoord ResEndPos;
        bool res = safedc()->arcTo(centerPos+m_offset, angleGradus, &ResEndPos);
        if (res)
        {
            if (pResEndPos)
               *pResEndPos = ResEndPos-m_offset;
        }

        return res;
    }

    virtual bool ellipse    (const DrawCoord &leftTop, const DrawCoord &rightBottom) override
    {
        return safedc()->ellipse(leftTop+m_offset, rightBottom+m_offset);
    }

    virtual bool fillEllipse(const DrawCoord &leftTop, const DrawCoord &rightBottom, bool drawFrame) override
    {
        return safedc()->fillEllipse(leftTop+m_offset, rightBottom+m_offset, drawFrame);
    }

    virtual bool circle    (const DrawCoord &centerPos, const DrawCoord::value_type &r) override
    {
        return safedc()->circle(centerPos+m_offset, r);
    }

    virtual bool fillCircle(const DrawCoord &centerPos, const DrawCoord::value_type &r, bool drawFrame) override
    {
        return safedc()->fillCircle(centerPos+m_offset, r, drawFrame);
    }


    std::vector<DrawCoord> makePointsVectorFromSizeAndPtrWithOffset(std::size_t numPoints, const DrawCoord *pPoints) const
    {
        std::vector<DrawCoord> points; points.reserve(numPoints);
        for(std::size_t i=0; pPoints && i!=numPoints; ++i, ++pPoints)
        {
            points.emplace_back(*pPoints + m_offset);
        }

        return points;
    }

    std::vector<DrawCoord> makePointsVectorFromVectorWithOffset(const std::vector<DrawCoord> &orgPoints) const
    {
        std::vector<DrawCoord> points; points.reserve(orgPoints.size());
        for(auto p : orgPoints)
        {
            points.emplace_back(p + m_offset);
        }

        return points;
    }

    //! Рисует набор горизонтальных и вертикальных линий, если две точки задают диагональную линию - это ошибка
    virtual bool roundRectFigure( const DrawCoord::value_type &cornersR
                                , std::size_t numPoints
                                , const DrawCoord             *pPoints
                                ) override
    {
        std::vector<DrawCoord> points = makePointsVectorFromSizeAndPtrWithOffset(numPoints, pPoints);
        if (points.empty())
            return false;

        return safedc()->roundRectFigure(cornersR, points.size(), &points[0]);
    }

    //! Implemented offten with serios of the lineTo and ellipticArcTo calls
    virtual bool roundRect( const DrawCoord::value_type &cornersR
                          , const DrawCoord             &leftTop
                          , const DrawCoord             &rightBottom
                          ) override
    {
        return safedc()->roundRect(cornersR, leftTop+m_offset, rightBottom+m_offset);
    }

    virtual bool fillRoundRect( const DrawCoord::value_type &cornersR
                          , const DrawCoord             &leftTop
                          , const DrawCoord             &rightBottom
                          , bool                         drawFrame
                          ) override
    {
        return safedc()->fillRoundRect(cornersR, leftTop+m_offset, rightBottom+m_offset, drawFrame);
    }

    virtual bool rect( const DrawCoord             &leftTop
                     , const DrawCoord             &rightBottom
                     ) override
    {
        return safedc()->rect(leftTop+m_offset, rightBottom+m_offset);
    }

    virtual bool fillRect( const DrawCoord             &leftTop
                         , const DrawCoord             &rightBottom
                         , bool                         drawFrame
                         ) override
    {
        return safedc()->fillRect(leftTop+m_offset, rightBottom+m_offset, drawFrame);
    }

    // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-gradientfill

    virtual bool fillGradientRect( const DrawCoord             &leftTop
                                 , const DrawCoord             &rightBottom
                                 , const ColorRef              &gradientColorBegin
                                 , const ColorRef              &gradientColorMid
                                 , const ColorRef              &gradientColorEnd
                                 , const DrawCoord::value_type &gradientMidPoint
                                 , GradientType                gradientType
                                 , bool                        excludeFrame
                                 ) override
    {
        return safedc()->fillGradientRect(leftTop+m_offset, rightBottom+m_offset, gradientColorBegin, gradientColorMid, gradientColorEnd, gradientMidPoint, gradientType, excludeFrame);
    }

    virtual bool fillGradientRect( const DrawCoord             &leftTop
                                 , const DrawCoord             &rightBottom
                                 , const GradientParams        &gradientParams
                                 , GradientType                gradientType
                                 , bool                        excludeFrame
                                 ) override
    {
        return safedc()->fillGradientRect(leftTop+m_offset, rightBottom+m_offset, gradientParams, gradientType, excludeFrame);
    }

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
                                      ) override
    {
        return safedc()->fillGradientRoundRect(cornersR, leftTop+m_offset, rightBottom+m_offset, gradientColorBegin, gradientColorMid, gradientColorEnd, gradientMidPoint, gradientType, excludeFrame, fillBreakPos, fillFlags);
    }

    virtual bool fillGradientRoundRect( DrawCoord::value_type       cornersR
                                      , const DrawCoord             &leftTop
                                      , const DrawCoord             &rightBottom
                                      , const GradientParams        &gradientParams
                                      , GradientType                gradientType
                                      , bool                        excludeFrame
                                      , DrawCoord::value_type       fillBreakPos
                                      , GradientRoundRectFillFlags  fillFlags // = GradientRoundRectFillFlags::roundBoth | GradientRoundRectFillFlags::fillFull
                                      ) override
    {
        return safedc()->fillGradientRoundRect(cornersR, leftTop+m_offset, rightBottom+m_offset, gradientParams, gradientType, excludeFrame, fillBreakPos, fillFlags);
    }

    virtual bool fillGradientCircle( const DrawCoord             &pos
                                   , const DrawCoord::value_type &r
                                   , const ColorRef              &gradientColorBegin
                                   , const ColorRef              &gradientColorMid
                                   , const ColorRef              &gradientColorEnd
                                   , const DrawCoord::value_type &gradientMidPoint
                                   , bool                        excludeFrame
                                   ) override
    {
        return safedc()->fillGradientCircle(pos+m_offset, r, gradientColorBegin, gradientColorMid, gradientColorEnd, gradientMidPoint, excludeFrame);
    }

    virtual bool fillGradientCircle( const DrawCoord             &pos
                                   , const DrawCoord::value_type &r
                                   , const GradientParams        &gradientParams
                                   , bool                        excludeFrame
                                   ) override
    {
        return safedc()->fillGradientCircle(pos+m_offset, r, gradientParams, excludeFrame);
    }

    virtual bool checkPolyCubicBezierNumPoints  (std::size_t numPoints) const override
    {
        return safedc()->checkPolyCubicBezierNumPoints(numPoints);
    }

    virtual bool checkPolyCubicBezierToNumPoints(std::size_t numPoints) const override
    {
        return safedc()->checkPolyCubicBezierToNumPoints(numPoints);
    }

    virtual bool polyCubicBezier  (const DrawCoord * pPoints, std::size_t numPoints) override
    {
        std::vector<DrawCoord> points = makePointsVectorFromSizeAndPtrWithOffset(numPoints, pPoints);
        if (points.empty())
            return false;

        return safedc()->polyCubicBezier(&points[0], points.size());
    }

    virtual bool polyCubicBezierTo(const DrawCoord * pPoints, std::size_t numPoints) override
    {
        std::vector<DrawCoord> points = makePointsVectorFromSizeAndPtrWithOffset(numPoints, pPoints);
        if (points.empty())
            return false;

        return safedc()->polyCubicBezierTo(&points[0], points.size());
    }

    virtual bool polyCubicBezier  (const std::vector<DrawCoord> &orgPoints) override
    {
        return safedc()->polyCubicBezier(makePointsVectorFromVectorWithOffset(orgPoints));
    }

    virtual bool polyCubicBezierTo(const std::vector<DrawCoord> &orgPoints) override
    {
        return safedc()->polyCubicBezierTo(makePointsVectorFromVectorWithOffset(orgPoints));
    }

    virtual bool checkPolyQuadraticBezierNumPoints  (std::size_t numPoints) const override
    {
        return safedc()->checkPolyQuadraticBezierNumPoints(numPoints);
    }

    virtual bool checkPolyQuadraticBezierToNumPoints(std::size_t numPoints) const override
    {
        return safedc()->checkPolyQuadraticBezierToNumPoints(numPoints);
    }

    virtual bool polyQuadraticBezier  (const DrawCoord * pPoints, std::size_t numPoints) override
    {
        std::vector<DrawCoord> points = makePointsVectorFromSizeAndPtrWithOffset(numPoints, pPoints);
        if (points.empty())
            return false;

        return safedc()->polyQuadraticBezier(&points[0], points.size());
    }

    virtual bool polyQuadraticBezierTo(const DrawCoord * pPoints, std::size_t numPoints) override
    {
        std::vector<DrawCoord> points = makePointsVectorFromSizeAndPtrWithOffset(numPoints, pPoints);
        if (points.empty())
            return false;

        return safedc()->polyQuadraticBezierTo(&points[0], points.size());
    }

    virtual bool polyQuadraticBezier  (const std::vector<DrawCoord> &orgPoints) override
    {
        return safedc()->polyQuadraticBezier(makePointsVectorFromVectorWithOffset(orgPoints));
    }

    virtual bool polyQuadraticBezierTo(const std::vector<DrawCoord> &orgPoints) override
    {
        return safedc()->polyQuadraticBezierTo(makePointsVectorFromVectorWithOffset(orgPoints));
    }

    virtual IImageList* createImageList() const override
    {
        return safedc()->createImageList();
    }

    virtual void destroyImageList(IImageList* pImgList) const override
    {
        return safedc()->destroyImageList(pImgList);
    }

    virtual std::shared_ptr<IImageList> createSharedImageList() const override
    {
        return safedc()->createSharedImageList();
    }

    virtual bool drawImageSimple( std::shared_ptr<IImageList> pImgList, int idx, const DrawCoord &pos) override
    {
        return safedc()->drawImageSimple(pImgList, idx, pos+m_offset);
    }

    virtual bool drawImageSimple( IImageList                 *pImgList, int idx, const DrawCoord &pos) override
    {
        return safedc()->drawImageSimple(pImgList, idx, pos+m_offset);
    }

    virtual bool drawImageSimpleEx( std::shared_ptr<IImageList> pImgList, int idx, const DrawCoord &pos, ImageSize imgPartLeftTop, ImageSize imgPartSize) override
    {
        return safedc()->drawImageSimpleEx(pImgList, idx, pos+m_offset, imgPartLeftTop, imgPartSize);
    }

    virtual bool drawImageSimpleEx( IImageList                 *pImgList, int idx, const DrawCoord &pos, ImageSize imgPartLeftTop, ImageSize imgPartSize) override
    {
        return safedc()->drawImageSimpleEx(pImgList, idx, pos+m_offset, imgPartLeftTop, imgPartSize);
    }

    virtual bool drawImageScaled( std::shared_ptr<IImageList> pImgList, int idx, const DrawCoord &pos, const DrawCoord &imgScreenSize, ImageSize imgPartLeftTop, ImageSize imgPartSize) override
    {
        return safedc()->drawImageScaled(pImgList, idx, pos+m_offset, imgScreenSize, imgPartLeftTop, imgPartSize);
    }

    virtual bool drawImageScaled( IImageList                 *pImgList, int idx, const DrawCoord &pos, const DrawCoord &imgScreenSize, ImageSize imgPartLeftTop, ImageSize imgPartSize) override
    {
        return safedc()->drawImageScaled(pImgList, idx, pos+m_offset, imgScreenSize, imgPartLeftTop, imgPartSize);
    }



}; // struct IDrawContext

    

} // namespace marty_draw_context




