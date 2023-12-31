#pragma once

#include "draw_context_types.h"
#include "svg_enums.h"
#include "utils.h"

//
#include "assert.h"

//
#include <pugixml/pugixml.hpp>

//
#include <cstdint>
#include <utility>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace marty_draw_context {

namespace svg {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
typedef  marty_draw_context::SizeWithDimensions     SizeWithDimensions;
typedef  marty_draw_context::ViewBox                ViewBox           ;

//----------------------------------------------------------------------------




//! Returns namespace alias
inline
std::string parseXmlTagName(const std::string &fullName, std::string &name)
{
    std::size_t pos = fullName.find(':');
    if (pos==fullName.npos)
    {
        name = fullName;
        return std::string(); // return empty ns
    }

    name = std::string(fullName, pos+1);

    return std::string(fullName, 0, pos);
}

//! Returns namespace alias
inline
std::string parseXmlAttrName(const std::string &fullName, std::string &name)
{
    return parseXmlTagName(fullName, name);
}

//! Returns namespace full name
inline
std::string parseXmlTagName(const std::unordered_map< std::string, std::string > &nsAliasToName, const std::string &fullName, std::string &name)
{
    std::string nsAlias = parseXmlTagName(fullName, name);

    std::unordered_map< std::string, std::string >::const_iterator it = nsAliasToName.find(nsAlias);
    if (it==nsAliasToName.end())
    {
        throw std::runtime_error("parseXmlTagName: failed to find XML namespace alias");
    }

    return it->second;
}

//! Returns namespace full name
inline
std::string parseXmlAttrName(const std::unordered_map< std::string, std::string > &nsAliasToName, const std::string &fullName, std::string &name)
{
    return parseXmlTagName(nsAliasToName, fullName, name);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct PathDataEntry
{
    PathSubcommand             entryCommand = PathSubcommand::unknown;
    std::vector<DrawCoord>     params      ;

    bool isValidCommand() const
    {
         return entryCommand!=PathSubcommand::unknown;
    }

    static
    PathSubcommand subcommandFromChar(char ch)
    {
        switch(ch)
        {
            case 'M': return PathSubcommand::moveToAbs                      ;
            case 'm': return PathSubcommand::moveToRel                      ;
            case 'Z': return PathSubcommand::closePathZ                     ;
            case 'z': return PathSubcommand::closePath                      ;
            case 'L': return PathSubcommand::lineToAbs                      ;
            case 'l': return PathSubcommand::lineToRel                      ;
            case 'H': return PathSubcommand::lineToHorAbs                   ;
            case 'h': return PathSubcommand::lineToHorRel                   ;
            case 'V': return PathSubcommand::lineToVertAbs                  ;
            case 'v': return PathSubcommand::lineToVertRel                  ;
            case 'C': return PathSubcommand::cubicBezierToAbs               ;
            case 'c': return PathSubcommand::cubicBezierToRel               ;
            case 'S': return PathSubcommand::cubicBezierReflectedCpToAbs    ;
            case 's': return PathSubcommand::cubicBezierReflectedCpToRel    ;
            case 'Q': return PathSubcommand::quadraticBezierToAbs           ;
            case 'q': return PathSubcommand::quadraticBezierToRel           ;
            case 'T': return PathSubcommand::quadraticBezierReflectedCpToAbs;
            case 't': return PathSubcommand::quadraticBezierReflectedCpToRel;

            case PathSubcommand::unknown: [[fallthrough]];
            default : return PathSubcommand::unknown;
        }
    }

    static
    PathDataEntry fromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        PathDataEntry e;

        std::size_t pos = 0;
        for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip leading WS

        if (*pStr==0)
        {
            MARTY_IDC_ASSERT_FAIL_MSG("marty_draw_context::svg::PathDataEntry: unexpected end of path subcommands");
            // throw std::runtime_error("marty_draw_context::svg::PathDataEntry: unexpected end of path subcommands");
        }

        e.entryCommand = subcommandFromChar(*pStr);
        if (!e.isValidCommand())
        {
            MARTY_IDC_ASSERT_FAIL_MSG(std::string("marty_draw_context::svg::PathDataEntry: unknown path subcommand: '") + pStr + std::string("'"));
            //throw std::runtime_error(std::string("marty_draw_context::svg::PathDataEntry: unknown path subcommand: '") + pStr + std::string("'"));
        }

        ++pStr; ++pos;

        switch(e.entryCommand)
        {
            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataMovetoCommands
            case PathSubcommand::moveToAbs                      : [[fallthrough]];
            case PathSubcommand::moveToRel                      : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    e.params.emplace_back(DrawCoord::fromString(pStr, &pos2));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataClosePathCommand
            // На команде закрытия path никаких параметров нет
            case PathSubcommand::closePathZ                     : [[fallthrough]];
            case PathSubcommand::closePath                      : 
            {
                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands
            case PathSubcommand::lineToAbs                      : [[fallthrough]];
            case PathSubcommand::lineToRel                      : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    e.params.emplace_back(DrawCoord::fromString(pStr, &pos2));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands
            case PathSubcommand::lineToHorAbs                   : [[fallthrough]];
            case PathSubcommand::lineToHorRel                   : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    auto lineToPos = DrawCoord::valueFromString(pStr, &pos2);
                    e.params.emplace_back(DrawCoord(lineToPos,0));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands
            case PathSubcommand::lineToVertAbs                  : [[fallthrough]];
            case PathSubcommand::lineToVertRel                  : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    auto lineToPos = DrawCoord::valueFromString(pStr, &pos2);
                    e.params.emplace_back(DrawCoord(0,lineToPos));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataCubicBezierCommands
            case PathSubcommand::cubicBezierToAbs               : [[fallthrough]];
            case PathSubcommand::cubicBezierToRel               : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    e.params.emplace_back(DrawCoord::fromString(pStr, &pos2));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                if ((e.params.size()%3)!=0)
                {
                    MARTY_IDC_ASSERT_FAIL_MSG("marty_draw_context::svg::PathDataEntry: wrong number or arguments in cubic bezier (C/c) curve");
                    //throw std::runtime_error("marty_draw_context::svg::PathDataEntry: wrong number or arguments in cubic bezier (C/c) curve");
                }

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataCubicBezierCommands
            case PathSubcommand::cubicBezierReflectedCpToAbs    : [[fallthrough]];
            case PathSubcommand::cubicBezierReflectedCpToRel    : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    e.params.emplace_back(DrawCoord::fromString(pStr, &pos2));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                if ((e.params.size()%2)!=0)
                {
                    MARTY_IDC_ASSERT_FAIL_MSG("marty_draw_context::svg::PathDataEntry: wrong number or arguments in cubic bezier (S/s) curve");
                    //throw std::runtime_error("marty_draw_context::svg::PathDataEntry: wrong number or arguments in cubic bezier (S/s) curve");
                }

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataQuadraticBezierCommands
            case PathSubcommand::quadraticBezierToAbs           : [[fallthrough]];
            case PathSubcommand::quadraticBezierToRel           : 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    e.params.emplace_back(DrawCoord::fromString(pStr, &pos2));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                if ((e.params.size()%2)!=0)
                {
                    MARTY_IDC_ASSERT_FAIL_MSG("marty_draw_context::svg::PathDataEntry: wrong number or arguments in quadratic bezier (Q/q) curve");
                    //throw std::runtime_error("marty_draw_context::svg::PathDataEntry: wrong number or arguments in quadratic bezier (Q/q) curve");
                }

                break;
            }

            // https://www.w3.org/TR/SVGTiny12/paths.html#PathDataQuadraticBezierCommands
            case PathSubcommand::quadraticBezierReflectedCpToAbs: [[fallthrough]];
            case PathSubcommand::quadraticBezierReflectedCpToRel: 
            {
                do
                {
                    for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
                    if (*pStr==0)
                    {
                        break;
                    }
                    std::size_t pos2 = 0;
                    e.params.emplace_back(DrawCoord::fromString(pStr, &pos2));
                    pStr += pos2;
                    pos  += pos2;
                    for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
                }
                while(subcommandFromChar(*pStr)==PathSubcommand::unknown); // Если там число или знак следующей точки, или пробел, или ноль - значит, список координат продолжается (subcommandFromChar вернёт invalid)

                // if ((e.params.size()%2)!=0)
                // {
                //     MARTY_IDC_ASSERT_FAIL_MSG("marty_draw_context::svg::PathDataEntry: wrong number or arguments in quadratic bezier (T/t) curve");
                //     throw std::runtime_error("marty_draw_context::svg::PathDataEntry: wrong number or arguments in quadratic bezier (T/t) curve");
                // }

                break;
            }

            case PathSubcommand::unknown: [[fallthrough]];
            default:
            {
                MARTY_IDC_ASSERT_FAIL_MSG("marty_draw_context::svg::PathDataEntry: unknown path subcommand");
                //throw std::runtime_error("marty_draw_context::svg::PathDataEntry: unknown path subcommand");
            }
        
        }

        if (pPosOut)
        {
            *pPosOut = pos;
        }

        return e;
    }

    static
    PathDataEntry fromString(const std::string &str, std::size_t* pPosOut = 0)
    {
        return fromString(str.c_str(), pPosOut);
    }

}; // struct PathDataEntry

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct Shape
{

protected:

    ShapeType                    shapeType  ;
    std::string                  id         ;
    std::vector<PathDataEntry>   pathEntries; //!< Если shapeType==ShapeType::path
    std::vector<DrawCoord>       shapeParams; //!< Геометрические параметры всех фигур, кроме path. В зависимости от типа фигуры там лежат разные значения.
    std::vector<Shape>           groupShapes;


    void expandShapeParams(std::size_t n, const DrawCoord &defVal = DrawCoord(0,0))
    {
        while(shapeParams.size()<n)
        {
            shapeParams.emplace_back(defVal);
        }
    }

    static
    std::vector<DrawCoord> parseCoordsVectorString(const char* pStr, std::size_t* pPosOut)
    {
        std::vector<DrawCoord> resVec;

        std::size_t pos = 0;
        do
        {
            for(; *pStr && (*pStr==',' || *pStr==';' || *pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // remove separators before
            if (*pStr==0)
            {
                break;
            }
            std::size_t pos2 = 0;
            resVec.emplace_back(DrawCoord::fromString(pStr, &pos2));
            pStr += pos2;
            pos  += pos2;
            for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS
        }
        while(*pStr!=0);

        if (pPosOut)
        {
            *pPosOut = pos;
        }

        return resVec;
    }


public:

    ShapeType                          getShapeType() const { return shapeType  ; }
    std::string                        getId()        const { return id         ; }
    const std::vector<PathDataEntry>&  getPathData()  const { return pathEntries; }

    bool isShapeValid() const
    {
        switch(shapeType)
        {
            case ShapeType::path     : return isPathValid()    ;
            case ShapeType::rect     : return isRectValid()    ;
            case ShapeType::circle   : return isCircleValid()  ;
            case ShapeType::ellipse  : return isEllipseValid() ;
            case ShapeType::line     : return isLineValid()    ;
            case ShapeType::polyline : return isPolylineValid();
            case ShapeType::polygon  : return isPolygonValid() ;

            case ShapeType::group    : return isGroupValid()   ;

            case ShapeType::text     : [[fallthrough]];
            case ShapeType::textArea : [[fallthrough]];

            case ShapeType::unknown  : [[fallthrough]];

            default: return false;
        };
    }

    bool isPathValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::path);
        return pathEntries.size()>0; //TODO: !!! На самом деле надо более комплексную проверку сделать
    }

    // https://www.w3.org/TR/SVGTiny12/shapes.html

    // rect
    // x = "<coordinate>"  The x-axis coordinate of the side of the rectangle which has the smaller x-axis coordinate value in the current user coordinate system. The lacuna value is '0'.
    // y = "<coordinate>"  The y-axis coordinate of the side of the rectangle which has the smaller y-axis coordinate value in the current user coordinate system. The lacuna value is '0'.
    // width = "<length>"  The width of the rectangle. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
    // height = "<length>" The height of the rectangle. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
    // rx = "<length>"     For rounded rectangles, the x-axis radius of the ellipse used to round off the corners of the rectangle. A negative value is unsupported. See the notes below about what happens if the attribute is not specified.
    // ry = "<length>"     For rounded rectangles, the y-axis radius of the ellipse used to round off the corners of the rectangle. A negative value is unsupported. See the notes below about what happens if the attribute is not specified.

    bool isRectValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);

