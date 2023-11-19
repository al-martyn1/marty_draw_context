#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



namespace marty_draw_context{
namespace emf{

enum class EmfRecordType : std::uint32_t
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

}; // enum class EmfRecordType : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EmfRecordType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::header                    , "Header"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polylineTo                , "PolylineTo"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polybezier                , "Polybezier"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyTextOutW              , "PolyTextOutW"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::excludeClipRect           , "ExcludeClipRect"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setColorAdjustment        , "SetColorAdjustment"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polygon                   , "Polygon"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::roundRect                 , "RoundRect"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polybezierTo              , "PolybezierTo"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::beginPath                 , "BeginPath"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyline                  , "Polyline"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyPolygon               , "PolyPolygon"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::fillRgn                   , "FillRgn"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::scaleViewportExtEx        , "ScaleViewportExtEx"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyPolyline              , "PolyPolyline"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setWindowextEx            , "SetWindowextEx"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setWindoworgEx            , "SetWindoworgEx"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setLinkedUfis             , "SetLinkedUfis"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::scaleWindowExtEx          , "ScaleWindowExtEx"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::smallTextOut              , "SmallTextOut"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setViewportextEx          , "SetViewportextEx"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setViewportorgEx          , "SetViewportorgEx"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setBrushorgEx             , "SetBrushorgEx"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::deleteObject              , "DeleteObject"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::eof                       , "Eof"                     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::pie                       , "Pie"                     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::stretchDiBits             , "StretchDiBits"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::chord                     , "Chord"                   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setMetargn                , "SetMetargn"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setPixelV                 , "SetPixelV"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setMapperFlags            , "SetMapperFlags"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setMapMode                , "SetMapMode"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::arc                       , "Arc"                     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::offsetCliprgn             , "OffsetCliprgn"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setBkMode                 , "SetBkMode"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setPolyfillMode           , "SetPolyfillMode"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setRop2                   , "SetRop2"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setIcmMode                , "SetIcmMode"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyDraw                  , "PolyDraw"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setStretchbltMode         , "SetStretchbltMode"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extFloodFill              , "ExtFloodFill"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setTextAlign              , "SetTextAlign"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setTextColor              , "SetTextColor"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::fillPath                  , "FillPath"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setBkColor                , "SetBkColor"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::realizePalette            , "RealizePalette"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::moveToEx                  , "MoveToEx"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::rectangle                 , "Rectangle"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::intersectClipRect         , "IntersectClipRect"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::saveDc                    , "SaveDc"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::restoreDc                 , "RestoreDc"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setWorldTransform         , "SetWorldTransform"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setMiterLimit             , "SetMiterLimit"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::modifyWorldTransform      , "ModifyWorldTransform"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::selectObject              , "SelectObject"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createPen                 , "CreatePen"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::selectPalette             , "SelectPalette"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extSelectClipRgn          , "ExtSelectClipRgn"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createBrushIndirect       , "CreateBrushIndirect"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::angleArc                  , "AngleArc"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::ellipse                   , "Ellipse"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::arcTo                     , "ArcTo"                   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createAlette              , "Create{Alette"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::flattenPath               , "FlattenPath"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::lineTo                    , "LineTo"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setPaletteEntries         , "SetPaletteEntries"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setColorSpace             , "SetColorSpace"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::resizePalette             , "ResizePalette"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setArcDirection           , "SetArcDirection"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::endPath                   , "EndPath"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::closeFigure               , "CloseFigure"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::strokeAndFillPath         , "StrokeAndFillPath"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::strokePath                , "StrokePath"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::widenPath                 , "WidenPath"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::selectClipPath            , "SelectClipPath"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::abortPath                 , "AbortPath"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::comment                   , "Comment"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::frameRgn                  , "FrameRgn"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::invertRgn                 , "InvertRgn"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::paintRgn                  , "PaintRgn"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::bitBlt                    , "BitBlt"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::stretchBlt                , "StretchBlt"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setLayout                 , "SetLayout"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::maskBlt                   , "MaskBlt"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::plgBlt                    , "PlgBlt"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setDiBitsToDevice         , "SetDiBitsToDevice"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extCreateFontIndirectW    , "ExtCreateFontIndirectW"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extTextOutA               , "ExtTextOutA"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polybezierTo16            , "PolybezierTo16"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extTextOutW               , "ExtTextOutW"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polybezier16              , "Polybezier16"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polygon16                 , "Polygon16"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyline16                , "Polyline16"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polylineTo16              , "PolylineTo16"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyPolyline16            , "PolyPolyline16"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyPolygon16             , "PolyPolygon16"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyDraw16                , "PolyDraw16"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createMonoBrush           , "CreateMonoBrush"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::alphablend                , "Alphablend"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createDibPatternBrushPt   , "CreateDibPatternBrushPt" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extCreatePen              , "ExtCreatePen"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::polyTextOutA              , "PolyTextOutA"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createColorSpace          , "CreateColorSpace"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::deleteColorSpace          , "DeleteColorSpace"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::glsRecord                 , "GlsRecord"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::glsBoundedRecord          , "GlsBoundedRecord"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::pixelFormat               , "PixelFormat"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::draweScape                , "DraweScape"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::extEscape                 , "ExtEscape"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::forceUfiMapping           , "ForceUfiMapping"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::namedEscape               , "NamedEscape"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::colorCorrectPalette       , "ColorCorrectPalette"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setIcmProfileA            , "SetIcmProfileA"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setIcmProfileW            , "SetIcmProfileW"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::transparentBlt            , "TransparentBlt"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::gradientFill              , "GradientFill"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::setTextJustification      , "SetTextJustification"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::colorMatchToTargetW       , "ColorMatchToTargetW"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfRecordType::createColorSpaceW         , "CreateColorSpaceW"       );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EmfRecordType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EmfRecordType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::header                    , "header"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polylineTo                , "polyline-to"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polylineTo                , "polyline_to"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polylineTo                , "polylineto"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezier                , "polybezier"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyTextOutW              , "poly-text-out-w"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyTextOutW              , "poly_text_out_w"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyTextOutW              , "polytextoutw"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::excludeClipRect           , "exclude-clip-rect"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::excludeClipRect           , "exclude_clip_rect"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::excludeClipRect           , "excludecliprect"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setColorAdjustment        , "set-color-adjustment"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setColorAdjustment        , "set_color_adjustment"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setColorAdjustment        , "setcoloradjustment"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polygon                   , "polygon"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::roundRect                 , "round-rect"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::roundRect                 , "round_rect"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::roundRect                 , "roundrect"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezierTo              , "polybezier-to"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezierTo              , "polybezier_to"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezierTo              , "polybezierto"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::beginPath                 , "begin-path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::beginPath                 , "begin_path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::beginPath                 , "beginpath"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyline                  , "polyline"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolygon               , "poly-polygon"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolygon               , "poly_polygon"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolygon               , "polypolygon"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::fillRgn                   , "fill-rgn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::fillRgn                   , "fill_rgn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::fillRgn                   , "fillrgn"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::scaleViewportExtEx        , "scale-viewport-ext-ex"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::scaleViewportExtEx        , "scale_viewport_ext_ex"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::scaleViewportExtEx        , "scaleviewportextex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolyline              , "poly-polyline"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolyline              , "poly_polyline"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolyline              , "polypolyline"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWindowextEx            , "set-windowext-ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWindowextEx            , "set_windowext_ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWindowextEx            , "setwindowextex"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWindoworgEx            , "set-windoworg-ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWindoworgEx            , "set_windoworg_ex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWindoworgEx            , "setwindoworgex"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setLinkedUfis             , "set-linked-ufis"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setLinkedUfis             , "set_linked_ufis"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setLinkedUfis             , "setlinkedufis"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::scaleWindowExtEx          , "scale-window-ext-ex"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::scaleWindowExtEx          , "scale_window_ext_ex"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::scaleWindowExtEx          , "scalewindowextex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::smallTextOut              , "small-text-out"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::smallTextOut              , "smalltextout"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::smallTextOut              , "small_text_out"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setViewportextEx          , "set-viewportext-ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setViewportextEx          , "set_viewportext_ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setViewportextEx          , "setviewportextex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setViewportorgEx          , "set-viewportorg-ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setViewportorgEx          , "setviewportorgex"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setViewportorgEx          , "set_viewportorg_ex"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBrushorgEx             , "set-brushorg-ex"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBrushorgEx             , "set_brushorg_ex"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBrushorgEx             , "setbrushorgex"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::deleteObject              , "delete-object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::deleteObject              , "delete_object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::deleteObject              , "deleteobject"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::eof                       , "eof"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::pie                       , "pie"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::stretchDiBits             , "stretch-di-bits"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::stretchDiBits             , "stretchdibits"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::stretchDiBits             , "stretch_di_bits"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::chord                     , "chord"                       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMetargn                , "set-metargn"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMetargn                , "set_metargn"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMetargn                , "setmetargn"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPixelV                 , "set-pixel-v"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPixelV                 , "set_pixel_v"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPixelV                 , "setpixelv"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMapperFlags            , "set-mapper-flags"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMapperFlags            , "set_mapper_flags"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMapperFlags            , "setmapperflags"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMapMode                , "set-map-mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMapMode                , "setmapmode"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMapMode                , "set_map_mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::arc                       , "arc"                         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::offsetCliprgn             , "offset-cliprgn"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::offsetCliprgn             , "offset_cliprgn"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::offsetCliprgn             , "offsetcliprgn"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBkMode                 , "set-bk-mode"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBkMode                 , "set_bk_mode"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBkMode                 , "setbkmode"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPolyfillMode           , "set-polyfill-mode"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPolyfillMode           , "set_polyfill_mode"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPolyfillMode           , "setpolyfillmode"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setRop2                   , "set-rop2"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setRop2                   , "set_rop2"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setRop2                   , "setrop2"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmMode                , "set-icm-mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmMode                , "set_icm_mode"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmMode                , "seticmmode"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyDraw                  , "poly-draw"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyDraw                  , "poly_draw"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyDraw                  , "polydraw"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setStretchbltMode         , "set-stretchblt-mode"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setStretchbltMode         , "setstretchbltmode"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setStretchbltMode         , "set_stretchblt_mode"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extFloodFill              , "ext-flood-fill"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extFloodFill              , "ext_flood_fill"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extFloodFill              , "extfloodfill"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextAlign              , "set-text-align"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextAlign              , "set_text_align"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextAlign              , "settextalign"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextColor              , "set-text-color"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextColor              , "set_text_color"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextColor              , "settextcolor"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::fillPath                  , "fill-path"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::fillPath                  , "fill_path"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::fillPath                  , "fillpath"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBkColor                , "set-bk-color"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBkColor                , "set_bk_color"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setBkColor                , "setbkcolor"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::realizePalette            , "realize-palette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::realizePalette            , "realize_palette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::realizePalette            , "realizepalette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::moveToEx                  , "move-to-ex"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::moveToEx                  , "move_to_ex"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::moveToEx                  , "movetoex"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::rectangle                 , "rectangle"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::intersectClipRect         , "intersect-clip-rect"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::intersectClipRect         , "intersect_clip_rect"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::intersectClipRect         , "intersectcliprect"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::saveDc                    , "save-dc"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::saveDc                    , "save_dc"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::saveDc                    , "savedc"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::restoreDc                 , "restore-dc"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::restoreDc                 , "restore_dc"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::restoreDc                 , "restoredc"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWorldTransform         , "set-world-transform"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWorldTransform         , "setworldtransform"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setWorldTransform         , "set_world_transform"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMiterLimit             , "set-miter-limit"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMiterLimit             , "set_miter_limit"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setMiterLimit             , "setmiterlimit"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::modifyWorldTransform      , "modify-world-transform"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::modifyWorldTransform      , "modifyworldtransform"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::modifyWorldTransform      , "modify_world_transform"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectObject              , "select-object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectObject              , "select_object"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectObject              , "selectobject"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createPen                 , "create-pen"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createPen                 , "create_pen"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createPen                 , "createpen"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectPalette             , "select-palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectPalette             , "select_palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectPalette             , "selectpalette"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extSelectClipRgn          , "ext-select-clip-rgn"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extSelectClipRgn          , "ext_select_clip_rgn"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extSelectClipRgn          , "extselectcliprgn"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createBrushIndirect       , "create-brush-indirect"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createBrushIndirect       , "create_brush_indirect"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createBrushIndirect       , "createbrushindirect"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::angleArc                  , "angle-arc"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::angleArc                  , "angle_arc"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::angleArc                  , "anglearc"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::ellipse                   , "ellipse"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::arcTo                     , "arc-to"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::arcTo                     , "arc_to"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::arcTo                     , "arcto"                       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createAlette              , "create-{-alette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createAlette              , "create_{_alette"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createAlette              , "create{alette"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::flattenPath               , "flatten-path"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::flattenPath               , "flatten_path"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::flattenPath               , "flattenpath"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::lineTo                    , "line-to"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::lineTo                    , "line_to"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::lineTo                    , "lineto"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPaletteEntries         , "set-palette-entries"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPaletteEntries         , "set_palette_entries"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setPaletteEntries         , "setpaletteentries"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setColorSpace             , "set-color-space"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setColorSpace             , "set_color_space"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setColorSpace             , "setcolorspace"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::resizePalette             , "resize-palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::resizePalette             , "resize_palette"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::resizePalette             , "resizepalette"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setArcDirection           , "set-arc-direction"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setArcDirection           , "set_arc_direction"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setArcDirection           , "setarcdirection"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::endPath                   , "end-path"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::endPath                   , "end_path"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::endPath                   , "endpath"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::closeFigure               , "close-figure"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::closeFigure               , "close_figure"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::closeFigure               , "closefigure"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::strokeAndFillPath         , "stroke-and-fill-path"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::strokeAndFillPath         , "stroke_and_fill_path"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::strokeAndFillPath         , "strokeandfillpath"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::strokePath                , "stroke-path"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::strokePath                , "stroke_path"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::strokePath                , "strokepath"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::widenPath                 , "widen-path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::widenPath                 , "widen_path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::widenPath                 , "widenpath"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectClipPath            , "select-clip-path"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectClipPath            , "select_clip_path"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::selectClipPath            , "selectclippath"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::abortPath                 , "abort-path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::abortPath                 , "abort_path"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::abortPath                 , "abortpath"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::comment                   , "comment"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::frameRgn                  , "frame-rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::frameRgn                  , "frame_rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::frameRgn                  , "framergn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::invertRgn                 , "invert-rgn"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::invertRgn                 , "invert_rgn"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::invertRgn                 , "invertrgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::paintRgn                  , "paint-rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::paintRgn                  , "paint_rgn"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::paintRgn                  , "paintrgn"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::bitBlt                    , "bit-blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::bitBlt                    , "bit_blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::bitBlt                    , "bitblt"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::stretchBlt                , "stretch-blt"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::stretchBlt                , "stretch_blt"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::stretchBlt                , "stretchblt"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setLayout                 , "set-layout"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setLayout                 , "set_layout"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setLayout                 , "setlayout"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::maskBlt                   , "mask-blt"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::maskBlt                   , "mask_blt"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::maskBlt                   , "maskblt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::plgBlt                    , "plg-blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::plgBlt                    , "plg_blt"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::plgBlt                    , "plgblt"                      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setDiBitsToDevice         , "set-di-bits-to-device"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setDiBitsToDevice         , "set_di_bits_to_device"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setDiBitsToDevice         , "setdibitstodevice"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extCreateFontIndirectW    , "ext-create-font-indirect-w"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extCreateFontIndirectW    , "ext_create_font_indirect_w"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extCreateFontIndirectW    , "extcreatefontindirectw"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extTextOutA               , "ext-text-out-a"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extTextOutA               , "ext_text_out_a"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extTextOutA               , "exttextouta"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezierTo16            , "polybezier-to16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezierTo16            , "polybezier_to16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezierTo16            , "polybezierto16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extTextOutW               , "ext-text-out-w"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extTextOutW               , "ext_text_out_w"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extTextOutW               , "exttextoutw"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polybezier16              , "polybezier16"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polygon16                 , "polygon16"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyline16                , "polyline16"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polylineTo16              , "polyline-to16"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polylineTo16              , "polyline_to16"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polylineTo16              , "polylineto16"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolyline16            , "poly-polyline16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolyline16            , "poly_polyline16"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolyline16            , "polypolyline16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolygon16             , "poly-polygon16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolygon16             , "poly_polygon16"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyPolygon16             , "polypolygon16"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyDraw16                , "poly-draw16"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyDraw16                , "poly_draw16"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyDraw16                , "polydraw16"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createMonoBrush           , "create-mono-brush"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createMonoBrush           , "create_mono_brush"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createMonoBrush           , "createmonobrush"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::alphablend                , "alphablend"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createDibPatternBrushPt   , "create-dib-pattern-brush-pt" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createDibPatternBrushPt   , "create_dib_pattern_brush_pt" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createDibPatternBrushPt   , "createdibpatternbrushpt"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extCreatePen              , "ext-create-pen"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extCreatePen              , "ext_create_pen"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extCreatePen              , "extcreatepen"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyTextOutA              , "poly-text-out-a"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyTextOutA              , "poly_text_out_a"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::polyTextOutA              , "polytextouta"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createColorSpace          , "create-color-space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createColorSpace          , "create_color_space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createColorSpace          , "createcolorspace"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::deleteColorSpace          , "delete-color-space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::deleteColorSpace          , "delete_color_space"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::deleteColorSpace          , "deletecolorspace"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::glsRecord                 , "gls-record"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::glsRecord                 , "gls_record"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::glsRecord                 , "glsrecord"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::glsBoundedRecord          , "gls-bounded-record"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::glsBoundedRecord          , "gls_bounded_record"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::glsBoundedRecord          , "glsboundedrecord"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::pixelFormat               , "pixel-format"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::pixelFormat               , "pixel_format"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::pixelFormat               , "pixelformat"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::draweScape                , "drawe-scape"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::draweScape                , "drawe_scape"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::draweScape                , "drawescape"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extEscape                 , "ext-escape"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extEscape                 , "ext_escape"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::extEscape                 , "extescape"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::forceUfiMapping           , "force-ufi-mapping"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::forceUfiMapping           , "force_ufi_mapping"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::forceUfiMapping           , "forceufimapping"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::namedEscape               , "named-escape"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::namedEscape               , "named_escape"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::namedEscape               , "namedescape"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::colorCorrectPalette       , "color-correct-palette"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::colorCorrectPalette       , "color_correct_palette"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::colorCorrectPalette       , "colorcorrectpalette"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmProfileA            , "set-icm-profile-a"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmProfileA            , "set_icm_profile_a"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmProfileA            , "seticmprofilea"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmProfileW            , "set-icm-profile-w"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmProfileW            , "set_icm_profile_w"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setIcmProfileW            , "seticmprofilew"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::transparentBlt            , "transparent-blt"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::transparentBlt            , "transparent_blt"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::transparentBlt            , "transparentblt"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::gradientFill              , "gradient-fill"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::gradientFill              , "gradient_fill"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::gradientFill              , "gradientfill"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextJustification      , "set-text-justification"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextJustification      , "set_text_justification"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::setTextJustification      , "settextjustification"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::colorMatchToTargetW       , "color-match-to-target-w"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::colorMatchToTargetW       , "color_match_to_target_w"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::colorMatchToTargetW       , "colormatchtotargetw"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createColorSpaceW         , "create-color-space-w"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createColorSpaceW         , "create_color_space_w"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfRecordType::createColorSpaceW         , "createcolorspacew"           );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EmfRecordType, std::map, 1 )


enum class EmfFormatSignature : std::uint32_t
{
    invalid   = (std::uint32_t)(-1),
    unknown   = (std::uint32_t)(-1),
    emf       = 0x464D4520,
    eps       = 0x46535045

}; // enum class EmfFormatSignature : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EmfFormatSignature, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfFormatSignature::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfFormatSignature::emf       , "Emf"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfFormatSignature::eps       , "Eps"     );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EmfFormatSignature, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EmfFormatSignature, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfFormatSignature::invalid   , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfFormatSignature::invalid   , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfFormatSignature::emf       , "emf"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfFormatSignature::eps       , "eps"     );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EmfFormatSignature, std::map, 1 )


enum class EmfOpenGlPresenceFlag : std::uint32_t
{
    invalid            = (std::uint32_t)(-1),
    unknown            = (std::uint32_t)(-1),
    openGlNotPresent   = 0x00000000,
    openGlAbsent       = 0x00000000,
    openGlPresent      = 0x00000001

}; // enum class EmfOpenGlPresenceFlag : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EmfOpenGlPresenceFlag, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfOpenGlPresenceFlag::invalid            , "Invalid"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "OpenGlNotPresent" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlPresent      , "OpenGlPresent"    );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EmfOpenGlPresenceFlag, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EmfOpenGlPresenceFlag, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::invalid            , "invalid"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::invalid            , "unknown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "open-gl-not-present" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "open_gl_absent"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "openglabsent"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "open_gl_not_present" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "openglnotpresent"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlNotPresent   , "open-gl-absent"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlPresent      , "open-gl-present"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlPresent      , "open_gl_present"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfOpenGlPresenceFlag::openGlPresent      , "openglpresent"       );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EmfOpenGlPresenceFlag, std::map, 1 )


enum class EmfMetafileHeaderOptions : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    basicHeader   = 0x00000000,
    headerExt1    = 0x00000001,
    headerExt2    = 0x00000002

}; // enum class EmfMetafileHeaderOptions : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EmfMetafileHeaderOptions, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfMetafileHeaderOptions::basicHeader   , "BasicHeader" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfMetafileHeaderOptions::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt1    , "HeaderExt1"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt2    , "HeaderExt2"  );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EmfMetafileHeaderOptions, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EmfMetafileHeaderOptions, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::basicHeader   , "basic-header" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::basicHeader   , "basic_header" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::basicHeader   , "basicheader"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::invalid       , "invalid"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::invalid       , "unknown"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt1    , "header-ext1"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt1    , "header_ext1"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt1    , "headerext1"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt2    , "header-ext2"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt2    , "header_ext2"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EmfMetafileHeaderOptions::headerExt2    , "headerext2"   );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EmfMetafileHeaderOptions, std::map, 1 )

} // namespace emf
} // namespace marty_draw_context

