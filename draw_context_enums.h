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

enum class Endianness : std::uint32_t
{
    invalid            = (std::uint32_t)(-1),
    unknown            = (std::uint32_t)(-1),
    littleEndian       = 0x00,
    bigEndian          = 0x01,
    networkByteOrder   = 0x01

}; // enum class Endianness : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(Endianness)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( Endianness, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( Endianness::invalid        , "Invalid"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( Endianness::bigEndian      , "BigEndian"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( Endianness::littleEndian   , "LittleEndian" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( Endianness, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( Endianness, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( Endianness::invalid        , "invalid"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( Endianness::invalid        , "unknown"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( Endianness::bigEndian      , "bigendian"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( Endianness::bigEndian      , "networkbyteorder" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( Endianness::littleEndian   , "littleendian"     );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( Endianness, std::map, 1 )


enum class HorAlign : std::uint32_t
{
    invalid        = (std::uint32_t)(-1),
    alignInvalid   = (std::uint32_t)(-1),
    left           = 0x00,
    alignLeft      = 0x00,
    center         = 0x01,
    alignCenter    = 0x01,
    right          = 0x02,
    alignRight     = 0x02,
    width          = 0x03,
    alignWidth     = 0x03

}; // enum class HorAlign : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(HorAlign)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( HorAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::left      , "Left"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::center    , "Center"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::right     , "Right"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::width     , "Width"   );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( HorAlign, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( HorAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::left      , "left"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::left      , "alignleft"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::invalid   , "invalid"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::invalid   , "aligninvalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::center    , "center"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::center    , "aligncenter"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::right     , "right"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::right     , "alignright"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::width     , "width"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::width     , "alignwidth"   );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( HorAlign, std::map, 1 )


enum class VertAlign : std::uint32_t
{
    invalid        = (std::uint32_t)(-1),
    alignInvalid   = (std::uint32_t)(-1),
    top            = 0x00,
    alignTop       = 0x00,
    center         = 0x01,
    alignCenter    = 0x01,
    bottom         = 0x02,
    alignBottom    = 0x02

}; // enum class VertAlign : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(VertAlign)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( VertAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::center    , "Center"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::top       , "Top"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::bottom    , "Bottom"  );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( VertAlign, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( VertAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::invalid   , "invalid"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::invalid   , "aligninvalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::center    , "center"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::center    , "aligncenter"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::top       , "top"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::top       , "aligntop"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::bottom    , "bottom"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::bottom    , "alignbottom"  );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( VertAlign, std::map, 1 )


enum class FontStyleFlags : std::uint32_t
{
    invalid      = (std::uint32_t)(-1),
    normal       = 0x00,
    none         = 0x00,
    italic       = 0x01,
    oblique      = 0x01,
    underlined   = 0x02,
    strikeout    = 0x04

}; // enum class FontStyleFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(FontStyleFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( FontStyleFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( FontStyleFlags::invalid      , "Invalid"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( FontStyleFlags::normal       , "Normal"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( FontStyleFlags::italic       , "Italic"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( FontStyleFlags::strikeout    , "Strikeout"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( FontStyleFlags::underlined   , "Underlined" );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( FontStyleFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( FontStyleFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::invalid      , "invalid"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::normal       , "normal"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::normal       , "none"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::italic       , "italic"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::italic       , "oblique"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::strikeout    , "strikeout"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::underlined   , "underlined" );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( FontStyleFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(FontStyleFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(FontStyleFlags, std::set)


enum class GradientRoundRectFillFlags : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    round         = 0x00,
    roundBoth     = 0x00,
    fillFull      = 0x00,
    none          = 0x00,
    squareBegin   = 0x01,
    squareEnd     = 0x02,
    noFillBegin   = 0x04,
    noFillEnd     = 0x08

}; // enum class GradientRoundRectFillFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(GradientRoundRectFillFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( GradientRoundRectFillFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( GradientRoundRectFillFlags::noFillBegin   , "NoFillBegin" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( GradientRoundRectFillFlags::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( GradientRoundRectFillFlags::squareEnd     , "SquareEnd"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( GradientRoundRectFillFlags::squareBegin   , "SquareBegin" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "Round"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( GradientRoundRectFillFlags::noFillEnd     , "NoFillEnd"   );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( GradientRoundRectFillFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( GradientRoundRectFillFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillBegin   , "nofillbegin" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::invalid       , "invalid"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::invalid       , "unknown"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareEnd     , "squareend"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareBegin   , "squarebegin" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "none"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "round"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "roundboth"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "fillfull"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillEnd     , "nofillend"   );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( GradientRoundRectFillFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(GradientRoundRectFillFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(GradientRoundRectFillFlags, std::set)