        if (shapeParams.size()<2)
        {
            return false;
        }

        if (shapeParams[1].x<0 || shapeParams[1].y<0) // Ширина и высота не могут быть отрицательными
        {
            return false;
        }

        return false;
    }

    DrawCoord getRectPos() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        MARTY_IDC_ASSERT(shapeParams.size()>0);
        return shapeParams[0];
    }

    DrawCoord getRectSize() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        MARTY_IDC_ASSERT(shapeParams.size()>1);
        return shapeParams[1];
    }

    bool isRectRound() const
    {
        return shapeParams.size()>2;
    }

    DrawCoord getRectRadiusXY() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        MARTY_IDC_ASSERT(shapeParams.size()>2);
        return shapeParams[2];
    }

    DrawCoord::value_type getRectRadius() const
    {
        auto rXY = getRectRadiusXY();
        //return (rXY.x+rXY.y)/2.0;
        return std::max(rXY.x, rXY.y);
    }
    
protected:

    void setRectPosX(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        expandShapeParams(1);
        shapeParams[0].x = v;
    }

    void setRectPosY(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        expandShapeParams(1);
        shapeParams[0].y = v;
    }

    void setRectWidth(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        expandShapeParams(2);
        shapeParams[1].x = v;
    }

    void setRectHeight(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        expandShapeParams(2);
        shapeParams[1].y = v;
    }

    void setRectRadiusX(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        expandShapeParams(3);
        shapeParams[2].x = v;
    }

    void setRectRadiusY(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::rect);
        expandShapeParams(3);
        shapeParams[2].y = v;
    }


