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
    alignRight     = 0x02

}; // enum class HorAlign : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(HorAlign)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( HorAlign, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( HorAlign::left      , "Left"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( HorAlign::invalid   , "Invalid" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( HorAlign::center    , "Center"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( HorAlign::right     , "Right"   );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( HorAlign, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( HorAlign, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::left      , "left"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::left      , "align-left"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::left      , "align_left"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::left      , "alignleft"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::invalid   , "invalid"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::invalid   , "align-invalid" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::invalid   , "align_invalid" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::invalid   , "aligninvalid"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::center    , "center"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::center    , "align-center"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::center    , "align_center"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::center    , "aligncenter"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::right     , "right"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::right     , "align-right"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::right     , "align_right"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( HorAlign::right     , "alignright"    );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( HorAlign, std::map, 1 )


enum class FontStyleFlags : std::uint32_t
{
    invalid      = (std::uint32_t)(-1),
    normal       = 0x00,
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
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::italic       , "italic"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::strikeout    , "strikeout"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( FontStyleFlags::underlined   , "underlined" );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( FontStyleFlags, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(FontStyleFlags, std::set)

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(FontStyleFlags, std::set)


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


enum class GradientRoundRectFillFlags : std::uint32_t
{
    invalid       = (std::uint32_t)(-1),
    unknown       = (std::uint32_t)(-1),
    round         = 0x00,
    roundBoth     = 0x00,
    fillFull      = 0x00,
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

} // namespace marty_draw_context