enum class FontWeight : int
{
    invalid      = (int)(-1),
    thin         = 100,
    _100         = 100,
    extralight   = 200,
    ultralight   = 200,
    _200         = 200,
    light        = 300,
    _300         = 300,
    normal       = 400,
    _400         = 400,
    regular      = 400,
    medium       = 500,
    _500         = 500,
    semibold     = 600,
    _600         = 600,
    demibold     = 600,
    bold         = 700,
    _700         = 700,
    extrabold    = 800,
    _800         = 800,
    ultrabold    = 800,
    heavy        = 900,
    _900         = 900,
    black        = 900

}; // enum class FontWeight : int

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(FontWeight)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( FontWeight, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::invalid      , "Invalid"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::extrabold    , "Extrabold"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::normal       , "Normal"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::thin         , "Thin"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::extralight   , "Extralight" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::light        , "Light"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::medium       , "Medium"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::bold         , "Bold"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::semibold     , "Semibold"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( FontWeight::heavy        , "Heavy"      );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( FontWeight, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( FontWeight, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::invalid      , "invalid"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::extrabold    , "extrabold"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::extrabold    , "800"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::extrabold    , "ultrabold"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::normal       , "normal"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::normal       , "400"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::normal       , "regular"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::thin         , "thin"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::thin         , "100"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::extralight   , "extralight" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::extralight   , "ultralight" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::extralight   , "200"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::light        , "light"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::light        , "300"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::medium       , "medium"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::medium       , "500"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::bold         , "700"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::bold         , "bold"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::semibold     , "semibold"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::semibold     , "600"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::semibold     , "demibold"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::heavy        , "heavy"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::heavy        , "black"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( FontWeight::heavy        , "900"        );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( FontWeight, std::map, 1 )


enum class GradientType : std::uint32_t
{
    invalid      = (std::uint32_t)(-1),
    unknown      = (std::uint32_t)(-1),
    vertical     = 0x00,
    horizontal   = 0x01

}; // enum class GradientType : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(GradientType)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( GradientType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( GradientType::invalid      , "Invalid"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( GradientType::vertical     , "Vertical"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( GradientType::horizontal   , "Horizontal" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( GradientType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( GradientType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( GradientType::invalid      , "invalid"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( GradientType::invalid      , "unknown"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( GradientType::vertical     , "vertical"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( GradientType::horizontal   , "horizontal" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( GradientType, std::map, 1 )


enum class LineType : std::uint32_t
{
    invalid      = (std::uint32_t)(-1),
    unknown      = (std::uint32_t)(-1),
    diagonal     = 0,
    vertical     = 1,
    horizontal   = 2

}; // enum class LineType : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(LineType)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( LineType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineType::invalid      , "Invalid"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineType::diagonal     , "Diagonal"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineType::vertical     , "Vertical"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineType::horizontal   , "Horizontal" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( LineType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( LineType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineType::invalid      , "invalid"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineType::invalid      , "unknown"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineType::diagonal     , "diagonal"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineType::vertical     , "vertical"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineType::horizontal   , "horizontal" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( LineType, std::map, 1 )


enum class LineDirection : std::uint32_t
{
    invalid           = (std::uint32_t)(-1),
    unknown           = (std::uint32_t)(-1),
    fromLeftToRight   = 0,
    fromTopToBottom   = 0,
    fromRightToLeft   = 1,
    fromBottomToTop   = 1

}; // enum class LineDirection : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(LineDirection)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( LineDirection, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineDirection::invalid           , "Invalid"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineDirection::fromLeftToRight   , "FromLeftToRight" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineDirection::fromRightToLeft   , "FromRightToLeft" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( LineDirection, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( LineDirection, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineDirection::invalid           , "invalid"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineDirection::invalid           , "unknown"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineDirection::fromLeftToRight   , "fromlefttoright" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineDirection::fromLeftToRight   , "fromtoptobottom" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineDirection::fromRightToLeft   , "fromrighttoleft" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineDirection::fromRightToLeft   , "frombottomtotop" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( LineDirection, std::map, 1 )


enum class LineEndcapStyle : std::uint32_t
{
    invalid   = (std::uint32_t)(-1),
    unknown   = (std::uint32_t)(-1),
    round     = 0,
    square    = 1,
    flat      = 2,
    butt      = 2

}; // enum class LineEndcapStyle : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(LineEndcapStyle)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( LineEndcapStyle, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineEndcapStyle::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineEndcapStyle::round     , "Round"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineEndcapStyle::square    , "Square"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineEndcapStyle::flat      , "Flat"    );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( LineEndcapStyle, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( LineEndcapStyle, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineEndcapStyle::invalid   , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineEndcapStyle::invalid   , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineEndcapStyle::round     , "round"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineEndcapStyle::square    , "square"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineEndcapStyle::flat      , "flat"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineEndcapStyle::flat      , "butt"    );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( LineEndcapStyle, std::map, 1 )


enum class LineJoinStyle : std::uint32_t
{
    invalid   = (std::uint32_t)(-1),
    unknown   = (std::uint32_t)(-1),
    bevel     = 0,
    mitter    = 1,
    round     = 2

}; // enum class LineJoinStyle : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(LineJoinStyle)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( LineJoinStyle, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineJoinStyle::mitter    , "Mitter"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineJoinStyle::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineJoinStyle::round     , "Round"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( LineJoinStyle::bevel     , "Bevel"   );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( LineJoinStyle, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( LineJoinStyle, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineJoinStyle::mitter    , "mitter"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineJoinStyle::invalid   , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineJoinStyle::invalid   , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineJoinStyle::round     , "round"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( LineJoinStyle::bevel     , "bevel"   );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( LineJoinStyle, std::map, 1 )


enum class BkMode : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    transparent   = 1,
    opaque        = 2

}; // enum class BkMode : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(BkMode)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( BkMode, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BkMode::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BkMode::transparent   , "Transparent" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BkMode::opaque        , "Opaque"      );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( BkMode, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( BkMode, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::invalid       , "invalid"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::invalid       , "unknown"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::transparent   , "transparent" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::opaque        , "opaque"      );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( BkMode, std::map, 1 )


enum class ArcDirectionEnum : std::uint32_t
{
    Invalid            = (std::uint32_t)(-1),
    Unknown            = (std::uint32_t)(-1),
    Clockwise          = 0,
    Cw                 = 0,
    CounterClockwise   = 1,
    Ccw                = 1

}; // enum class ArcDirectionEnum : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(ArcDirectionEnum)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( ArcDirectionEnum, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ArcDirectionEnum::Invalid            , "Invalid"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ArcDirectionEnum::Clockwise          , "Clockwise"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ArcDirectionEnum::CounterClockwise   , "CounterClockwise" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( ArcDirectionEnum, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( ArcDirectionEnum, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Invalid            , "invalid"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Invalid            , "unknown"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Clockwise          , "clockwise"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Clockwise          , "cw"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::CounterClockwise   , "counterclockwise" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::CounterClockwise   , "ccw"              );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( ArcDirectionEnum, std::map, 1 )


enum class SmoothingMode : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    defMode       = 0,
    highSpeed     = 1,
    lowQuality    = 1,
    highQuality   = 2,
    lowSpeed      = 2,
    noSmoothing   = 3,
    none          = 3,
    antiAlias     = 4

}; // enum class SmoothingMode : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(SmoothingMode)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( SmoothingMode, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( SmoothingMode::highSpeed     , "HighSpeed"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( SmoothingMode::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( SmoothingMode::antiAlias     , "AntiAlias"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( SmoothingMode::defMode       , "DefMode"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( SmoothingMode::highQuality   , "HighQuality" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( SmoothingMode::noSmoothing   , "NoSmoothing" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( SmoothingMode, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( SmoothingMode, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::highSpeed     , "highspeed"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::highSpeed     , "lowquality"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::invalid       , "invalid"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::invalid       , "unknown"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::antiAlias     , "antialias"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::defMode       , "defmode"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::highQuality   , "highquality" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::highQuality   , "lowspeed"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::noSmoothing   , "nosmoothing" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( SmoothingMode::noSmoothing   , "none"        );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( SmoothingMode, std::map, 1 )


enum class DrawingPrecise : std::uint32_t
{
    invalid            = (std::uint32_t)(-1),
    unknown            = (std::uint32_t)(-1),
    defPrecise         = 0,
    pixelPrecise       = 1,
    textPrecise        = 2,
    smoothingPrecise   = 3

}; // enum class DrawingPrecise : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(DrawingPrecise)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( DrawingPrecise, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( DrawingPrecise::invalid            , "Invalid"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( DrawingPrecise::defPrecise         , "DefPrecise"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( DrawingPrecise::pixelPrecise       , "PixelPrecise"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( DrawingPrecise::textPrecise        , "TextPrecise"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( DrawingPrecise::smoothingPrecise   , "SmoothingPrecise" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( DrawingPrecise, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( DrawingPrecise, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( DrawingPrecise::invalid            , "invalid"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( DrawingPrecise::invalid            , "unknown"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( DrawingPrecise::defPrecise         , "defprecise"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( DrawingPrecise::pixelPrecise       , "pixelprecise"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( DrawingPrecise::textPrecise        , "textprecise"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( DrawingPrecise::smoothingPrecise   , "smoothingprecise" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( DrawingPrecise, std::map, 1 )


enum class DrawTextFlags : std::uint32_t
{
    invalid                    = (std::uint32_t)(-1),
    unknown                    = (std::uint32_t)(-1),
    none                       = 0x00000000,
    defMode                    = 0x00000000,
    calcOnly                   = 0x00000001 /*!< Don't draw, calc only */,
    fitGlyphEntire             = 0x00000000 /*!< Entire glyph must fit taken width */,
    fitGlyphDefault            = 0x00000000 /*!< Entire glyph must fit taken width */,
    fitGlyphStartPos           = 0x00000002 /*!< Only start pos must fit taken width, entire glyph may go beyond boundary */,
    fitWidthDisable            = 0x00000004 /*!< Disable fit to width limit, not used for para's drawing */,
    fitHeightStartPos          = 0x00000010 /*!< Line Y start pos must fit taken height, entire line may go beyond boundary */,
    fitHeightDisable           = 0x00000020 /*!< Disable fit to height limit */,
    endEllipsis                = 0x00000100 /*!< Draw ellipsis at end if text not entire fit to limit */,
    pathEllipsis               = 0x00000200 /*!< Draw ellipsis in the middle of space if text not entire fit to limit, text interpreted as path separated by '\' or '/' */,
    wordEllipsis               = 0x00000400 /*!< Draw ellipsis in the middle of space if text not entire fit to limit, like pathEllipsis, but text is separated by spaces */,
    dontExpandTabs             = 0x00000800 /*!< If not tab stop positions taken, or if they are over, in normal case tabs will be expanded with taken tabSize. This flags disables such behavior, and forces to threat tabs as spaces */,
    kerningDisable             = 0x00001000 /*!< Disable kerning */,
    combiningAsSeparateGlyph   = 0x00002000 /*!< Combining symbol calulated as standalone symbol into pSymbolsDrawn */,
    combiningAsGlyph           = 0x00002000 /*!< Combining symbol calulated as standalone symbol into pSymbolsDrawn */,
    forceSpacesColoring        = 0x00004000 /*!< Force increment color index while drawing space chars */,
    skipEmptyParas             = 0x00008000 /*!< Skip empty paras while drawing multiple paras */,
    stopOnLineBreaks           = 0x00010000 /*!< Stop on any linebreak sequence */,
    stopOnTabs                 = 0x00020000 /*!< Stop on any hor tab symbols */,
    keepLtSpaces               = 0x00040000 /*!< Keep leading and trailing spaces while drawing paras */,
    noLastLineSpacing          = 0x00080000 /*!< Disable adding line spacing to last para line */,
    coloringResetOnPara        = 0x00100000 /*!< Start each para coloring from colors begin */,
    coloringWords              = 0x00200000 /*!< Coloring whole words insted of each letter coloring */

}; // enum class DrawTextFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(DrawTextFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( DrawTextFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitGlyphStartPos           , "FitGlyphStartPos"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::invalid                    , "Invalid"                  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::none                       , "None"                     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::calcOnly                   , "CalcOnly"                 );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitWidthDisable            , "FitWidthDisable"          );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitHeightDisable           , "FitHeightDisable"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitHeightStartPos          , "FitHeightStartPos"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::endEllipsis                , "EndEllipsis"              );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::pathEllipsis               , "PathEllipsis"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::wordEllipsis               , "WordEllipsis"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::dontExpandTabs             , "DontExpandTabs"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::kerningDisable             , "KerningDisable"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::combiningAsSeparateGlyph   , "CombiningAsSeparateGlyph" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::forceSpacesColoring        , "ForceSpacesColoring"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::stopOnLineBreaks           , "StopOnLineBreaks"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::skipEmptyParas             , "SkipEmptyParas"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::coloringResetOnPara        , "ColoringResetOnPara"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::stopOnTabs                 , "StopOnTabs"               );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::keepLtSpaces               , "KeepLtSpaces"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::noLastLineSpacing          , "NoLastLineSpacing"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::coloringWords              , "ColoringWords"            );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( DrawTextFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( DrawTextFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitGlyphStartPos           , "fitglyphstartpos"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::invalid                    , "invalid"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::invalid                    , "unknown"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::none                       , "none"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::none                       , "fitglyphdefault"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::none                       , "fitglyphentire"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::none                       , "defmode"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::calcOnly                   , "calconly"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitWidthDisable            , "fitwidthdisable"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitHeightDisable           , "fitheightdisable"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitHeightStartPos          , "fitheightstartpos"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::endEllipsis                , "endellipsis"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::pathEllipsis               , "pathellipsis"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::wordEllipsis               , "wordellipsis"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::dontExpandTabs             , "dontexpandtabs"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::kerningDisable             , "kerningdisable"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::combiningAsSeparateGlyph   , "combiningasseparateglyph" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::combiningAsSeparateGlyph   , "combiningasglyph"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::forceSpacesColoring        , "forcespacescoloring"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::stopOnLineBreaks           , "stoponlinebreaks"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::skipEmptyParas             , "skipemptyparas"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::coloringResetOnPara        , "coloringresetonpara"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::stopOnTabs                 , "stopontabs"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::keepLtSpaces               , "keepltspaces"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::noLastLineSpacing          , "nolastlinespacing"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::coloringWords              , "coloringwords"            );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( DrawTextFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(DrawTextFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(DrawTextFlags, std::set)


enum class WindowSizingEventEdge : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    none          = 0,
    left          = 1,
    right         = 2,
    top           = 3,
    topLeft       = 4,
    topRigh       = 5,
    bottom        = 6,
    bottomLeft    = 7,
    bottomRight   = 8

}; // enum class WindowSizingEventEdge : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(WindowSizingEventEdge)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( WindowSizingEventEdge, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::left          , "Left"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::none          , "None"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::topLeft       , "TopLeft"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::right         , "Right"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::top           , "Top"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::topRigh       , "TopRigh"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::bottom        , "Bottom"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::bottomLeft    , "BottomLeft"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizingEventEdge::bottomRight   , "BottomRight" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( WindowSizingEventEdge, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( WindowSizingEventEdge, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::left          , "left"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::invalid       , "invalid"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::invalid       , "unknown"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::none          , "none"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::topLeft       , "topleft"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::right         , "right"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::top           , "top"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::topRigh       , "toprigh"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::bottom        , "bottom"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::bottomLeft    , "bottomleft"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizingEventEdge::bottomRight   , "bottomright" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( WindowSizingEventEdge, std::map, 1 )