public:

    // https://www.w3.org/TR/SVGTiny12/shapes.html

    // circle
    // cx = "<coordinate>" The x-axis coordinate of the center of the circle. The lacuna value is '0'.
    // cy = "<coordinate>" The y-axis coordinate of the center of the circle. The lacuna value is '0'.
    // r  = "<length>"     The radius of the circle. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.

    bool isCircleValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::circle);

        if (shapeParams.size()<2)
        {
            return false;
        }

        if (shapeParams[1].x<0)
        {
            return false;
        }

        return true;
    }

    DrawCoord getCircleCenter() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::circle);
        MARTY_IDC_ASSERT(shapeParams.size()>0);
        return shapeParams[0];
    }

    DrawCoord::value_type getCircleRadius() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::circle);
        MARTY_IDC_ASSERT(shapeParams.size()>1);
        return shapeParams[1].x;
    }

protected:

    void setCircleCenterX(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::circle);
        expandShapeParams(1);
        shapeParams[0].x = v;
    }

    void setCircleCenterY(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::circle);
        expandShapeParams(1);
        shapeParams[0].y = v;
    }

    void setCircleRadius(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::circle);
        expandShapeParams(2);
        shapeParams[1].x = v;
    }


public:

    // https://www.w3.org/TR/SVGTiny12/shapes.html

    // ellipse
    // cx = "<coordinate>"  The x-axis coordinate of the center of the ellipse. The lacuna value is '0'.
    // cy = "<coordinate>"  The y-axis coordinate of the center of the ellipse. The lacuna value is '0'.
    // rx = "<length>"      The x-axis radius of the ellipse. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
    // ry = "<length>"      The y-axis radius of the ellipse. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.

    bool isEllipseValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);

        if (shapeParams.size()<2)
        {
            return false;
        }

        if (shapeParams[1].x<0 || shapeParams[1].y<0)
        {
            return false;
        }

        return true;
    }

    DrawCoord getEllipseCenter() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);
        MARTY_IDC_ASSERT(shapeParams.size()>0);
        return shapeParams[0];
    }

    DrawCoord getEllipseSize() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);
        MARTY_IDC_ASSERT(shapeParams.size()>1);
        return shapeParams[1];
    }

