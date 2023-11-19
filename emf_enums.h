#pragma once

#include "marty_cpp/marty_enum.h"
#include "marty_cpp/marty_flag_ops.h"
#include "marty_cpp/marty_flags.h"

#include <exception>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>



namespace marty_draw_context{
namespace emf{

enum class RecordType : std::uint32_t
{
    header                    = 0x00000001 /*!< EMR_HEADER                  - http://msdn.microsoft.com/en-us/library/cc230635(v=PROT.10).aspx */,
    polybezier                = 0x00000002 /*!< EMR_POLYBEZIER              - http://msdn.microsoft.com/en-us/library/cc230649(v=PROT.10).aspx */,
    polygon                   = 0x00000003 /*!< EMR_POLYGON                 - http://msdn.microsoft.com/en-us/library/cc230653(v=PROT.10).aspx */,
    polyline                  = 0x00000004 /*!< EMR_POLYLINE                - http://msdn.microsoft.com/en-us/library/cc230655(v=PROT.10).aspx */,
    polybezierTo              = 0x00000005 /*!< EMR_POLYBEZIERTO            - http://msdn.microsoft.com/en-us/library/cc230651(v=PROT.10).aspx */,
    polylineTo                = 0x00000006 /*!< EMR_POLYLINETO              - */,
    polyPolyline              = 0x00000007 /*!< EMR_POLYPOLYLINE            - */,
    polyPolygon               = 0x00000008 /*!< EMR_POLYPOLYGON             - http://msdn.microsoft.com/en-us/library/cc230663(v=PROT.10).aspx */,
    setWindowextEx            = 0x00000009 /*!< EMR_SETWINDOWEXTEX          - http://msdn.microsoft.com/en-us/library/cc230597(v=PROT.10).aspx */,
    setWindoworgEx            = 0x0000000A /*!< EMR_SETWINDOWORGEX          - http://msdn.microsoft.com/en-us/library/cc230598(v=PROT.10).aspx */,
    setViewportextEx          = 0x0000000B /*!< EMR_SETVIEWPORTEXTEX        - http://msdn.microsoft.com/en-us/library/cc230595(v=PROT.10).aspx */,
    setViewportorgEx          = 0x0000000C /*!< EMR_SETVIEWPORTORGEX        - http://msdn.microsoft.com/en-us/library/cc230596(v=PROT.10).aspx */,
    setBrushorgEx             = 0x0000000D /*!< EMR_SETBRUSHORGEX           - http://msdn.microsoft.com/en-us/library/cc230682(v=PROT.10).aspx */,
    eof                       = 0x0000000E /*!< EMR_EOF                     - http://msdn.microsoft.com/en-us/library/cc230617(v=PROT.10).aspx */,
    setPixelV                 = 0x0000000F /*!< EMR_SETPIXELV               - http://msdn.microsoft.com/en-us/library/cc230586(v=PROT.10).aspx */,
    setMapperFlags            = 0x00000010 /*!< EMR_SETMAPPERFLAGS          - http://msdn.microsoft.com/en-us/library/cc230692(v=PROT.10).aspx */,
    setMapMode                = 0x00000011 /*!< EMR_SETMAPMODE              - http://msdn.microsoft.com/en-us/library/cc230691(v=PROT.10).aspx */,
    setBkMode                 = 0x00000012 /*!< EMR_SETBKMODE               - http://msdn.microsoft.com/en-us/library/cc230681(v=PROT.10).aspx */,
    setPolyfillMode           = 0x00000013 /*!< EMR_SETPOLYFILLMODE         - http://msdn.microsoft.com/en-us/library/cc230587(v=PROT.10).aspx */,
    setRop2                   = 0x00000014 /*!< EMR_SETROP2                 - http://msdn.microsoft.com/en-us/library/cc230588(v=PROT.10).aspx */,
    setStretchbltMode         = 0x00000015 /*!< EMR_SETSTRETCHBLTMODE       - http://msdn.microsoft.com/en-us/library/cc230589(v=PROT.10).aspx */,
    setTextAlign              = 0x00000016 /*!< EMR_SETTEXTALIGN            - http://msdn.microsoft.com/en-us/library/cc230590(v=PROT.10).aspx */,
    setColorAdjustment        = 0x00000017 /*!< EMR_SETCOLORADJUSTMENT      - http://msdn.microsoft.com/en-us/library/cc230683(v=PROT.10).aspx */,
    setTextColor              = 0x00000018 /*!< EMR_SETTEXTCOLOR            - http://msdn.microsoft.com/en-us/library/cc230591(v=PROT.10).aspx */,
    setBkColor                = 0x00000019 /*!< EMR_SETBKCOLOR              - http://msdn.microsoft.com/en-us/library/cc230680(v=PROT.10).aspx */,
    offsetCliprgn             = 0x0000001A /*!< EMR_OFFSETCLIPRGN           - http://msdn.microsoft.com/en-us/library/cc230644(v=PROT.10).aspx */,
    moveToEx                  = 0x0000001B /*!< EMR_MOVETOEX                - http://msdn.microsoft.com/en-us/library/cc230641(v=PROT.10).aspx */,
    setMetargn                = 0x0000001C /*!< EMR_SETMETARGN              - */,
    excludeClipRect           = 0x0000001D /*!< EMR_EXCLUDECLIPRECT         - http://msdn.microsoft.com/en-us/library/cc230618(v=PROT.10).aspx */,
    intersectClipRect         = 0x0000001E /*!< EMR_INTERSECTCLIPRECT       - http://msdn.microsoft.com/en-us/library/cc230636(v=PROT.10).aspx */,
    scaleViewportExtEx        = 0x0000001F /*!< EMR_SCALEVIEWPORTEXTEX      - http://msdn.microsoft.com/en-us/library/cc230674(v=PROT.10).aspx */,
    scaleWindowExtEx          = 0x00000020 /*!< EMR_SCALEWINDOWEXTEX        - http://msdn.microsoft.com/en-us/library/cc230675(v=PROT.10).aspx */,
    saveDc                    = 0x00000021 /*!< EMR_SAVEDC                  - */,
    restoreDc                 = 0x00000022 /*!< EMR_RESTOREDC               - http://msdn.microsoft.com/en-us/library/cc230671(v=PROT.10).aspx */,
    setWorldTransform         = 0x00000023 /*!< EMR_SETWORLDTRANSFORM       - */,
    modifyWorldTransform      = 0x00000024 /*!< EMR_MODIFYWORLDTRANSFORM    - */,
    selectObject              = 0x00000025 /*!< EMR_SELECTOBJECT            - http://msdn.microsoft.com/en-us/library/cc230677(v=PROT.10).aspx */,
    createPen                 = 0x00000026 /*!< EMR_CREATEPEN               - */,
    createBrushIndirect       = 0x00000027 /*!< EMR_CREATEBRUSHINDIRECT     - http://msdn.microsoft.com/en-us/library/cc230604(v=PROT.10).aspx */,
    deleteObject              = 0x00000028 /*!< EMR_DELETEOBJECT            - http://msdn.microsoft.com/en-us/library/cc230614(v=PROT.10).aspx */,
    angleArc                  = 0x00000029 /*!< EMR_ANGLEARC                - http://msdn.microsoft.com/en-us/library/cc230623(v=PROT.10).aspx */,
    ellipse                   = 0x0000002A /*!< EMR_ELLIPSE                 - http://msdn.microsoft.com/en-us/library/cc230616(v=PROT.10).aspx */,
    rectangle                 = 0x0000002B /*!< EMR_RECTANGLE               - http://msdn.microsoft.com/en-us/library/cc230669(v=PROT.10).aspx */,
    roundRect                 = 0x0000002C /*!< EMR_ROUNDRECT               - http://msdn.microsoft.com/en-us/library/cc230672(v=PROT.10).aspx */,
    arc                       = 0x0000002D /*!< EMR_ARC                     - http://msdn.microsoft.com/en-us/library/cc230632(v=PROT.10).aspx */,
    chord                     = 0x0000002E /*!< EMR_CHORD                   - http://msdn.microsoft.com/en-us/library/cc230673(v=PROT.10).aspx */,
    pie                       = 0x0000002F /*!< EMR_PIE                     - http://msdn.microsoft.com/en-us/library/cc230646(v=PROT.10).aspx */,
    selectPalette             = 0x00000030 /*!< EMR_SELECTPALETTE           - http://msdn.microsoft.com/en-us/library/cc230678(v=PROT.10).aspx */,
    createAlette              = 0x00000031 /*!< EMR_CREATEPALETTE           - http://msdn.microsoft.com/en-us/library/cc230610(v=PROT.10).aspx */,
    setPaletteEntries         = 0x00000032 /*!< EMR_SETPALETTEENTRIES       - http://msdn.microsoft.com/en-us/library/cc230585(v=PROT.10).aspx */,
    resizePalette             = 0x00000033 /*!< EMR_RESIZEPALETTE           - http://msdn.microsoft.com/en-us/library/cc230670(v=PROT.10).aspx */,
    realizePalette            = 0x00000034 /*!< EMR_REALIZEPALETTE          - */,
    extFloodFill              = 0x00000035 /*!< EMR_EXTFLOODFILL            - http://msdn.microsoft.com/en-us/library/cc230622(v=PROT.10).aspx */,
    lineTo                    = 0x00000036 /*!< EMR_LINETO                  - http://msdn.microsoft.com/en-us/library/cc230638(v=PROT.10).aspx */,
    arcTo                     = 0x00000037 /*!< EMR_ARCTO                   - http://msdn.microsoft.com/en-us/library/cc230643(v=PROT.10).aspx */,
    polyDraw                  = 0x00000038 /*!< EMR_POLYDRAW                - */,
    setArcDirection           = 0x00000039 /*!< EMR_SETARCDIRECTION         - http://msdn.microsoft.com/en-us/library/cc230679(v=PROT.10).aspx */,
    setMiterLimit             = 0x0000003A /*!< EMR_SETMITERLIMIT           - http://msdn.microsoft.com/en-us/library/cc230584(v=PROT.10).aspx */,
    beginPath                 = 0x0000003B /*!< EMR_BEGINPATH               - */,
    endPath                   = 0x0000003C /*!< EMR_ENDPATH                 - */,
    closeFigure               = 0x0000003D /*!< EMR_CLOSEFIGURE             - */,
    fillPath                  = 0x0000003E /*!< EMR_FILLPATH                - */,
    strokeAndFillPath         = 0x0000003F /*!< EMR_STROKEANDFILLPATH       - */,
    strokePath                = 0x00000040 /*!< EMR_STROKEPATH              - http://msdn.microsoft.com/en-us/library/cc230603(v=PROT.10).aspx */,
    flattenPath               = 0x00000041 /*!< EMR_FLATTENPATH             - */,
    widenPath                 = 0x00000042 /*!< EMR_WIDENPATH               - */,
    selectClipPath            = 0x00000043 /*!< EMR_SELECTCLIPPATH          - */,
    abortPath                 = 0x00000044 /*!< EMR_ABORTPATH               - */,
    comment                   = 0x00000046 /*!< EMR_COMMENT                 - http://msdn.microsoft.com/en-us/library/cc231170(v=PROT.10).aspx */,
    fillRgn                   = 0x00000047 /*!< EMR_FILLRGN                 - http://msdn.microsoft.com/en-us/library/cc230628(v=PROT.10).aspx */,
    frameRgn                  = 0x00000048 /*!< EMR_FRAMERGN                - */,
    invertRgn                 = 0x00000049 /*!< EMR_INVERTRGN               - http://msdn.microsoft.com/en-us/library/cc230637(v=PROT.10).aspx */,
    paintRgn                  = 0x0000004A /*!< EMR_PAINTRGN                - http://msdn.microsoft.com/en-us/library/cc230645(v=PROT.10).aspx */,
    extSelectClipRgn          = 0x0000004B /*!< EMR_EXTSELECTCLIPRGN        - http://msdn.microsoft.com/en-us/library/cc230624(v=PROT.10).aspx */,
    bitBlt                    = 0x0000004C /*!< EMR_BITBLT                  - http://msdn.microsoft.com/en-us/library/cc230664(v=PROT.10).aspx */,
    stretchBlt                = 0x0000004D /*!< EMR_STRETCHBLT              - http://msdn.microsoft.com/en-us/library/cc230600(v=PROT.10).aspx */,
    maskBlt                   = 0x0000004E /*!< EMR_MASKBLT                 - */,
    plgBlt                    = 0x0000004F /*!< EMR_PLGBLT                  - */,
    setDiBitsToDevice         = 0x00000050 /*!< EMR_SETDIBITSTODEVICE       - http://msdn.microsoft.com/en-us/library/cc230685(v=PROT.10).aspx */,
    stretchDiBits             = 0x00000051 /*!< EMR_STRETCHDIBITS           - http://msdn.microsoft.com/en-us/library/cc230601(v=PROT.10).aspx */,
    extCreateFontIndirectW    = 0x00000052 /*!< EMR_EXTCREATEFONTINDIRECTW  - http://msdn.microsoft.com/en-us/library/cc230619(v=PROT.10).aspx */,
    extTextOutA               = 0x00000053 /*!< EMR_EXTTEXTOUTA             - */,
    extTextOutW               = 0x00000054 /*!< EMR_EXTTEXTOUTW             - */,
    polybezier16              = 0x00000055 /*!< EMR_POLYBEZIER16            - http://msdn.microsoft.com/en-us/library/cc230650(v=PROT.10).aspx */,
    polygon16                 = 0x00000056 /*!< EMR_POLYGON16               - http://msdn.microsoft.com/en-us/library/cc230654(v=PROT.10).aspx */,
    polyline16                = 0x00000057 /*!< EMR_POLYLINE16              - http://msdn.microsoft.com/en-us/library/cc230656(v=PROT.10).aspx */,
    polybezierTo16            = 0x00000058 /*!< EMR_POLYBEZIERTO16          - http://msdn.microsoft.com/en-us/library/cc230652(v=PROT.10).aspx */,
    polylineTo16              = 0x00000059 /*!< EMR_POLYLINETO16            - */,
    polyPolyline16            = 0x0000005A /*!< EMR_POLYPOLYLINE16          - */,
    polyPolygon16             = 0x0000005B /*!< EMR_POLYPOLYGON16           - http://msdn.microsoft.com/en-us/library/cc230665(v=PROT.10).aspx */,
    polyDraw16                = 0x0000005C /*!< EMR_POLYDRAW16              - */,
    createMonoBrush           = 0x0000005D /*!< EMR_CREATEMONOBRUSH         - */,
    createDibPatternBrushPt   = 0x0000005E /*!< EMR_CREATEDIBPATTERNBRUSHPT - */,
    extCreatePen              = 0x0000005F /*!< EMR_EXTCREATEPEN            - http://msdn.microsoft.com/en-us/library/cc230620(v=PROT.10).aspx */,
    polyTextOutA              = 0x00000060 /*!< EMR_POLYTEXTOUTA            - */,
    polyTextOutW              = 0x00000061 /*!< EMR_POLYTEXTOUTW            - */,
    setIcmMode                = 0x00000062 /*!< EMR_SETICMMODE              - http://msdn.microsoft.com/en-us/library/cc230686(v=PROT.10).aspx */,
    createColorSpace          = 0x00000063 /*!< EMR_CREATECOLORSPACE        - http://msdn.microsoft.com/en-us/library/cc230606(v=PROT.10).aspx */,
    setColorSpace             = 0x00000064 /*!< EMR_SETCOLORSPACE           - http://msdn.microsoft.com/en-us/library/cc230684(v=PROT.10).aspx */,
    deleteColorSpace          = 0x00000065 /*!< EMR_DELETECOLORSPACE        - http://msdn.microsoft.com/en-us/library/cc230612(v=PROT.10).aspx */,
    glsRecord                 = 0x00000066 /*!< EMR_GLSRECORD               - http://msdn.microsoft.com/en-us/library/cc230631(v=PROT.10).aspx */,
    glsBoundedRecord          = 0x00000067 /*!< EMR_GLSBOUNDEDRECORD        - http://msdn.microsoft.com/en-us/library/cc230633(v=PROT.10).aspx */,
    pixelFormat               = 0x00000068 /*!< EMR_PIXELFORMAT             - http://msdn.microsoft.com/en-us/library/cc230647(v=PROT.10).aspx */,
    draweScape                = 0x00000069 /*!< EMR_DRAWESCAPE              - */,
    extEscape                 = 0x0000006A /*!< EMR_EXTESCAPE               - */,
    smallTextOut              = 0x0000006C /*!< EMR_SMALLTEXTOUT            - */,
    forceUfiMapping           = 0x0000006D /*!< EMR_FORCEUFIMAPPING         - http://msdn.microsoft.com/en-us/library/cc230629(v=PROT.10).aspx */,
    namedEscape               = 0x0000006E /*!< EMR_NAMEDESCAPE             - */,
    colorCorrectPalette       = 0x0000006F /*!< EMR_COLORCORRECTPALETTE     - http://msdn.microsoft.com/en-us/library/cc230583(v=PROT.10).aspx */,
    setIcmProfileA            = 0x00000070 /*!< EMR_SETICMPROFILEA          - http://msdn.microsoft.com/en-us/library/cc230687(v=PROT.10).aspx */,
    setIcmProfileW            = 0x00000071 /*!< EMR_SETICMPROFILEW          - http://msdn.microsoft.com/en-us/library/cc230688(v=PROT.10).aspx */,
    alphablend                = 0x00000072 /*!< EMR_ALPHABLEND              - */,
    setLayout                 = 0x00000073 /*!< EMR_SETLAYOUT               - http://msdn.microsoft.com/en-us/library/cc230689(v=PROT.10).aspx */,
    transparentBlt            = 0x00000074 /*!< EMR_TRANSPARENTBLT          - */,
    gradientFill              = 0x00000076 /*!< EMR_GRADIENTFILL            - http://msdn.microsoft.com/en-us/library/cc230634(v=PROT.10).aspx */,
    setLinkedUfis             = 0x00000077 /*!< EMR_SETLINKEDUFIS           - http://msdn.microsoft.com/en-us/library/cc230690(v=PROT.10).aspx */,
    setTextJustification      = 0x00000078 /*!< EMR_SETTEXTJUSTIFICATION    - http://msdn.microsoft.com/en-us/library/cc230592(v=PROT.10).aspx */,
    colorMatchToTargetW       = 0x00000079 /*!< EMR_COLORMATCHTOTARGETW     - */,
    createColorSpaceW         = 0x0000007A /*!< EMR_CREATECOLORSPACEW       - */

}; // enum class RecordType : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( RecordType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::header                    , "Header"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polylineTo                , "PolylineTo"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polybezier                , "Polybezier"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyTextOutW              , "PolyTextOutW"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::excludeClipRect           , "ExcludeClipRect"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setColorAdjustment        , "SetColorAdjustment"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polygon                   , "Polygon"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::roundRect                 , "RoundRect"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polybezierTo              , "PolybezierTo"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::beginPath                 , "BeginPath"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyline                  , "Polyline"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyPolygon               , "PolyPolygon"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::fillRgn                   , "FillRgn"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::scaleViewportExtEx        , "ScaleViewportExtEx"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyPolyline              , "PolyPolyline"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setWindowextEx            , "SetWindowextEx"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setWindoworgEx            , "SetWindoworgEx"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setLinkedUfis             , "SetLinkedUfis"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::scaleWindowExtEx          , "ScaleWindowExtEx"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::smallTextOut              , "SmallTextOut"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setViewportextEx          , "SetViewportextEx"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setViewportorgEx          , "SetViewportorgEx"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setBrushorgEx             , "SetBrushorgEx"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::deleteObject              , "DeleteObject"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::eof                       , "Eof"                     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::pie                       , "Pie"                     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::stretchDiBits             , "StretchDiBits"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::chord                     , "Chord"                   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setMetargn                , "SetMetargn"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setPixelV                 , "SetPixelV"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setMapperFlags            , "SetMapperFlags"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setMapMode                , "SetMapMode"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::arc                       , "Arc"                     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::offsetCliprgn             , "OffsetCliprgn"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setBkMode                 , "SetBkMode"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setPolyfillMode           , "SetPolyfillMode"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setRop2                   , "SetRop2"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setIcmMode                , "SetIcmMode"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyDraw                  , "PolyDraw"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setStretchbltMode         , "SetStretchbltMode"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extFloodFill              , "ExtFloodFill"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setTextAlign              , "SetTextAlign"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setTextColor              , "SetTextColor"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::fillPath                  , "FillPath"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setBkColor                , "SetBkColor"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::realizePalette            , "RealizePalette"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::moveToEx                  , "MoveToEx"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::rectangle                 , "Rectangle"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::intersectClipRect         , "IntersectClipRect"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::saveDc                    , "SaveDc"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::restoreDc                 , "RestoreDc"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setWorldTransform         , "SetWorldTransform"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setMiterLimit             , "SetMiterLimit"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::modifyWorldTransform      , "ModifyWorldTransform"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::selectObject              , "SelectObject"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createPen                 , "CreatePen"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::selectPalette             , "SelectPalette"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extSelectClipRgn          , "ExtSelectClipRgn"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createBrushIndirect       , "CreateBrushIndirect"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::angleArc                  , "AngleArc"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::ellipse                   , "Ellipse"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::arcTo                     , "ArcTo"                   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createAlette              , "Create{Alette"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::flattenPath               , "FlattenPath"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::lineTo                    , "LineTo"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setPaletteEntries         , "SetPaletteEntries"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setColorSpace             , "SetColorSpace"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::resizePalette             , "ResizePalette"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setArcDirection           , "SetArcDirection"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::endPath                   , "EndPath"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::closeFigure               , "CloseFigure"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::strokeAndFillPath         , "StrokeAndFillPath"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::strokePath                , "StrokePath"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::widenPath                 , "WidenPath"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::selectClipPath            , "SelectClipPath"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::abortPath                 , "AbortPath"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::comment                   , "Comment"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::frameRgn                  , "FrameRgn"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::invertRgn                 , "InvertRgn"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::paintRgn                  , "PaintRgn"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::bitBlt                    , "BitBlt"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::stretchBlt                , "StretchBlt"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setLayout                 , "SetLayout"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::maskBlt                   , "MaskBlt"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::plgBlt                    , "PlgBlt"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setDiBitsToDevice         , "SetDiBitsToDevice"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extCreateFontIndirectW    , "ExtCreateFontIndirectW"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extTextOutA               , "ExtTextOutA"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polybezierTo16            , "PolybezierTo16"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extTextOutW               , "ExtTextOutW"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polybezier16              , "Polybezier16"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polygon16                 , "Polygon16"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyline16                , "Polyline16"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polylineTo16              , "PolylineTo16"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyPolyline16            , "PolyPolyline16"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyPolygon16             , "PolyPolygon16"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyDraw16                , "PolyDraw16"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createMonoBrush           , "CreateMonoBrush"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::alphablend                , "Alphablend"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createDibPatternBrushPt   , "CreateDibPatternBrushPt" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extCreatePen              , "ExtCreatePen"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::polyTextOutA              , "PolyTextOutA"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createColorSpace          , "CreateColorSpace"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::deleteColorSpace          , "DeleteColorSpace"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::glsRecord                 , "GlsRecord"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::glsBoundedRecord          , "GlsBoundedRecord"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::pixelFormat               , "PixelFormat"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::draweScape                , "DraweScape"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::extEscape                 , "ExtEscape"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::forceUfiMapping           , "ForceUfiMapping"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::namedEscape               , "NamedEscape"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::colorCorrectPalette       , "ColorCorrectPalette"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setIcmProfileA            , "SetIcmProfileA"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setIcmProfileW            , "SetIcmProfileW"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::transparentBlt            , "TransparentBlt"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::gradientFill              , "GradientFill"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::setTextJustification      , "SetTextJustification"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::colorMatchToTargetW       , "ColorMatchToTargetW"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( RecordType::createColorSpaceW         , "CreateColorSpaceW"       );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( RecordType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( RecordType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::header                    , "header"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polylineTo                , "polyline-to"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polylineTo                , "polyline_to"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polylineTo                , "polylineto"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezier                , "polybezier"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyTextOutW              , "poly-text-out-w"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyTextOutW              , "poly_text_out_w"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyTextOutW              , "polytextoutw"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::excludeClipRect           , "exclude-clip-rect"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::excludeClipRect           , "exclude_clip_rect"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::excludeClipRect           , "excludecliprect"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setColorAdjustment        , "set-color-adjustment"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setColorAdjustment        , "set_color_adjustment"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setColorAdjustment        , "setcoloradjustment"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polygon                   , "polygon"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::roundRect                 , "round-rect"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::roundRect                 , "round_rect"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::roundRect                 , "roundrect"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezierTo              , "polybezier-to"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezierTo              , "polybezier_to"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezierTo              , "polybezierto"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::beginPath                 , "begin-path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::beginPath                 , "begin_path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::beginPath                 , "beginpath"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyline                  , "polyline"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolygon               , "poly-polygon"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolygon               , "poly_polygon"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolygon               , "polypolygon"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::fillRgn                   , "fill-rgn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::fillRgn                   , "fill_rgn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::fillRgn                   , "fillrgn"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::scaleViewportExtEx        , "scale-viewport-ext-ex"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::scaleViewportExtEx        , "scale_viewport_ext_ex"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::scaleViewportExtEx        , "scaleviewportextex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolyline              , "poly-polyline"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolyline              , "poly_polyline"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolyline              , "polypolyline"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWindowextEx            , "set-windowext-ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWindowextEx            , "set_windowext_ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWindowextEx            , "setwindowextex"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWindoworgEx            , "set-windoworg-ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWindoworgEx            , "set_windoworg_ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWindoworgEx            , "setwindoworgex"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setLinkedUfis             , "set-linked-ufis"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setLinkedUfis             , "set_linked_ufis"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setLinkedUfis             , "setlinkedufis"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::scaleWindowExtEx          , "scale-window-ext-ex"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::scaleWindowExtEx          , "scale_window_ext_ex"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::scaleWindowExtEx          , "scalewindowextex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::smallTextOut              , "small-text-out"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::smallTextOut              , "smalltextout"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::smallTextOut              , "small_text_out"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setViewportextEx          , "set-viewportext-ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setViewportextEx          , "set_viewportext_ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setViewportextEx          , "setviewportextex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setViewportorgEx          , "set-viewportorg-ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setViewportorgEx          , "setviewportorgex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setViewportorgEx          , "set_viewportorg_ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBrushorgEx             , "set-brushorg-ex"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBrushorgEx             , "set_brushorg_ex"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBrushorgEx             , "setbrushorgex"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::deleteObject              , "delete-object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::deleteObject              , "delete_object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::deleteObject              , "deleteobject"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::eof                       , "eof"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::pie                       , "pie"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::stretchDiBits             , "stretch-di-bits"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::stretchDiBits             , "stretchdibits"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::stretchDiBits             , "stretch_di_bits"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::chord                     , "chord"                       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMetargn                , "set-metargn"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMetargn                , "set_metargn"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMetargn                , "setmetargn"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPixelV                 , "set-pixel-v"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPixelV                 , "set_pixel_v"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPixelV                 , "setpixelv"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMapperFlags            , "set-mapper-flags"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMapperFlags            , "set_mapper_flags"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMapperFlags            , "setmapperflags"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMapMode                , "set-map-mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMapMode                , "setmapmode"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMapMode                , "set_map_mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::arc                       , "arc"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::offsetCliprgn             , "offset-cliprgn"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::offsetCliprgn             , "offset_cliprgn"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::offsetCliprgn             , "offsetcliprgn"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBkMode                 , "set-bk-mode"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBkMode                 , "set_bk_mode"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBkMode                 , "setbkmode"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPolyfillMode           , "set-polyfill-mode"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPolyfillMode           , "set_polyfill_mode"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPolyfillMode           , "setpolyfillmode"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setRop2                   , "set-rop2"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setRop2                   , "set_rop2"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setRop2                   , "setrop2"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmMode                , "set-icm-mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmMode                , "set_icm_mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmMode                , "seticmmode"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyDraw                  , "poly-draw"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyDraw                  , "poly_draw"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyDraw                  , "polydraw"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setStretchbltMode         , "set-stretchblt-mode"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setStretchbltMode         , "setstretchbltmode"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setStretchbltMode         , "set_stretchblt_mode"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extFloodFill              , "ext-flood-fill"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extFloodFill              , "ext_flood_fill"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extFloodFill              , "extfloodfill"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextAlign              , "set-text-align"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextAlign              , "set_text_align"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextAlign              , "settextalign"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextColor              , "set-text-color"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextColor              , "set_text_color"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextColor              , "settextcolor"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::fillPath                  , "fill-path"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::fillPath                  , "fill_path"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::fillPath                  , "fillpath"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBkColor                , "set-bk-color"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBkColor                , "set_bk_color"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setBkColor                , "setbkcolor"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::realizePalette            , "realize-palette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::realizePalette            , "realize_palette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::realizePalette            , "realizepalette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::moveToEx                  , "move-to-ex"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::moveToEx                  , "move_to_ex"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::moveToEx                  , "movetoex"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::rectangle                 , "rectangle"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::intersectClipRect         , "intersect-clip-rect"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::intersectClipRect         , "intersect_clip_rect"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::intersectClipRect         , "intersectcliprect"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::saveDc                    , "save-dc"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::saveDc                    , "save_dc"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::saveDc                    , "savedc"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::restoreDc                 , "restore-dc"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::restoreDc                 , "restore_dc"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::restoreDc                 , "restoredc"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWorldTransform         , "set-world-transform"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWorldTransform         , "setworldtransform"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setWorldTransform         , "set_world_transform"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMiterLimit             , "set-miter-limit"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMiterLimit             , "set_miter_limit"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setMiterLimit             , "setmiterlimit"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::modifyWorldTransform      , "modify-world-transform"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::modifyWorldTransform      , "modifyworldtransform"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::modifyWorldTransform      , "modify_world_transform"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectObject              , "select-object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectObject              , "select_object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectObject              , "selectobject"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createPen                 , "create-pen"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createPen                 , "create_pen"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createPen                 , "createpen"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectPalette             , "select-palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectPalette             , "select_palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectPalette             , "selectpalette"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extSelectClipRgn          , "ext-select-clip-rgn"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extSelectClipRgn          , "ext_select_clip_rgn"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extSelectClipRgn          , "extselectcliprgn"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createBrushIndirect       , "create-brush-indirect"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createBrushIndirect       , "create_brush_indirect"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createBrushIndirect       , "createbrushindirect"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::angleArc                  , "angle-arc"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::angleArc                  , "angle_arc"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::angleArc                  , "anglearc"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::ellipse                   , "ellipse"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::arcTo                     , "arc-to"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::arcTo                     , "arc_to"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::arcTo                     , "arcto"                       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createAlette              , "create-{-alette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createAlette              , "create_{_alette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createAlette              , "create{alette"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::flattenPath               , "flatten-path"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::flattenPath               , "flatten_path"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::flattenPath               , "flattenpath"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::lineTo                    , "line-to"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::lineTo                    , "line_to"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::lineTo                    , "lineto"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPaletteEntries         , "set-palette-entries"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPaletteEntries         , "set_palette_entries"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setPaletteEntries         , "setpaletteentries"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setColorSpace             , "set-color-space"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setColorSpace             , "set_color_space"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setColorSpace             , "setcolorspace"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::resizePalette             , "resize-palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::resizePalette             , "resize_palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::resizePalette             , "resizepalette"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setArcDirection           , "set-arc-direction"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setArcDirection           , "set_arc_direction"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setArcDirection           , "setarcdirection"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::endPath                   , "end-path"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::endPath                   , "end_path"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::endPath                   , "endpath"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::closeFigure               , "close-figure"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::closeFigure               , "close_figure"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::closeFigure               , "closefigure"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::strokeAndFillPath         , "stroke-and-fill-path"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::strokeAndFillPath         , "stroke_and_fill_path"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::strokeAndFillPath         , "strokeandfillpath"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::strokePath                , "stroke-path"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::strokePath                , "stroke_path"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::strokePath                , "strokepath"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::widenPath                 , "widen-path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::widenPath                 , "widen_path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::widenPath                 , "widenpath"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectClipPath            , "select-clip-path"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectClipPath            , "select_clip_path"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::selectClipPath            , "selectclippath"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::abortPath                 , "abort-path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::abortPath                 , "abort_path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::abortPath                 , "abortpath"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::comment                   , "comment"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::frameRgn                  , "frame-rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::frameRgn                  , "frame_rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::frameRgn                  , "framergn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::invertRgn                 , "invert-rgn"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::invertRgn                 , "invert_rgn"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::invertRgn                 , "invertrgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::paintRgn                  , "paint-rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::paintRgn                  , "paint_rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::paintRgn                  , "paintrgn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::bitBlt                    , "bit-blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::bitBlt                    , "bit_blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::bitBlt                    , "bitblt"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::stretchBlt                , "stretch-blt"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::stretchBlt                , "stretch_blt"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::stretchBlt                , "stretchblt"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setLayout                 , "set-layout"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setLayout                 , "set_layout"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setLayout                 , "setlayout"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::maskBlt                   , "mask-blt"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::maskBlt                   , "mask_blt"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::maskBlt                   , "maskblt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::plgBlt                    , "plg-blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::plgBlt                    , "plg_blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::plgBlt                    , "plgblt"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setDiBitsToDevice         , "set-di-bits-to-device"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setDiBitsToDevice         , "set_di_bits_to_device"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setDiBitsToDevice         , "setdibitstodevice"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extCreateFontIndirectW    , "ext-create-font-indirect-w"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extCreateFontIndirectW    , "ext_create_font_indirect_w"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extCreateFontIndirectW    , "extcreatefontindirectw"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extTextOutA               , "ext-text-out-a"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extTextOutA               , "ext_text_out_a"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extTextOutA               , "exttextouta"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezierTo16            , "polybezier-to16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezierTo16            , "polybezier_to16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezierTo16            , "polybezierto16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extTextOutW               , "ext-text-out-w"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extTextOutW               , "ext_text_out_w"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extTextOutW               , "exttextoutw"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polybezier16              , "polybezier16"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polygon16                 , "polygon16"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyline16                , "polyline16"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polylineTo16              , "polyline-to16"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polylineTo16              , "polyline_to16"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polylineTo16              , "polylineto16"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolyline16            , "poly-polyline16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolyline16            , "poly_polyline16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolyline16            , "polypolyline16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolygon16             , "poly-polygon16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolygon16             , "poly_polygon16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyPolygon16             , "polypolygon16"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyDraw16                , "poly-draw16"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyDraw16                , "poly_draw16"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyDraw16                , "polydraw16"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createMonoBrush           , "create-mono-brush"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createMonoBrush           , "create_mono_brush"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createMonoBrush           , "createmonobrush"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::alphablend                , "alphablend"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createDibPatternBrushPt   , "create-dib-pattern-brush-pt" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createDibPatternBrushPt   , "create_dib_pattern_brush_pt" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createDibPatternBrushPt   , "createdibpatternbrushpt"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extCreatePen              , "ext-create-pen"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extCreatePen              , "ext_create_pen"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extCreatePen              , "extcreatepen"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyTextOutA              , "poly-text-out-a"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyTextOutA              , "poly_text_out_a"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::polyTextOutA              , "polytextouta"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createColorSpace          , "create-color-space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createColorSpace          , "create_color_space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createColorSpace          , "createcolorspace"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::deleteColorSpace          , "delete-color-space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::deleteColorSpace          , "delete_color_space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::deleteColorSpace          , "deletecolorspace"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::glsRecord                 , "gls-record"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::glsRecord                 , "gls_record"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::glsRecord                 , "glsrecord"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::glsBoundedRecord          , "gls-bounded-record"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::glsBoundedRecord          , "gls_bounded_record"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::glsBoundedRecord          , "glsboundedrecord"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::pixelFormat               , "pixel-format"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::pixelFormat               , "pixel_format"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::pixelFormat               , "pixelformat"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::draweScape                , "drawe-scape"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::draweScape                , "drawe_scape"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::draweScape                , "drawescape"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extEscape                 , "ext-escape"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extEscape                 , "ext_escape"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::extEscape                 , "extescape"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::forceUfiMapping           , "force-ufi-mapping"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::forceUfiMapping           , "force_ufi_mapping"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::forceUfiMapping           , "forceufimapping"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::namedEscape               , "named-escape"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::namedEscape               , "named_escape"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::namedEscape               , "namedescape"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::colorCorrectPalette       , "color-correct-palette"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::colorCorrectPalette       , "color_correct_palette"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::colorCorrectPalette       , "colorcorrectpalette"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmProfileA            , "set-icm-profile-a"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmProfileA            , "set_icm_profile_a"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmProfileA            , "seticmprofilea"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmProfileW            , "set-icm-profile-w"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmProfileW            , "set_icm_profile_w"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setIcmProfileW            , "seticmprofilew"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::transparentBlt            , "transparent-blt"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::transparentBlt            , "transparent_blt"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::transparentBlt            , "transparentblt"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::gradientFill              , "gradient-fill"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::gradientFill              , "gradient_fill"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::gradientFill              , "gradientfill"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextJustification      , "set-text-justification"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextJustification      , "set_text_justification"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::setTextJustification      , "settextjustification"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::colorMatchToTargetW       , "color-match-to-target-w"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::colorMatchToTargetW       , "color_match_to_target_w"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::colorMatchToTargetW       , "colormatchtotargetw"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createColorSpaceW         , "create-color-space-w"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createColorSpaceW         , "create_color_space_w"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( RecordType::createColorSpaceW         , "createcolorspacew"           );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( RecordType, std::map, 1 )


enum class FormatSignature : std::uint32_t
{
    invalid   = (std::uint32_t)(-1),
    unknown   = (std::uint32_t)(-1),
    emf       = 0x464D4520,
    eps       = 0x46535045

}; // enum class FormatSignature : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( FormatSignature, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FormatSignature::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FormatSignature::emf       , "Emf"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FormatSignature::eps       , "Eps"     );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( FormatSignature, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( FormatSignature, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FormatSignature::invalid   , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FormatSignature::invalid   , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FormatSignature::emf       , "emf"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FormatSignature::eps       , "eps"     );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( FormatSignature, std::map, 1 )


enum class OpenGlPresenceFlag : std::uint32_t
{
    invalid            = (std::uint32_t)(-1),
    unknown            = (std::uint32_t)(-1),
    openGlNotPresent   = 0x00000000,
    openGlAbsent       = 0x00000000,
    openGlPresent      = 0x00000001

}; // enum class OpenGlPresenceFlag : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( OpenGlPresenceFlag, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( OpenGlPresenceFlag::invalid            , "Invalid"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "OpenGlNotPresent" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( OpenGlPresenceFlag::openGlPresent      , "OpenGlPresent"    );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( OpenGlPresenceFlag, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( OpenGlPresenceFlag, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::invalid            , "invalid"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::invalid            , "unknown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "open-gl-not-present" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "open_gl_absent"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "openglabsent"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "open_gl_not_present" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "openglnotpresent"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlNotPresent   , "open-gl-absent"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlPresent      , "open-gl-present"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlPresent      , "open_gl_present"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( OpenGlPresenceFlag::openGlPresent      , "openglpresent"       );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( OpenGlPresenceFlag, std::map, 1 )


enum class MetafileHeaderOptions : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    basicHeader   = 0x00000000,
    headerExt1    = 0x00000001,
    headerExt2    = 0x00000002

}; // enum class MetafileHeaderOptions : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( MetafileHeaderOptions, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MetafileHeaderOptions::basicHeader   , "BasicHeader" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MetafileHeaderOptions::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MetafileHeaderOptions::headerExt1    , "HeaderExt1"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MetafileHeaderOptions::headerExt2    , "HeaderExt2"  );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( MetafileHeaderOptions, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( MetafileHeaderOptions, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::basicHeader   , "basic-header" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::basicHeader   , "basic_header" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::basicHeader   , "basicheader"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::invalid       , "invalid"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::invalid       , "unknown"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::headerExt1    , "header-ext1"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::headerExt1    , "header_ext1"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::headerExt1    , "headerext1"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::headerExt2    , "header-ext2"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::headerExt2    , "header_ext2"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MetafileHeaderOptions::headerExt2    , "headerext2"   );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( MetafileHeaderOptions, std::map, 1 )


enum class PixelFormatDescriptorFlags : std::uint32_t
{
    invalid                = (std::uint32_t)(-1),
    unknown                = (std::uint32_t)(-1),
    doubleBuffer           = 0x00000001,
    stereo                 = 0x00000002,
    drawToWindow           = 0x00000004,
    drawToBitmap           = 0x00000008,
    supportGdi             = 0x00000010,
    supportOpenGl          = 0x00000020,
    genericFormat          = 0x00000040,
    needPalette            = 0x00000080,
    needSystemPalette      = 0x00000100,
    swapExchange           = 0x00000200,
    swapCopy               = 0x00000400,
    swapLayerBuffers       = 0x00000800,
    genericAccelerated     = 0x00001000,
    supportDirectDraw      = 0x00002000,
    direct3dAccelerated    = 0x00004000,
    supportComposition     = 0x00008000,
    depthDontCare          = 0x20000000,
    doubleBufferDontCare   = 0x40000000,
    stereoDontCare         = 0x80000000

}; // enum class PixelFormatDescriptorFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(PixelFormatDescriptorFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( PixelFormatDescriptorFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::invalid              , "Invalid"              );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToWindow         , "DrawToWindow"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::direct3dAccelerated  , "Direct3dAccelerated"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBuffer         , "DoubleBuffer"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToBitmap         , "DrawToBitmap"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::stereo               , "Stereo"               );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::supportGdi           , "SupportGdi"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::supportOpenGl        , "SupportOpenGl"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::genericFormat        , "GenericFormat"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::needPalette          , "NeedPalette"          );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::needSystemPalette    , "NeedSystemPalette"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::swapExchange         , "SwapExchange"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::swapCopy             , "SwapCopy"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::swapLayerBuffers     , "SwapLayerBuffers"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::genericAccelerated   , "GenericAccelerated"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::supportDirectDraw    , "SupportDirectDraw"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::supportComposition   , "SupportComposition"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::depthDontCare        , "DepthDontCare"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBufferDontCare , "DoubleBufferDontCare" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( PixelFormatDescriptorFlags::stereoDontCare       , "StereoDontCare"       );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( PixelFormatDescriptorFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( PixelFormatDescriptorFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::invalid              , "invalid"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::invalid              , "unknown"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToWindow         , "draw-to-window"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToWindow         , "draw_to_window"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToWindow         , "drawtowindow"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::direct3dAccelerated  , "direct3d-accelerated"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::direct3dAccelerated  , "direct3d_accelerated"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::direct3dAccelerated  , "direct3daccelerated"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBuffer         , "double-buffer"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBuffer         , "double_buffer"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBuffer         , "doublebuffer"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToBitmap         , "draw-to-bitmap"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToBitmap         , "draw_to_bitmap"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::drawToBitmap         , "drawtobitmap"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::stereo               , "stereo"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportGdi           , "support-gdi"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportGdi           , "support_gdi"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportGdi           , "supportgdi"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportOpenGl        , "support-open-gl"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportOpenGl        , "support_open_gl"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportOpenGl        , "supportopengl"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::genericFormat        , "generic-format"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::genericFormat        , "generic_format"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::genericFormat        , "genericformat"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::needPalette          , "need-palette"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::needPalette          , "need_palette"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::needPalette          , "needpalette"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::needSystemPalette    , "need-system-palette"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::needSystemPalette    , "needsystempalette"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::needSystemPalette    , "need_system_palette"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapExchange         , "swap-exchange"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapExchange         , "swap_exchange"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapExchange         , "swapexchange"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapCopy             , "swap-copy"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapCopy             , "swap_copy"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapCopy             , "swapcopy"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapLayerBuffers     , "swap-layer-buffers"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapLayerBuffers     , "swap_layer_buffers"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::swapLayerBuffers     , "swaplayerbuffers"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::genericAccelerated   , "generic-accelerated"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::genericAccelerated   , "generic_accelerated"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::genericAccelerated   , "genericaccelerated"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportDirectDraw    , "support-direct-draw"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportDirectDraw    , "support_direct_draw"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportDirectDraw    , "supportdirectdraw"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportComposition   , "support-composition"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportComposition   , "support_composition"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::supportComposition   , "supportcomposition"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::depthDontCare        , "depth-dont-care"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::depthDontCare        , "depth_dont_care"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::depthDontCare        , "depthdontcare"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBufferDontCare , "double-buffer-dont-care" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBufferDontCare , "double_buffer_dont_care" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::doubleBufferDontCare , "doublebufferdontcare"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::stereoDontCare       , "stereo-dont-care"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::stereoDontCare       , "stereo_dont_care"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( PixelFormatDescriptorFlags::stereoDontCare       , "stereodontcare"          );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( PixelFormatDescriptorFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(PixelFormatDescriptorFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(PixelFormatDescriptorFlags, std::set)


enum class PfdPixelType : std::uint8_t
{
    invalid      = (std::uint8_t)(-1),
    unknown      = (std::uint8_t)(-1),
    rgba         = 0x00,
    colorIndex   = 0x01

}; // enum class PfdPixelType : std::uint8_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( PfdPixelType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PfdPixelType::invalid      , "Invalid"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PfdPixelType::rgba         , "Rgba"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( PfdPixelType::colorIndex   , "ColorIndex" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( PfdPixelType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( PfdPixelType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PfdPixelType::invalid      , "invalid"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PfdPixelType::invalid      , "unknown"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PfdPixelType::rgba         , "rgba"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PfdPixelType::colorIndex   , "color-index" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PfdPixelType::colorIndex   , "color_index" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( PfdPixelType::colorIndex   , "colorindex"  );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( PfdPixelType, std::map, 1 )

} // namespace emf
} // namespace marty_draw_context