enum class WindowSizeRequestType : std::uint32_t
{
    invalid     = (std::uint32_t)(-1),
    unknown     = (std::uint32_t)(-1),
    restored    = 0,
    none        = 0,
    minimized   = 1,
    maximized   = 2,
    maxShow     = 3,
    maxHide     = 4

}; // enum class WindowSizeRequestType : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(WindowSizeRequestType)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( WindowSizeRequestType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizeRequestType::maxShow     , "MaxShow"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizeRequestType::invalid     , "Invalid"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizeRequestType::restored    , "Restored"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizeRequestType::minimized   , "Minimized" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizeRequestType::maxHide     , "MaxHide"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( WindowSizeRequestType::maximized   , "Maximized" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( WindowSizeRequestType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( WindowSizeRequestType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::maxShow     , "maxshow"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::invalid     , "invalid"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::invalid     , "unknown"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::restored    , "restored"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::restored    , "none"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::minimized   , "minimized" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::maxHide     , "maxhide"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( WindowSizeRequestType::maximized   , "maximized" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( WindowSizeRequestType, std::map, 1 )


enum class MouseButtonEvent : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    released      = 0,
    pressed       = 1,
    doubleClick   = 2

}; // enum class MouseButtonEvent : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(MouseButtonEvent)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( MouseButtonEvent, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButtonEvent::doubleClick   , "DoubleClick" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButtonEvent::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButtonEvent::released      , "Released"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButtonEvent::pressed       , "Pressed"     );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( MouseButtonEvent, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( MouseButtonEvent, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButtonEvent::doubleClick   , "doubleclick" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButtonEvent::invalid       , "invalid"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButtonEvent::invalid       , "unknown"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButtonEvent::released      , "released"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButtonEvent::pressed       , "pressed"     );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( MouseButtonEvent, std::map, 1 )