protected:

    void setEllipseCenterX(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);
        expandShapeParams(1);
        shapeParams[0].x = v;
    }

    void setEllipseCenterY(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);
        expandShapeParams(1);
        shapeParams[0].y = v;
    }

    void setEllipseWidth(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);
        expandShapeParams(2);
        shapeParams[1].x = v;
    }

    void setEllipseHeight(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::ellipse);
        expandShapeParams(2);
        shapeParams[1].y = v;
    }

public:

    // https://www.w3.org/TR/SVGTiny12/shapes.html

    // line
    // x1 = "<coordinate>" The x-axis coordinate of the start of the line. The lacuna value is '0'.
    // y1 = "<coordinate>" The y-axis coordinate of the start of the line. The lacuna value is '0'.
    // x2 = "<coordinate>" The x-axis coordinate of the end of the line. The lacuna value is '0'.
    // y2 = "<coordinate>" The y-axis coordinate of the end of the line. The lacuna value is '0'.

    bool isLineValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);

        if (shapeParams.size()<2)
        {
            return false;
        }

        return true;
    }

    DrawCoord getLineStart() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);
        MARTY_IDC_ASSERT(shapeParams.size()>0);
        return shapeParams[0];
    }

    DrawCoord getLineEnd() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);
        MARTY_IDC_ASSERT(shapeParams.size()>1);
        return shapeParams[1];
    }

protected:

    void setLineStartX(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);
        expandShapeParams(1);
        shapeParams[0].x = v;
    }

    void setLineStartY(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);
        expandShapeParams(1);
        shapeParams[0].y = v;
    }

    void setLineEndX(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);
        expandShapeParams(2);
        shapeParams[1].x = v;
    }

    void setLineEndY(DrawCoord::value_type v)
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::line);
        expandShapeParams(2);
        shapeParams[1].y = v;
    }

