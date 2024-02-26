#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


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

    DrawingColor getPenColor(int penId) const
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
                      //, bool          directionCounterclockwise
                      , int arcDirection // ArcDirectionEnum
                      ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;
        return pDc->ellipticArcTo(leftTop, rightBottom, arcStartRefPoint, arcEndRefPoint, arcDirection ? true : false /* directionCounterclockwise */ );
    }

    mutable DrawingCoords lastArcEndPos;

    DrawingCoords getLastArcEndPos() const
    {
        return lastArcEndPos;
    }

    bool arcToPos( DrawingCoords centerPos, DrawingCoords endPos
                 , bool directionCounterclockwise
                 , int arcDirection // ArcDirectionEnum
                 ) const
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        DrawCoord calculatedEndPos;
        bool res = pDc->arcTo(centerPos, endPos, arcDirection ? true : false /* directionCounterclockwise */, &calculatedEndPos);
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


    bool drawImageSimple(ImageListWrapper imgListWrapper, int idx, DrawingCoords pos)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        return pDc->drawImageSimple(imgListWrapper.m_pImgList, idx, DrawCoord(pos) );
    }

    bool drawImageSimpleEx(ImageListWrapper imgListWrapper, int idx, DrawingCoords pos, ImageSize imgPartLeftTop, ImageSize imgPartSize)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        return pDc->drawImageSimpleEx(imgListWrapper.m_pImgList, idx, DrawCoord(pos), imgPartLeftTop, imgPartSize );
    }

    bool drawImageScaled(ImageListWrapper imgListWrapper, int idx, DrawingCoords pos, DrawingCoords targetSize, ImageSize imgPartLeftTop, ImageSize imgPartSize)
    {
        MARTY_DC_BIND_SQUIRREL_ASSERT(pDc);
        if (!pDc)
            return false;

        return pDc->drawImageScaled(imgListWrapper.m_pImgList, idx, DrawCoord(pos), DrawCoord(targetSize), imgPartLeftTop, imgPartSize );
    }



    static
    marty_simplesquirrel::ClassInfo getClassInfo(const std::string &clsName = "Context")
    {
        auto clsInfo = marty_simplesquirrel::ClassInfo(clsName);

        // clsInfo.addConstructor("any_integral width, Drawing.LineEndcapStyle endcaps, Drawing.LineJoinStyle join");
        //  

        clsInfo.addFunc("void flushBits()");
        clsInfo.addFunc("Drawing.DrawingPrecise setDrawingPrecise(Drawing.DrawingPrecise p)");
        clsInfo.addFunc("Drawing.DrawingPrecise getDrawingPrecise() const");
        clsInfo.addFunc("Drawing.Coords getRawSize() const");
        clsInfo.addFunc("Drawing.Coords getSize() const");
        clsInfo.addFunc("float distanceBetween(Drawing.Coords pos1, Drawing.Coords pos2) const");
        clsInfo.addFunc("Drawing.Coords reflectPoint(Drawing.Coords point, Drawing.Coords reflectRelativeTo) const");

        // clsInfo.addFunc("getResourcesState"); //TODO: !!!
        // clsInfo.addFunc("restoreResourcesState"); //TODO: !!!

        // clsInfo.addFunc("getOffsetScale"); //TODO: !!!
        // clsInfo.addFunc("restoreOffsetScale"); //TODO: !!!

        clsInfo.addFunc("bool setCollectMarkers(bool newCollectMarkersMode)");
        clsInfo.addFunc("bool getCollectMarkers() const");
        clsInfo.addFunc("bool markerAdd(Drawing.Coords markerPos)");
        clsInfo.addFunc("bool markerAddEx(Drawing.Coords markerPos, integer|float|string markerSize)");
        clsInfo.addFunc("bool markersClear() const");
        clsInfo.addFunc("bool markersDraw() const");
        clsInfo.addFunc("bool markersDrawEx(int penId) const");

        clsInfo.addFunc("float markerSetDefSize(integer|float|string markerSize)");
        clsInfo.addFunc("float markerGetDefSize() const");

        clsInfo.addFunc("Drawing.SmoothingMode  setSmoothingMode( Drawing.SmoothingMode smoothingMode)");
        clsInfo.addFunc("Drawing.SmoothingMode  getSmoothingMode() const");

        clsInfo.addFunc("Drawing.Color setTextColor(Drawing.Color clr)");
        clsInfo.addFunc("Drawing.Color getTextColor() const");

        clsInfo.addFunc("Drawing.Color setBkColor(Drawing.Color clr)");
        clsInfo.addFunc("Drawing.Color getBkColor() const");

        clsInfo.addFunc("Drawing.BkMode setBkMode(Drawing.BkMode bkMode)");
        clsInfo.addFunc("Drawing.BkMode getBkMode() const");

        clsInfo.addFunc("Drawing.Coords getDialigBaseUnits() const");

        clsInfo.addFunc("Drawing.Coords mapRawToLogicPos(Drawing.Coords c) const");
        clsInfo.addFunc("Drawing.Coords mapRawToLogicSize(Drawing.Coords c) const");

        clsInfo.addFunc("Drawing.Coords getPixelSize() const");

        clsInfo.addFunc("Drawing.Coords getScaledPos( Drawing.Coords c ) const");
        clsInfo.addFunc("Drawing.Coords getScaledSize( Drawing.Coords c ) const");

        clsInfo.addFunc("Drawing.Coords setOffset( Drawing.Coords c )");
        clsInfo.addFunc("Drawing.Coords getOffset( ) const");

        clsInfo.addFunc("Drawing.Coords setScale( Drawing.Coords c )");
        clsInfo.addFunc("Drawing.Coords getScale( ) const");

        clsInfo.addFunc("float setPenScale( integer|float|string scale )");
        clsInfo.addFunc("float getPenScale( ) const");

        clsInfo.addFunc("integer createSolidPen( Drawing.PenParams penParams, Drawing.Color clr )");
        clsInfo.addFunc("integer selectPen( integer penId ) const");
        clsInfo.addFunc("integer selectNewSolidPen( Drawing.PenParams penParams, Drawing.Color clr ) const");
        clsInfo.addFunc("integer getCurPen() const");
        clsInfo.addFunc("Drawing.Color getPenColor(integer penId)");
        clsInfo.addFunc("Drawing.PenParams getPenParams(integer penId) const");
        clsInfo.addFunc("integer setDefaultCosmeticPen( integer penId )");
        clsInfo.addFunc("integer getDefaultCosmeticPen( ) const");

        clsInfo.addFunc("integer createSolidBrush( Drawing.Color rgb )");
        clsInfo.addFunc("integer selectBrush( integer brushId )");
        clsInfo.addFunc("integer selectNewSolidBrush( Drawing.Color rgb )");
        clsInfo.addFunc("integer getCurBrush() const");

        clsInfo.addFunc("integer createFont(Drawing.FontParams fontParams)");
        clsInfo.addFunc("integer createFontEx(Drawing.FontParams fontParams, integer|float|string height)");
        clsInfo.addFunc("integer createOrFindFont(Drawing.FontParams fontParams)");
        clsInfo.addFunc("integer createOrFindFontEx(Drawing.FontParams fontParams, integer|float|string height)");

        clsInfo.addFunc("integer selectFont( integer fontId )");
        clsInfo.addFunc("integer selectNewFont(Drawing.FontParams fontParams)");
        clsInfo.addFunc("integer selectNewFontEx(Drawing.FontParams fontParams, integer|float|string height) const");

        clsInfo.addFunc("integer createFontWithFace(Drawing.FontParams fontParams, string fontFace)");
        clsInfo.addFunc("integer createOrFindFontWithFace(Drawing.FontParams fontParams, string fontFace)");

        clsInfo.addFunc("integer  getCurFont() const");
        clsInfo.addFunc("Drawing.FontParams getFontParamsById(integer id) const");

        clsInfo.addFunc("bool beginPath()");
        clsInfo.addFunc("bool beginPathFrom(Drawing.Coords c)");
        clsInfo.addFunc("bool endPath( bool bStroke, bool bFill )");
        clsInfo.addFunc("bool closeFigure()");
        clsInfo.addFunc("bool isPathStarted() const");

        clsInfo.addFunc("bool moveTo( Drawing.Coords to )");
        clsInfo.addFunc("bool lineTo( Drawing.Coords to )");

        clsInfo.addFunc("bool ellipse(Drawing.Coords leftTop, Drawing.Coords rightBottom)");
        clsInfo.addFunc("bool fillEllipse(Drawing.Coords leftTop, Drawing.Coords rightBottom, bool drawFrame)");

        clsInfo.addFunc("bool ellipticArcTo( Drawing.Coords leftTop, Drawing.Coords rightBottom, Drawing.Coords arcStartRefPoint, Drawing.Coords arcEndRefPoint, Drawing.ArcDirection arcDirection) const");
        clsInfo.addFunc("Drawing.Coords getLastArcEndPos() const");
        clsInfo.addFunc("bool arcToPos(Drawing.Coords centerPos, Drawing.Coords endPos, Drawing.ArcDirection arcDirection)");
        clsInfo.addFunc("bool arcByAngleDeg(Drawing.Coords centerPos, integer|float|string angle)");

        clsInfo.addFunc("bool roundRectFigure( integer|float|string cornersR, array of Drawing.Coords points )");

        clsInfo.addFunc("bool circle(Drawing.Coords centerPos, integer|float|string r)");
        clsInfo.addFunc("bool fillCircle(Drawing.Coords centerPos, integer|float|string r, bool drawFrame)");
        clsInfo.addFunc("bool roundRect(integer|float|string cornersR, Drawing.Coords leftTop, Drawing.Coords rightBottom)");
        clsInfo.addFunc("bool fillRoundRect(integer|float|string cornersR, Drawing.Coords leftTop, Drawing.Coords rightBottom, bool drawFrame)");
        clsInfo.addFunc("bool rect(Drawing.Coords leftTop, Drawing.Coords rightBottom)");
        clsInfo.addFunc("bool fillRect(Drawing.Coords leftTop, Drawing.Coords rightBottom, bool drawFrame)");
        clsInfo.addFunc("bool fillGradientRect(Drawing.Coords leftTop, Drawing.Coords rightBottom, Drawing.GradientParams gradientParams, Drawing.GradientType gradientType, bool excludeFrame)");
        clsInfo.addFunc("bool fillGradientRoundRect( integer|float|string cornersR, Drawing.Coords leftTop, Drawing.Coords rightBottom, Drawing.GradientParams gradientParams, Drawing.GradientType gradientType, bool excludeFrame, float fillBreakPos, Drawing.GradientRoundRectFillFlags fillFlags)");
        clsInfo.addFunc("bool fillGradientCircle(Drawing.Coords pos, integer|float|string r, Drawing.GradientParams gradientParams, bool excludeFrame)");

        clsInfo.addFunc("bool textOut(Drawing.Coords pos, string text)");
        clsInfo.addFunc("bool textOutWithFontAndColor(Drawing.Coords pos, int fontId, Drawing.Color clr, string text)");

        clsInfo.addFunc("bool drawTextColored( Drawing.Coords startPos"
                                             ", integer|float|string widthLim"
                                             ", DrawTextFlags flags"
                                             ", string    text"
                                             ", string    stopChars"
                                             ", array of Drawing.Color colors"
                                             ", array of Drawing.Color bkColors"
                                             ", int fontId"
                                             ")"
                                             );
        clsInfo.addFunc("bool drawParaColored( Drawing.Coords   startPos"
                                            ", Drawing.Coords  limits"
                                            ", integer|float|string lineSpacing"
                                            ", integer|float|string paraIndent"
                                            ", integer|float|string tabSize"
                                            ", DrawTextFlags flags"
                                            ", Drawing.HorAlign horAlign"
                                            ", Drawing.VertAlign vertAlign"
                                            ", string text"
                                            ", array of Drawing.Color colors"
                                            ", array of Drawing.Color bkColors"
                                            ", array of integer|float|string tabStopPositions"
                                            ", int fontId"
                                            ")"
                                            );
        clsInfo.addFunc("bool drawMultiParasColored( Drawing.Coords startPos"
                                                  ", Drawing.Coords  limits"
                                                  ", integer|float|string lineSpacing"
                                                  ", integer|float|string paraIndent"
                                                  ", integer|float|string tabSize"
                                                  ", DrawTextFlags flags"
                                                  ", Drawing.HorAlign horAlign"
                                                  ", Drawing.VertAlign vertAlign"
                                                  ", string text"
                                                  ", array of Drawing.Color colors"
                                                  ", array of Drawing.Color bkColors"
                                                  ", array of integer|float|string tabStopPositions"
                                                  ", array of Drawing.Color paraColors"
                                                  ", array of Drawing.Color paraBkColors"
                                                  ", int fontId"
                                                   ")"
                                             );

        //  
        clsInfo.addFunc("bool polyQuadraticBezier(Drawing.Coords cp1, Drawing.Coords cp2, Drawing.Coords cp3)");
        clsInfo.addFunc("bool polyQuadraticBezierTo(Drawing.Coords cp2, Drawing.Coords cp3)");

        clsInfo.addFunc("bool polyCubicBezier(Drawing.Coords cp1, Drawing.Coords cp2, Drawing.Coords cp3, Drawing.Coords cp4)");
        clsInfo.addFunc("bool polyCubicBezierTo(Drawing.Coords cp2, Drawing.Coords cp3, Drawing.Coords cp4)");

        clsInfo.addFunc("bool polyCubicBeziers(array of Drawing.Coords points)");
        clsInfo.addFunc("bool polyCubicBeziersTo(array of Drawing.Coords points)");

        clsInfo.addFunc("bool polyQuadraticBeziers(array of Drawing.Coords points)");
        clsInfo.addFunc("bool polyQuadraticBeziersTo(array of Drawing.Coords points)");

        
        clsInfo.addFunc("float distanceBetween( Drawing.Coords pos1, Drawing.Coords pos2)");
        clsInfo.addFunc("Drawing.Coords reflectPoint( Drawing.Coords pos, Drawing.Coords relativeTo)");


        // clsInfo.addFunc("");
        // clsInfo.addFunc("");


        return clsInfo;
    }


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

        cls.addFunc( _SC("drawImageSimple")        , &DrawingContext::drawImageSimple);
        cls.addFunc( _SC("drawImageSimpleEx")      , &DrawingContext::drawImageSimpleEx);
        cls.addFunc( _SC("drawImageScaled")        , &DrawingContext::drawImageScaled);


        return cls;
    }

}; // struct DrawingContext



} // namespace simplesquirrel {
} // namespace marty_draw_context {
