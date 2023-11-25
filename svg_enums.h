#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



namespace marty_draw_context{
namespace svg{

enum class PathSubcommand : std::uint32_t
{
    invalid                           = (std::uint32_t)(-1),
    unknown                           = (std::uint32_t)(-1),
    moveToAbs                         = 0x0000004D /*!< 'M' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataMovetoCommands */,
    moveToRel                         = 0x0000006D /*!< 'm' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataMovetoCommands */,
    closePathZ                        = 0x0000005A /*!< 'Z' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataClosePathCommand */,
    closePath                         = 0x0000007A /*!< 'z' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataClosePathCommand */,
    lineToAbs                         = 0x0000004C /*!< 'L' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands */,
    lineToRel                         = 0x0000006C /*!< 'l' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands */,
    lineToHorAbs                      = 0x00000048 /*!< 'H' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands */,
    lineToHorRel                      = 0x00000068 /*!< 'h' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands */,
    lineToVertAbs                     = 0x00000056 /*!< 'V' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands */,
    lineToVertRel                     = 0x00000076 /*!< 'v' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataLinetoCommands */,
    cubicBezierToAbs                  = 0x00000043 /*!< 'C' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataCubicBezierCommands */,
    cubicBezierToRel                  = 0x00000063 /*!< 'c' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataCubicBezierCommands */,
    cubicBezierReflectedCpToAbs       = 0x00000053 /*!< 'S' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataCubicBezierCommands */,
    cubicBezierReflectedCpToRel       = 0x00000073 /*!< 's' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataCubicBezierCommands */,
    quadraticBezierToAbs              = 0x00000051 /*!< 'Q' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataQuadraticBezierCommands */,
    quadraticBezierToRel              = 0x00000071 /*!< 'q' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataQuadraticBezierCommands */,
    quadraticBezierReflectedCpToAbs   = 0x00000054 /*!< 'T' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataQuadraticBezierCommands */,
    quadraticBezierReflectedCpToRel   = 0x00000074 /*!< 't' - https://www.w3.org/TR/SVGTiny12/paths.html#PathDataQuadraticBezierCommands */

}; // enum class PathSubcommand : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( PathSubcommand, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToAbs      , "CubicBezierReflectedCpToAbs"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::invalid                          , "Invalid"                         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::lineToVertAbs                    , "LineToVertAbs"                   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::moveToAbs                        , "MoveToAbs"                       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::closePath                        , "ClosePath"                       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::lineToVertRel                    , "LineToVertRel"                   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::moveToRel                        , "MoveToRel"                       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::closePathZ                       , "ClosePathZ"                      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::lineToAbs                        , "LineToAbs"                       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::lineToRel                        , "LineToRel"                       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::lineToHorAbs                     , "LineToHorAbs"                    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::lineToHorRel                     , "LineToHorRel"                    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::cubicBezierToAbs                 , "CubicBezierToAbs"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::cubicBezierToRel                 , "CubicBezierToRel"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToRel      , "CubicBezierReflectedCpToRel"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::quadraticBezierToAbs             , "QuadraticBezierToAbs"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::quadraticBezierToRel             , "QuadraticBezierToRel"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToAbs  , "QuadraticBezierReflectedCpToAbs" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToRel  , "QuadraticBezierReflectedCpToRel" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( PathSubcommand, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( PathSubcommand, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToAbs      , "cubic-bezier-reflected-cp-to-abs"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToAbs      , "cubic_bezier_reflected_cp_to_abs"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToAbs      , "cubicbezierreflectedcptoabs"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::invalid                          , "invalid"                              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::invalid                          , "unknown"                              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToVertAbs                    , "line-to-vert-abs"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToVertAbs                    , "line_to_vert_abs"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToVertAbs                    , "linetovertabs"                        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::moveToAbs                        , "move-to-abs"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::moveToAbs                        , "move_to_abs"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::moveToAbs                        , "movetoabs"                            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::closePath                        , "close-path"                           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::closePath                        , "close_path"                           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::closePath                        , "closepath"                            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToVertRel                    , "line-to-vert-rel"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToVertRel                    , "line_to_vert_rel"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToVertRel                    , "linetovertrel"                        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::moveToRel                        , "move-to-rel"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::moveToRel                        , "move_to_rel"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::moveToRel                        , "movetorel"                            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::closePathZ                       , "close-path-z"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::closePathZ                       , "close_path_z"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::closePathZ                       , "closepathz"                           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToAbs                        , "line-to-abs"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToAbs                        , "line_to_abs"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToAbs                        , "linetoabs"                            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToRel                        , "line-to-rel"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToRel                        , "line_to_rel"                          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToRel                        , "linetorel"                            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToHorAbs                     , "line-to-hor-abs"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToHorAbs                     , "line_to_hor_abs"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToHorAbs                     , "linetohorabs"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToHorRel                     , "line-to-hor-rel"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToHorRel                     , "line_to_hor_rel"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::lineToHorRel                     , "linetohorrel"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierToAbs                 , "cubic-bezier-to-abs"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierToAbs                 , "cubic_bezier_to_abs"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierToAbs                 , "cubicbeziertoabs"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierToRel                 , "cubic-bezier-to-rel"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierToRel                 , "cubic_bezier_to_rel"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierToRel                 , "cubicbeziertorel"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToRel      , "cubic-bezier-reflected-cp-to-rel"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToRel      , "cubic_bezier_reflected_cp_to_rel"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::cubicBezierReflectedCpToRel      , "cubicbezierreflectedcptorel"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierToAbs             , "quadratic-bezier-to-abs"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierToAbs             , "quadratic_bezier_to_abs"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierToAbs             , "quadraticbeziertoabs"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierToRel             , "quadratic-bezier-to-rel"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierToRel             , "quadratic_bezier_to_rel"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierToRel             , "quadraticbeziertorel"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToAbs  , "quadratic-bezier-reflected-cp-to-abs" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToAbs  , "quadratic_bezier_reflected_cp_to_abs" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToAbs  , "quadraticbezierreflectedcptoabs"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToRel  , "quadratic-bezier-reflected-cp-to-rel" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToRel  , "quadratic_bezier_reflected_cp_to_rel" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PathSubcommand::quadraticBezierReflectedCpToRel  , "quadraticbezierreflectedcptorel"      );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( PathSubcommand, std::map, 1 )


enum class ShapeType : std::uint32_t
{
    invalid    = (std::uint32_t)(-1),
    unknown    = (std::uint32_t)(-1),
    group      = 0x00000000 /*!< https://www.w3.org/TR/SVGTiny12/struct.html#Groups */,
    path       = 0x00000001 /*!< https=//www.w3.org/TR/SVGTiny12/paths.html */,
    rect       = 0x00000002 /*!< https=//www.w3.org/TR/SVGTiny12/shapes.html */,
    circle     = 0x00000003 /*!< https=//www.w3.org/TR/SVGTiny12/shapes.html */,
    ellipse    = 0x00000004 /*!< https=//www.w3.org/TR/SVGTiny12/shapes.html */,
    line       = 0x00000005 /*!< https=//www.w3.org/TR/SVGTiny12/shapes.html */,
    polyline   = 0x00000006 /*!< https=//www.w3.org/TR/SVGTiny12/shapes.html */,
    polygon    = 0x00000007 /*!< https=//www.w3.org/TR/SVGTiny12/shapes.html */,
    text       = 0x00000008 /*!< https=//www.w3.org/TR/SVGTiny12/text.html#TextElement */,
    textArea   = 0x00000009 /*!< https=//www.w3.org/TR/SVGTiny12/text.html#TextAreaElement */

}; // enum class ShapeType : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( ShapeType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::invalid    , "Invalid"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::group      , "Group"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::path       , "Path"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::rect       , "Rect"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::line       , "Line"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::ellipse    , "Ellipse"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::circle     , "Circle"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::polyline   , "Polyline" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::polygon    , "Polygon"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::text       , "Text"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ShapeType::textArea   , "TextArea" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( ShapeType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( ShapeType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::invalid    , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::invalid    , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::group      , "group"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::path       , "path"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::rect       , "rect"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::line       , "line"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::ellipse    , "ellipse"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::circle     , "circle"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::polyline   , "polyline"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::polygon    , "polygon"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::text       , "text"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::textArea   , "text-area" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::textArea   , "text_area" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ShapeType::textArea   , "textarea"  );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( ShapeType, std::map, 1 )


enum class TransformType : std::uint32_t
{
    invalid     = (std::uint32_t)(-1),
    unknown     = (std::uint32_t)(-1),
    matrix      = 0x00000000 /*!< https://www.w3.org/TR/SVGTiny12/coords.html#TransformAttribute */,
    translate   = 0x00000001 /*!< https=//www.w3.org/TR/SVGTiny12/coords.html#TransformAttribute */,
    scale       = 0x00000002 /*!< https=//www.w3.org/TR/SVGTiny12/coords.html#TransformAttribute */,
    rotate      = 0x00000003 /*!< https=//www.w3.org/TR/SVGTiny12/coords.html#TransformAttribute */,
    skewX       = 0x00000004 /*!< https=//www.w3.org/TR/SVGTiny12/coords.html#TransformAttribute */,
    skewY       = 0x00000005 /*!< https=//www.w3.org/TR/SVGTiny12/coords.html#TransformAttribute */

}; // enum class TransformType : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( TransformType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::invalid     , "Invalid"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::matrix      , "Matrix"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::skewX       , "SkewX"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::translate   , "Translate" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::scale       , "Scale"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::skewY       , "SkewY"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( TransformType::rotate      , "Rotate"    );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( TransformType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( TransformType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::invalid     , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::invalid     , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::matrix      , "matrix"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::skewX       , "skew-x"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::skewX       , "skew_x"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::skewX       , "skewx"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::translate   , "translate" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::scale       , "scale"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::skewY       , "skew-y"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::skewY       , "skew_y"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::skewY       , "skewy"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( TransformType::rotate      , "rotate"    );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( TransformType, std::map, 1 )

} // namespace svg
} // namespace marty_draw_context