public:

    // https://www.w3.org/TR/SVGTiny12/shapes.html

    // polyline
    // points = "<points-data>" The points that make up the polyline. All coordinate values are in the user coordinate system.
    //                          An empty attribute value (points="") disables rendering of the element. The lacuna value is the empty string.
    // points="50,375
    //         150,375 150,325 250,325 250,375
    //         350,375 350,250 450,250 450,375
    //         550,375 550,175 650,175 650,375
    //         750,375 750,100 850,100 850,375
    //         950,375 950,25 1050,25 1050,375
    //         1150,375"

    bool isPolylineValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polyline);

        if (shapeParams.size()<2)
        {
            return false;
        }

        return true;
    }

    const std::vector<DrawCoord>& getPolylinePoints() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polyline);
        return shapeParams;
    }

protected:

    void addPolylinePoint( const DrawCoord &c )
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polyline);
        shapeParams.emplace_back(c);
    }

    void setPolylinePoints( const std::vector<DrawCoord> &v )
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polyline);
        shapeParams = v;
    }

public:


    // https://www.w3.org/TR/SVGTiny12/shapes.html

    // polygon
    // Почти как polyline, но замыкается как path
    // points = "<points-data>" The points that make up the polygon. 
    //                          All coordinate values are in the user coordinate system.
    // points="50,375
    //         150,375 150,325 250,325 250,375
    //         350,375 350,250 450,250 450,375
    //         550,375 550,175 650,175 650,375
    //         750,375 750,100 850,100 850,375
    //         950,375 950,25 1050,25 1050,375
    //         1150,375"

    bool isPolygonValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polygon);

        if (shapeParams.size()<2)
        {
            return false;
        }

        return true;
    }

    const std::vector<DrawCoord>& getPolygonPoints() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polygon);
        return shapeParams;
    }

protected:

    void addPolygonPoint( const DrawCoord &c )
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polygon);
        shapeParams.emplace_back(c);
    }

    void setPolygonPoints( const std::vector<DrawCoord> &v )
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::polygon);
        shapeParams = v;
    }


//TODO: !!! text сделаем потом

    // https://www.w3.org/TR/SVGTiny12/text.html#TextElement
    // text
    // x = "<list-of-coordinates>"
    // y = "<list-of-coordinates>"
    // rotate = "<list-of-numbers>"
    // Список в x/y не поддерживается
    // rotate не поддерживается
    // font-family="Verdana"
    // font-size="55" fill="blue"
    // 'font-style' Value: normal|italic|oblique|inherit, oblique - is italic
    // 'font-variant'  Value: normal|small-caps|inherit
    // 'font-weight'   Value: normal|bold|bolder|lighter|100|200|300|400|500|600|700|800|900|inherit
    // Не поддерживаются значения
    // bolder - Specifies the next weight that is assigned to a font that is darker than the inherited one. If there is no such weight, it simply results in the next darker numerical value (and the font remains unchanged), unless the inherited value was "900", in which case the resulting weight is also "900".
    // lighter - Specifies the next weight that is assigned to a font that is lighter than the inherited one. If there is no such weight, it simply results in the next lighter numerical value (and the font remains unchanged), unless the inherited value was "100", in which case the resulting weight is also "100".

    // tspan подтэг не поддерживается

    // textArea font-size="25" font-family="Georgia" x="10" y="10" width="200" height="300">Tomorrow, and tomorrow, and tomorrow; creeps in this petty pace from day to day, until the last syll&#xAD;able of recorded time. And all our yesterdays have lighted fools the way to dusty death.</textArea>
    // x = "<coordinate>" The x-axis coordinate of one corner of the rectangular region into which the text content will be placed. The lacuna value is '0'.
    // y = "<coordinate>" The y-axis coordinate of one corner of the rectangular region into which the text content will be placed. The lacuna value is '0'.
    // width = "auto" | "<coordinate>"  The width of the rectangular region into which the text content will be placed. A value of 'auto' indicates that the width of the rectangular region is infinite. The lacuna value is 'auto'.
    // height = "auto" | "<coordinate>" The height of the rectangular region into which the text content will be placed. A value of 'auto' indicates that the height of the rectangular region is infinite. The lacuna value is 'auto'.

    // tbreak подтэг не поддерживается

    // line-increment
    // text-align
    // display-align

protected:

    static inline const std::string svgNs = "http://www.w3.org/2000/svg";


