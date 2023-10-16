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

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( HorAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::left      , "Left"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::center    , "Center"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::right     , "Right"   );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( HorAlign::width     , "Width"   );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( HorAlign, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( HorAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::left      , "left"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::left      , "align-left"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::left      , "align_left"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::left      , "alignleft"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::invalid   , "invalid"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::invalid   , "align-invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::invalid   , "align_invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::invalid   , "aligninvalid"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::center    , "center"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::center    , "align-center"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::center    , "align_center"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::center    , "aligncenter"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::right     , "right"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::right     , "align-right"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::right     , "align_right"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::right     , "alignright"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::width     , "width"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::width     , "align-width"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::width     , "align_width"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( HorAlign::width     , "alignwidth"    );
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

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( VertAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::center    , "Center"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::top       , "Top"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( VertAlign::bottom    , "Bottom"  );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( VertAlign, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( VertAlign, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::invalid   , "invalid"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::invalid   , "align-invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::invalid   , "align_invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::invalid   , "aligninvalid"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::center    , "center"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::center    , "align-center"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::center    , "align_center"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::center    , "aligncenter"   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::top       , "top"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::top       , "align-top"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::top       , "align_top"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::top       , "aligntop"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::bottom    , "bottom"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::bottom    , "align-bottom"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::bottom    , "align_bottom"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( VertAlign::bottom    , "alignbottom"   );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( VertAlign, std::map, 1 )


enum class FontStyleFlags : std::uint32_t
{
    invalid      = (std::uint32_t)(-1),
    normal       = 0x00,
    none         = 0x00,
    italic       = 0x01,
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
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillBegin   , "no-fill-begin" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillBegin   , "nofillbegin"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillBegin   , "no_fill_begin" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::invalid       , "invalid"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::invalid       , "unknown"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareEnd     , "square-end"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareEnd     , "square_end"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareEnd     , "squareend"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareBegin   , "square-begin"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareBegin   , "square_begin"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::squareBegin   , "squarebegin"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "none"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "round_both"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "round"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "round-both"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "roundboth"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "fill-full"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "fill_full"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::round         , "fillfull"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillEnd     , "no-fill-end"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillEnd     , "nofillend"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( GradientRoundRectFillFlags::noFillEnd     , "no_fill_end"   );
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
    flat      = 2

}; // enum class LineEndcapStyle : std::uint32_t

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
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( LineEndcapStyle, std::map, 1 )


enum class LineJoinStyle : std::uint32_t
{
    invalid   = (std::uint32_t)(-1),
    unknown   = (std::uint32_t)(-1),
    bevel     = 0,
    mitter    = 1,
    round     = 2

}; // enum class LineJoinStyle : std::uint32_t

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
    opaque        = 0,
    transparent   = 1

}; // enum class BkMode : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( BkMode, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BkMode::invalid       , "Invalid"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BkMode::opaque        , "Opaque"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( BkMode::transparent   , "Transparent" );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( BkMode, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( BkMode, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::invalid       , "invalid"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::invalid       , "unknown"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::opaque        , "opaque"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( BkMode::transparent   , "transparent" );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( BkMode, std::map, 1 )


enum class ArcDirectionEnum : std::uint32_t
{
    Invalid            = (std::uint32_t)(-1),
    Unknown            = (std::uint32_t)(-1),
    Cw                 = 0,
    Clockwise          = 0,
    Ccw                = 1,
    CounterClockwise   = 1

}; // enum class ArcDirectionEnum : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( ArcDirectionEnum, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ArcDirectionEnum::Invalid   , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ArcDirectionEnum::Cw        , "Cw"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ArcDirectionEnum::Ccw       , "Ccw"     );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( ArcDirectionEnum, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( ArcDirectionEnum, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Invalid   , "invalid"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Invalid   , "unknown"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Cw        , "cw"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Cw        , "clockwise"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Ccw       , "ccw"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ArcDirectionEnum::Ccw       , "counterclockwise" );
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
    defMode                    = 0x00000000,
    calcOnly                   = 0x00000001 /*!< Don't draw, calc only */,
    fitGlyphEntire             = 0x00000000 /*!< Entire glyph must fit taken width */,
    fitGlyphDefault            = 0x00000000 /*!< Entire glyph must fit taken width */,
    fitGlyphStartPos           = 0x00000002 /*!< Only start pos must fit taken width, entire glyph may go beyond boundary */,
    fitWidthDisable            = 0x00000004 /*!< Disable fit to width limit, not used for para's drawing */,
    fitHeightStartPos          = 0x00000010 /*!< Line Y start pos must fit taken height, entire line may go beyond boundary */,
    fitHeightDisable           = 0x00000020 /*!< Disable fit to height limit, not used for para's drawing */,
    endEllipsis                = 0x00000100 /*!< Draw ellipsis if text not entire fit to limit */,
    kerningDisable             = 0x00000200 /*!< Disable kerning */,
    combiningAsSeparateGlyph   = 0x00000400 /*!< Combining symbol calulated as standalone symbol into pSymbolsDrawn */,
    combiningAsGlyph           = 0x00000400 /*!< Combining symbol calulated as standalone symbol into pSymbolsDrawn */,
    forceSpacesColoring        = 0x00000800,
    stopOnLineBreaks           = 0x00001000 /*!< Stop on any linebreak sequence */,
    stopOnTabs                 = 0x00002000 /*!< Stop on any hor tab symbols */

}; // enum class DrawTextFlags : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(DrawTextFlags)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( DrawTextFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitGlyphStartPos           , "FitGlyphStartPos"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::invalid                    , "Invalid"                  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::defMode                    , "DefMode"                  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::calcOnly                   , "CalcOnly"                 );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitWidthDisable            , "FitWidthDisable"          );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitHeightDisable           , "FitHeightDisable"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::fitHeightStartPos          , "FitHeightStartPos"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::endEllipsis                , "EndEllipsis"              );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::kerningDisable             , "KerningDisable"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::combiningAsSeparateGlyph   , "CombiningAsSeparateGlyph" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::forceSpacesColoring        , "ForceSpacesColoring"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::stopOnLineBreaks           , "StopOnLineBreaks"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( DrawTextFlags::stopOnTabs                 , "StopOnTabs"               );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( DrawTextFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( DrawTextFlags, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitGlyphStartPos           , "fitglyphstartpos"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::invalid                    , "invalid"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::invalid                    , "unknown"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::defMode                    , "fitglyphdefault"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::defMode                    , "fitglyphentire"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::defMode                    , "defmode"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::calcOnly                   , "calconly"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitWidthDisable            , "fitwidthdisable"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitHeightDisable           , "fitheightdisable"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::fitHeightStartPos          , "fitheightstartpos"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::endEllipsis                , "endellipsis"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::kerningDisable             , "kerningdisable"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::combiningAsSeparateGlyph   , "combiningasseparateglyph" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::combiningAsSeparateGlyph   , "combiningasglyph"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::forceSpacesColoring        , "forcespacescoloring"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::stopOnLineBreaks           , "stoponlinebreaks"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( DrawTextFlags::stopOnTabs                 , "stopontabs"               );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( DrawTextFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(DrawTextFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(DrawTextFlags, std::set)

} // namespace marty_draw_context