enum class MouseButton : std::uint32_t
{
    invalid        = (std::uint32_t)(-1),
    unknown        = (std::uint32_t)(-1),
    none           = 0,
    leftButton     = 1,
    rightButton    = 2,
    middleButton   = 3,
    midButton      = 3,
    xButton1       = 4,
    xButton2       = 5

}; // enum class MouseButton : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(MouseButton)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( MouseButton, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::invalid        , "Invalid"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::none           , "None"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::middleButton   , "MiddleButton" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::leftButton     , "LeftButton"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::rightButton    , "RightButton"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::xButton1       , "XButton1"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseButton::xButton2       , "XButton2"     );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( MouseButton, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( MouseButton, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::invalid        , "invalid"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::invalid        , "unknown"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::none           , "none"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::middleButton   , "middlebutton" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::middleButton   , "midbutton"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::leftButton     , "leftbutton"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::rightButton    , "rightbutton"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::xButton1       , "xbutton1"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseButton::xButton2       , "xbutton2"     );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( MouseButton, std::map, 1 )


enum class MouseButtonStateFlags : std::uint32_t
{
    invalid               = (std::uint32_t)(-1),
    unknown               = (std::uint32_t)(-1),
    none                  = 0x00000000,
    leftButtonPressed     = 0x00000001,
    rightButtonPressed    = 0x00000002,
    shiftPressed          = 0x00000004,
    controlPressed        = 0x00000008,
    middleButtonPressed   = 0x00000010,
    midButtonPressed      = 0x00000010,
    xButton1Pressed       = 0x00000020,
    xButton2Pressed       = 0x00000040

}; // enum class MouseButtonStateFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(MouseButtonStateFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( MouseButtonStateFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::xButton1Pressed       , "XButton1Pressed"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::invalid               , "Invalid"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::none                  , "None"                );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::middleButtonPressed   , "MiddleButtonPressed" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::leftButtonPressed     , "LeftButtonPressed"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::rightButtonPressed    , "RightButtonPressed"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::shiftPressed          , "ShiftPressed"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::controlPressed        , "ControlPressed"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( MouseButtonStateFlags::xButton2Pressed       , "XButton2Pressed"     );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( MouseButtonStateFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( MouseButtonStateFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::xButton1Pressed       , "xbutton1pressed"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::invalid               , "invalid"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::invalid               , "unknown"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::none                  , "none"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::middleButtonPressed   , "middlebuttonpressed" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::middleButtonPressed   , "midbuttonpressed"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::leftButtonPressed     , "leftbuttonpressed"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::rightButtonPressed    , "rightbuttonpressed"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::shiftPressed          , "shiftpressed"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::controlPressed        , "controlpressed"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( MouseButtonStateFlags::xButton2Pressed       , "xbutton2pressed"     );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( MouseButtonStateFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(MouseButtonStateFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(MouseButtonStateFlags, std::set)