public:

    static
    std::vector<PathDataEntry> pathDataFromString(const char* pStr, std::size_t* pPosOut = 0)
    {
        std::vector<PathDataEntry> pathEntries;

        std::size_t pos = 0;
        for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS

        do
        {
            std::size_t pos2 = 0;
            pathEntries.emplace_back(PathDataEntry::fromString(pStr, &pos2));
            pStr += pos2;
            pos  += pos2;
            for(; *pStr && (*pStr=='\r' || *pStr=='\n' || *pStr==' ' || *pStr=='\t'); ++pStr, ++pos) {} // skip WS

        } while(*pStr!=0);

        if (pPosOut)
        {
            *pPosOut = pos;
        }
        
        return pathEntries;
    }

    static
    std::vector<PathDataEntry> pathDataFromString(const std::string &str, std::size_t* pPosOut = 0)
    {
        return pathDataFromString(str.c_str(), pPosOut);
    }


    static
    Shape fromPathXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::path;

        // https://www.w3.org/TR/SVGTiny12/paths.html

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else // if ()
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }
                else if (attrName=="d")
                {
                    shape.pathEntries = pathDataFromString(attr.value());
                }
                else
                {
                    //TODO: !!! Need to parse other attrs
                    std::cerr << "  !!! Unknown attr: path:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }
                
            }

        } // for

        return shape;
    }

    static
    Shape fromRectXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::rect;

        // https://www.w3.org/TR/SVGTiny12/shapes.html

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else // if ()
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // x = "<coordinate>"  The x-axis coordinate of the side of the rectangle which has the smaller x-axis coordinate value in the current user coordinate system. The lacuna value is '0'.
                // y = "<coordinate>"  The y-axis coordinate of the side of the rectangle which has the smaller y-axis coordinate value in the current user coordinate system. The lacuna value is '0'.
                // width = "<length>"  The width of the rectangle. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
                // height = "<length>" The height of the rectangle. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
                // rx = "<length>"     For rounded rectangles, the x-axis radius of the ellipse used to round off the corners of the rectangle. A negative value is unsupported. See the notes below about what happens if the attribute is not specified.
                // ry = "<length>"     For rounded rectangles, the y-axis radius of the ellipse used to round off the corners of the rectangle. A negative value is unsupported. See the notes below about what happens if the attribute is not specified.

                else if (attrName=="x")
                {
                    shape.setRectPosX(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="y")
                {
                    shape.setRectPosY(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="width")
                {
                    shape.setRectWidth(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="height")
                {
                    shape.setRectHeight(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="rx")
                {
                    shape.setRectRadiusX(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="ry")
                {
                    shape.setRectRadiusY(DrawCoord::valueFromStringExact(attr.value()));
                }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: rect:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }
                
            }

        } // for

        return shape;
    }
    
    static
    Shape fromCircleXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::circle;

        // https://www.w3.org/TR/SVGTiny12/shapes.html

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // cx = "<coordinate>" The x-axis coordinate of the center of the circle. The lacuna value is '0'.
                // cy = "<coordinate>" The y-axis coordinate of the center of the circle. The lacuna value is '0'.
                // r  = "<length>"     The radius of the circle. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
                else if (attrName=="cx")
                {
                    shape.setCircleCenterX(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="cy")
                {
                    shape.setCircleCenterY(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="r")
                {
                    shape.setCircleRadius(DrawCoord::valueFromStringExact(attr.value()));
                }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: circle:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }

            }

        } // for

        return shape;
    }

    static
    Shape fromEllipseXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::ellipse;

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // https://www.w3.org/TR/SVGTiny12/shapes.html
            
                // ellipse
                // cx = "<coordinate>"  The x-axis coordinate of the center of the ellipse. The lacuna value is '0'.
                // cy = "<coordinate>"  The y-axis coordinate of the center of the ellipse. The lacuna value is '0'.
                // rx = "<length>"      The x-axis radius of the ellipse. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.
                // ry = "<length>"      The y-axis radius of the ellipse. A negative value is unsupported. A value of zero disables rendering of the element. The lacuna value is '0'.

                else if (attrName=="cx")
                {
                    shape.setEllipseCenterX(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="cy")
                {
                    shape.setEllipseCenterY(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="rx")
                {
                    shape.setEllipseWidth(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="ry")
                {
                    shape.setEllipseHeight(DrawCoord::valueFromStringExact(attr.value()));
                }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: ellipse:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }

            }

        } // for

        return shape;
    }

    static
    Shape fromLineXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::line;

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // https://www.w3.org/TR/SVGTiny12/shapes.html
            
                // line
                // x1 = "<coordinate>" The x-axis coordinate of the start of the line. The lacuna value is '0'.
                // y1 = "<coordinate>" The y-axis coordinate of the start of the line. The lacuna value is '0'.
                // x2 = "<coordinate>" The x-axis coordinate of the end of the line. The lacuna value is '0'.
                // y2 = "<coordinate>" The y-axis coordinate of the end of the line. The lacuna value is '0'.
            
                else if (attrName=="x1")
                {
                    shape.setLineStartX(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="y1")
                {
                    shape.setLineStartY(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="x2")
                {
                    shape.setLineEndX(DrawCoord::valueFromStringExact(attr.value()));
                }
                else if (attrName=="y2")
                {
                    shape.setLineEndY(DrawCoord::valueFromStringExact(attr.value()));
                }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: line:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }

            }

        } // for
     
        return shape;
    }
    
    static
    Shape fromPolylineXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::polyline;

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // https://www.w3.org/TR/SVGTiny12/shapes.html
            
                // polyline
                // points = "<points-data>" The points that make up the polyline. All coordinate values are in the user coordinate system.
                //                          An empty attribute value (points="") disables rendering of the element. The lacuna value is the empty string.
                // points="50,375
                //         150,375 150,325 250,325 250,375
                //         350,375 350,250 450,250 450,375
                //         550,375 550,175 650,175 650,375
                //         750,375 750,100 850,100 850,375
                //         950,375 950,25 1050,25 1050,375
                //         1150,375"
            
                // void addPolylinePoint( const DrawCoord &c )

                else if (attrName=="points")
                {
                    shape.setPolylinePoints(parseCoordsVectorString(attr.value(), 0));
                }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: polyline:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }

            }

        } // for

        return shape;
    }
    
    static
    Shape fromPolygonXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::polygon;

        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // https://www.w3.org/TR/SVGTiny12/shapes.html
            
                // polygon
                // Почти как polyline, но замыкается как path
                // points = "<points-data>" The points that make up the polygon. 
                //                          All coordinate values are in the user coordinate system.
                // points="50,375
                //         150,375 150,325 250,325 250,375
                //         350,375 350,250 450,250 450,375
                //         550,375 550,175 650,175 650,375
                //         750,375 750,100 850,100 850,375
                //         950,375 950,25 1050,25 1050,375
                //         1150,375"

                else if (attrName=="points")
                {
                    shape.setPolygonPoints(parseCoordsVectorString(attr.value(), 0));
                }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: polygon:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }

            }

        } // for

        return shape;
    }


public:

    // https://www.w3.org/TR/SVGTiny12/struct.html#GElement

    const std::vector<Shape>& getGroupShapes() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::group);
        return groupShapes;
    }

    bool isGroupValid() const
    {
        MARTY_IDC_ASSERT(shapeType==ShapeType::group);
        return true; //TODO: !!! На самом деле надо более комплексную проверку сделать
    }

protected:

    static
    Shape fromGroupXmlNode(pugi::xml_node groupNode, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        Shape shape;
        shape.shapeType = ShapeType::group;

        pugi::xml_node node = groupNode.first_child();
        for(; node; node=node.next_sibling())
        {
            std::string name;
            std::string ns = parseXmlTagName(nsPrefixNamespaces, node.name(), name);
            if (ns!=svgNs)
            {
                //cerr << "- Not SVG node: " << node.name() << "\n";
            }
            else
            {
                shape.groupShapes.emplace_back(fromXmlNode(node, nsPrefixNamespaces));
                
            } // if

        } // for node


        pugi::xml_attribute attr = node.first_attribute();
        for(; attr; attr=attr.next_attribute())
        {
            std::string attrName;
            std::string attrNs = parseXmlAttrName(nsPrefixNamespaces, attr.name(), attrName);

            if (attrNs!=svgNs)
            {
                //throw std::runtime_error(std::string("marty_draw_context::svg::PathData: unknown"));
                //cerr << "  - Not SVG attr: " << attr.name() << "\n";
            }
            else
            {
                if (attrName=="id")
                {
                    shape.id = attr.value();
                }

                // else if (attrName=="points")
                // {
                //     shape.setPolygonPoints(parseCoordsVectorString(attr.value(), 0));
                // }
                else
                {
                    //TODO: !!! Need to parse other attrs

                    std::cerr << "  !!! Unknown attr: g:" << attrName << ", value: " << attr.value() << "\n" << std::flush;
                }

            }

        } // for attr


        return shape;
    }



    //typedef Shape (Shape::*ShapeParseNodeMethod)(pugi::xml_node, const std::unordered_map< std::string, std::string > &);
    typedef Shape (*ShapeParseNodeMethod)(pugi::xml_node, const std::unordered_map< std::string, std::string > &);


protected:

    static
    std::unordered_map<std::string, ShapeParseNodeMethod> makeShapeParseNodeMethodsMap()
    {
        std::unordered_map<std::string, ShapeParseNodeMethod>  m;

        m["path"    ] = &Shape::fromPathXmlNode     ;
        m["rect"    ] = &Shape::fromRectXmlNode     ;
        m["circle"  ] = &Shape::fromCircleXmlNode   ;
        m["ellipse" ] = &Shape::fromEllipseXmlNode  ;
        m["line"    ] = &Shape::fromLineXmlNode     ;
        m["polyline"] = &Shape::fromPolylineXmlNode ;
        m["polygon" ] = &Shape::fromPolygonXmlNode  ;
        m["g"       ] = &Shape::fromGroupXmlNode    ;

        return m;
    }

    static
    std::unordered_set<std::string> makeShapeParseNodeMethodsSet()
    {
        std::unordered_set<std::string> s;

        const std::unordered_map<std::string, ShapeParseNodeMethod> &m = getShapeParseNodeMethodsMap();

        std::unordered_map<std::string, ShapeParseNodeMethod>::const_iterator mit = m.begin();
        for(; mit!=m.end(); ++mit)
        {
            s.insert(mit->first);
        }

        return s;
    }