enum class MouseMoveEventType : std::uint32_t
{
    invalid   = (std::uint32_t)(-1),
    unknown   = (std::uint32_t)(-1),
    move      = 0,
    hover     = 1,
    leave     = 2

}; // enum class MouseMoveEventType : std::uint32_t

MARTY_CPP_MAKE_ENUM_IS_FLAGS_FOR_NON_FLAGS_ENUM(MouseMoveEventType)

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( MouseMoveEventType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseMoveEventType::leave     , "Leave"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseMoveEventType::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseMoveEventType::move      , "Move"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( MouseMoveEventType::hover     , "Hover"   );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( MouseMoveEventType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( MouseMoveEventType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseMoveEventType::leave     , "leave"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseMoveEventType::invalid   , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseMoveEventType::invalid   , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseMoveEventType::move      , "move"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( MouseMoveEventType::hover     , "hover"   );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( MouseMoveEventType, std::map, 1 )


enum class CallbackResultFlags : std::uint32_t
{
    invalid              = (std::uint32_t)(-1),
    unknown              = (std::uint32_t)(-1),
    none                 = 0x00000000,
    repaint              = 0x00000001,
    captureMouse         = 0x00000002,
    releaseCapture       = 0x00000004,
    disableTimerUpdate   = 0x00000008,
    enableTimerUpdate    = 0x00000010

}; // enum class CallbackResultFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(CallbackResultFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( CallbackResultFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::captureMouse         , "CaptureMouse"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::invalid              , "Invalid"            );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::none                 , "None"               );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::releaseCapture       , "ReleaseCapture"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::repaint              , "Repaint"            );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::disableTimerUpdate   , "DisableTimerUpdate" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( CallbackResultFlags::enableTimerUpdate    , "EnableTimerUpdate"  );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( CallbackResultFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( CallbackResultFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::captureMouse         , "capturemouse"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::invalid              , "invalid"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::invalid              , "unknown"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::none                 , "none"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::releaseCapture       , "releasecapture"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::repaint              , "repaint"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::disableTimerUpdate   , "disabletimerupdate" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( CallbackResultFlags::enableTimerUpdate    , "enabletimerupdate"  );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( CallbackResultFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(CallbackResultFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(CallbackResultFlags, std::set)


enum class ImgListBandFlags : std::uint32_t
{
    invalid             = (std::uint32_t)(-1),
    unknown             = (std::uint32_t)(-1),
    horizontalBand      = 0x00000000,
    horBand             = 0x00000000,
    verticalBand        = 0x00000001,
    vertBand            = 0x00000001,
    skipMinSizeFrames   = 0x00000002,
    rescaleFrames       = 0x00000004,
    cutFrames           = 0x00000008

}; // enum class ImgListBandFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(ImgListBandFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( ImgListBandFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( ImgListBandFlags::rescaleFrames       , "RescaleFrames"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( ImgListBandFlags::invalid             , "Invalid"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( ImgListBandFlags::horizontalBand      , "HorizontalBand"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( ImgListBandFlags::verticalBand        , "VerticalBand"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( ImgListBandFlags::skipMinSizeFrames   , "SkipMinSizeFrames" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( ImgListBandFlags::cutFrames           , "CutFrames"         );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( ImgListBandFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( ImgListBandFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::rescaleFrames       , "rescaleframes"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::invalid             , "invalid"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::invalid             , "unknown"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::horizontalBand      , "horizontalband"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::horizontalBand      , "horband"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::verticalBand        , "verticalband"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::verticalBand        , "vertband"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::skipMinSizeFrames   , "skipminsizeframes" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( ImgListBandFlags::cutFrames           , "cutframes"         );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( ImgListBandFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(ImgListBandFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(ImgListBandFlags, std::set)

} // namespace marty_draw_context