public:

    static
    const std::unordered_map<std::string, ShapeParseNodeMethod>& getShapeParseNodeMethodsMap()
    {
        static std::unordered_map<std::string, ShapeParseNodeMethod> m = makeShapeParseNodeMethodsMap();
        return m;
    }

    static
    const std::unordered_set<std::string>& getShapeParseNodeMethodsSet()
    {
        static std::unordered_set<std::string> s = makeShapeParseNodeMethodsSet();
        return s;
    }

    static
    bool isKnownShapeName(const std::string &name)
    {
        const std::unordered_set<std::string>& s = getShapeParseNodeMethodsSet();
        return s.find(name)!=s.end();
    }

    static
    Shape fromXmlNode(pugi::xml_node node, const std::unordered_map< std::string, std::string > &nsPrefixNamespaces)
    {
        std::string name;
        std::string ns = parseXmlTagName(nsPrefixNamespaces, node.name(), name);
        if (ns!=svgNs)
        {
            throw std::runtime_error( std::string("Not an SVG node: ") + node.name() );
        }

        const std::unordered_map<std::string, ShapeParseNodeMethod>& m = getShapeParseNodeMethodsMap();

        std::unordered_map<std::string, ShapeParseNodeMethod>::const_iterator mit = m.find(name);
        if (mit==m.end())
        {
            throw std::runtime_error( std::string("Unknown shape node: ") + name );
        }

        auto pfn = mit->second;

        return (*pfn)(node, nsPrefixNamespaces);

    }


}; // struct Shape

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
using SizeWithDimensions    = marty_draw_context::SizeWithDimensions;
using ViewBox               = marty_draw_context::ViewBox           ;

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct Image
{
    SizeWithDimensions    size   ;
    ViewBox               viewBox;

    std::vector<Shape>    shapes ;

protected:

    static inline const std::string svgNs = "http://www.w3.org/2000/svg";


public:

    static
    Image fromSvgXmlNode(pugi::xml_node svgNode)
    {
        Image img;

        std::unordered_map< std::string, std::string > nsPrefixNamespaces; // "svg" -> http://www.w3.org/2000/svg

        pugi::xml_attribute svgAttr = svgNode.first_attribute();
        for(; svgAttr; svgAttr=svgAttr.next_attribute())
        {
            // xmlns:svg="http://www.w3.org/2000/svg"

            std::string svgAttrFullName = svgAttr.name();
            std::string svgAttrValue    = svgAttr.value();

            std::string name;
            std::string ns = parseXmlAttrName(svgAttrFullName, name);

            //if (attrParts[0]=="xmlns")
            if (ns=="xmlns")
            {
                nsPrefixNamespaces[name] = svgAttrValue;
            }
            else if (ns=="" && name=="xmlns")
            {
                nsPrefixNamespaces[std::string()] = svgAttrValue;
            }
            else if (name=="width")
            {
                img.size.width   = SizeWithDimensions::valueFromString(svgAttr.value() /* , &nextConvertPos */ );
            }
            else if (name=="height")
            {
                img.size.height  = SizeWithDimensions::valueFromString(svgAttr.value() /* , &nextConvertPos */ );
            }
            else if (name=="viewBox")
            {
                img.viewBox = ViewBox::fromString(svgAttr.value() /* , &nextConvertPos */ );
            }
        }



        pugi::xml_node node = svgNode.first_child();
        for(; node; node=node.next_sibling())
        {
            std::string name;
            std::string ns = parseXmlTagName(nsPrefixNamespaces, node.name(), name);
            if (ns!=svgNs)
            {
                //std::cerr << "- Not SVG node: " << node.name() << "\n" << std::flush;
            }
            else
            {
                if (Shape::isKnownShapeName(name))
                {
                    img.shapes.emplace_back(Shape::fromXmlNode(node, nsPrefixNamespaces));
                }
                else
                {
                    std::cerr << "!!! Unknown tag: " << name << "\n" << std::flush;
                }
                
            } // if

        } // for

        return img;
    }


}; // struct Image


} // namespace svg

} // namespace marty_draw_context

