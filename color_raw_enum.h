#pragma once

#include "marty_cpp/marty_enum.h"

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>



namespace marty_draw_context{

enum class EColorRawEnum : std::uint32_t
{
    AliceBlue              = 0xF0F8FF,
    AntiqueWhite           = 0xFAEBD7,
    Aqua                   = 0x00FFFF,
    Aquamarine             = 0x7FFFD4,
    Azure                  = 0xF0FFFF,
    Beige                  = 0xF5F5DC,
    Bisque                 = 0xFFE4C4,
    Black                  = 0x000000,
    BlanchedAlmond         = 0xFFEBCD,
    Blue                   = 0x0000FF,
    BlueViolet             = 0x8A2BE2,
    Brown                  = 0xA52A2A,
    BurlyWood              = 0xDEB887,
    CadetBlue              = 0x5F9EA0,
    Chartreuse             = 0x7FFF00,
    Cyan                   = 0x00FFFF,
    MediumCyan             = 0x00B7EB,
    Chocolate              = 0xD2691E,
    Coral                  = 0xFF7F50,
    CornflowerBlue         = 0x6495ED,
    Cornsilk               = 0xFFF8DC,
    DarkCyan               = 0x008B8B,
    DarkGoldenRod          = 0xB8860B,
    DarkGray               = 0xA9A9A9,
    DarkGrey               = 0xA9A9A9,
    DarkGreen              = 0x006400,
    DarkKhaki              = 0xBDB76B,
    DarkMagenta            = 0x8B008B,
    DarkOliveGreen         = 0x556B2F,
    DarkOrange             = 0xFF8C00,
    DarkOrchid             = 0x9932CC,
    DarkRed                = 0x8B0000,
    DarkSalmon             = 0xE9967A,
    DarkSeaGreen           = 0x8FBC8F,
    DarkSlateBlue          = 0x483D8B,
    DarkSlateGray          = 0x2F4F4F,
    DarkSlateGrey          = 0x2F4F4F,
    DarkTurquoise          = 0x00CED1,
    DarkViolet             = 0x9400D3,
    DeepPink               = 0xFF1493,
    DeepSkyBlue            = 0x00BFFF,
    DimGray                = 0x696969,
    DimGrey                = 0x696969,
    DodgerBlue             = 0x1E90FF,
    FireBrick              = 0xB22222,
    FloralWhite            = 0xFFFAF0,
    ForestGreen            = 0x228B22,
    Fuchsia                = 0xFF00FF,
    Gainsboro              = 0xDCDCDC,
    GhostWhite             = 0xF8F8FF,
    Gold                   = 0xFFD700,
    GoldenRod              = 0xDAA520,
    Gray                   = 0x808080,
    Grey                   = 0x808080,
    Green                  = 0x008000,
    GreenYellow            = 0xADFF2F,
    HoneyDew               = 0xF0FFF0,
    HotPink                = 0xFF69B4,
    IndianRed              = 0xCD5C5C,
    Indigo                 = 0x4B0082,
    Ivory                  = 0xFFFFF0,
    Khaki                  = 0xF0E68C,
    Lavender               = 0xE6E6FA,
    LavenderBlush          = 0xFFF0F5,
    LawnGreen              = 0x7CFC00,
    LemonChiffon           = 0xFFFACD,
    LightBlue              = 0xADD8E6,
    LightCoral             = 0xF08080,
    LightCyan              = 0xE0FFFF,
    LightGoldenRodYellow   = 0xFAFAD2,
    LightGray              = 0xD3D3D3,
    LightGrey              = 0xD3D3D3,
    LightGreen             = 0x90EE90,
    LightPink              = 0xFFB6C1,
    LightSalmon            = 0xFFA07A,
    LightSeaGreen          = 0x20B2AA,
    LightSkyBlue           = 0x87CEFA,
    LightSlateGray         = 0x778899,
    LightSlateGrey         = 0x778899,
    LightSteelBlue         = 0xB0C4DE,
    LightYellow            = 0xFFFFE0,
    Lime                   = 0x00FF00,
    LimeGreen              = 0x32CD32,
    Linen                  = 0xFAF0E6,
    Magenta                = 0xFE00FE,
    Maroon                 = 0x800000,
    MediumAquaMarine       = 0x66CDAA,
    MediumBlue             = 0x0000CD,
    MediumOrchid           = 0xBA55D3,
    MediumPurple           = 0x9370DB,
    MediumSeaGreen         = 0x3CB371,
    MediumSlateBlue        = 0x7B68EE,
    MediumSpringGreen      = 0x00FA9A,
    MediumTurquoise        = 0x48D1CC,
    MediumVioletRed        = 0xC71585,
    MidnightBlue           = 0x191970,
    MintCream              = 0xF5FFFA,
    MistyRose              = 0xFFE4E1,
    Moccasin               = 0xFFE4B5,
    NavajoWhite            = 0xFFDEAD,
    Navy                   = 0x000080,
    OldLace                = 0xFDF5E6,
    Olive                  = 0x808000,
    OliveDrab              = 0x6B8E23,
    Orange                 = 0xFFA500,
    OrangeRed              = 0xFF4500,
    Orchid                 = 0xDA70D6,
    PaleGoldenRod          = 0xEEE8AA,
    PaleGreen              = 0x98FB98,
    PaleTurquoise          = 0xAFEEEE,
    PaleVioletRed          = 0xDB7093,
    PapayaWhip             = 0xFFEFD5,
    PeachPuff              = 0xFFDAB9,
    Peru                   = 0xCD853F,
    Pink                   = 0xFFC0CB,
    Plum                   = 0xDDA0DD,
    PowderBlue             = 0xB0E0E6,
    Purple                 = 0x800080,
    RebeccaPurple          = 0x663399,
    Red                    = 0xFF0000,
    RosyBrown              = 0xBC8F8F,
    RoyalBlue              = 0x4169E1,
    SaddleBrown            = 0x8B4513,
    Salmon                 = 0xFA8072,
    SandyBrown             = 0xF4A460,
    SeaGreen               = 0x2E8B57,
    SeaShell               = 0xFFF5EE,
    Sienna                 = 0xA0522D,
    Silver                 = 0xC0C0C0,
    SkyBlue                = 0x87CEEB,
    SlateBlue              = 0x6A5ACD,
    SlateGray              = 0x708090,
    SlateGrey              = 0x708090,
    Snow                   = 0xFFFAFA,
    SpringGreen            = 0x00FF7F,
    SteelBlue              = 0x4682B4,
    Tan                    = 0xD2B48C,
    Teal                   = 0x008080,
    Thistle                = 0xD8BFD8,
    Tomato                 = 0xFF6347,
    Turquoise              = 0x40E0D0,
    Violet                 = 0xEE82EE,
    Wheat                  = 0xF5DEB3,
    White                  = 0xFFFFFF,
    WhiteSmoke             = 0xF5F5F5,
    Yellow                 = 0xFFFF00,
    YellowGreen            = 0x9ACD32

}; // enum class EColorRawEnum : std::uint32_t

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( EColorRawEnum, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Beige                 , "Beige"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Peru                  , "Peru"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::AliceBlue             , "AliceBlue"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SeaGreen              , "SeaGreen"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Aquamarine            , "Aquamarine"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DeepPink              , "DeepPink"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkOliveGreen        , "DarkOliveGreen"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::AntiqueWhite          , "AntiqueWhite"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SlateGray             , "SlateGray"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Aqua                  , "Aqua"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Azure                 , "Azure"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkOrchid            , "DarkOrchid"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkGray              , "DarkGray"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Bisque                , "Bisque"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Black                 , "Black"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::BlanchedAlmond        , "BlanchedAlmond"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Blue                  , "Blue"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PaleTurquoise         , "PaleTurquoise"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::BlueViolet            , "BlueViolet"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Brown                 , "Brown"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::RebeccaPurple         , "RebeccaPurple"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Magenta               , "Magenta"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::BurlyWood             , "BurlyWood"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::CadetBlue             , "CadetBlue"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::GhostWhite            , "GhostWhite"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PeachPuff             , "PeachPuff"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Chartreuse            , "Chartreuse"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumCyan            , "MediumCyan"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "DarkSlateGray"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Chocolate             , "Chocolate"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkKhaki             , "DarkKhaki"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Coral                 , "Coral"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkMagenta           , "DarkMagenta"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::CornflowerBlue        , "CornflowerBlue"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Cornsilk              , "Cornsilk"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Gray                  , "Gray"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Fuchsia               , "Fuchsia"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkTurquoise         , "DarkTurquoise"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkCyan              , "DarkCyan"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkGoldenRod         , "DarkGoldenRod"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Red                   , "Red"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::GreenYellow           , "GreenYellow"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MistyRose             , "MistyRose"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkGreen             , "DarkGreen"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Indigo                , "Indigo"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Sienna                , "Sienna"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkOrange            , "DarkOrange"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Green                 , "Green"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkRed               , "DarkRed"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkSalmon            , "DarkSalmon"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightPink             , "LightPink"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkSeaGreen          , "DarkSeaGreen"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkSlateBlue         , "DarkSlateBlue"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DarkViolet            , "DarkViolet"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DeepSkyBlue           , "DeepSkyBlue"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DimGray               , "DimGray"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::DodgerBlue            , "DodgerBlue"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::FireBrick             , "FireBrick"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LawnGreen             , "LawnGreen"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SlateBlue             , "SlateBlue"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Ivory                 , "Ivory"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightCyan             , "LightCyan"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::FloralWhite           , "FloralWhite"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LemonChiffon          , "LemonChiffon"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::ForestGreen           , "ForestGreen"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Gold                  , "Gold"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightBlue             , "LightBlue"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Gainsboro             , "Gainsboro"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::GoldenRod             , "GoldenRod"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::HotPink               , "HotPink"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::HoneyDew              , "HoneyDew"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::IndianRed             , "IndianRed"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Khaki                 , "Khaki"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Lavender              , "Lavender"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LavenderBlush         , "LavenderBlush"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightCoral            , "LightCoral"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightGoldenRodYellow  , "LightGoldenRodYellow" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Lime                  , "Lime"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightGray             , "LightGray"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightGreen            , "LightGreen"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightSalmon           , "LightSalmon"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Navy                  , "Navy"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MidnightBlue          , "MidnightBlue"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightSeaGreen         , "LightSeaGreen"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightSkyBlue          , "LightSkyBlue"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LimeGreen             , "LimeGreen"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "LightSlateGray"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightSteelBlue        , "LightSteelBlue"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::LightYellow           , "LightYellow"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Plum                  , "Plum"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Orange                , "Orange"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Linen                 , "Linen"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Maroon                , "Maroon"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumAquaMarine      , "MediumAquaMarine"     );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumBlue            , "MediumBlue"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumOrchid          , "MediumOrchid"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumPurple          , "MediumPurple"         );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumSeaGreen        , "MediumSeaGreen"       );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumSlateBlue       , "MediumSlateBlue"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumSpringGreen     , "MediumSpringGreen"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumTurquoise       , "MediumTurquoise"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MediumVioletRed       , "MediumVioletRed"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::MintCream             , "MintCream"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Moccasin              , "Moccasin"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::NavajoWhite           , "NavajoWhite"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::OldLace               , "OldLace"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Olive                 , "Olive"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::OliveDrab             , "OliveDrab"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::OrangeRed             , "OrangeRed"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Orchid                , "Orchid"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PaleGoldenRod         , "PaleGoldenRod"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PaleGreen             , "PaleGreen"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PaleVioletRed         , "PaleVioletRed"        );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PapayaWhip            , "PapayaWhip"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Pink                  , "Pink"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::PowderBlue            , "PowderBlue"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Purple                , "Purple"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::RosyBrown             , "RosyBrown"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::RoyalBlue             , "RoyalBlue"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SaddleBrown           , "SaddleBrown"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Salmon                , "Salmon"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SandyBrown            , "SandyBrown"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SeaShell              , "SeaShell"             );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Silver                , "Silver"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SkyBlue               , "SkyBlue"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Violet                , "Violet"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Snow                  , "Snow"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SpringGreen           , "SpringGreen"          );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::SteelBlue             , "SteelBlue"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Tan                   , "Tan"                  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Teal                  , "Teal"                 );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Thistle               , "Thistle"              );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Tomato                , "Tomato"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Turquoise             , "Turquoise"            );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Wheat                 , "Wheat"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::White                 , "White"                );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::WhiteSmoke            , "WhiteSmoke"           );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::Yellow                , "Yellow"               );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( EColorRawEnum::YellowGreen           , "YellowGreen"          );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( EColorRawEnum, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( EColorRawEnum, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Beige                 , "beige"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Peru                  , "peru"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::AliceBlue             , "alice-blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::AliceBlue             , "alice_blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::AliceBlue             , "aliceblue"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SeaGreen              , "sea-green"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SeaGreen              , "sea_green"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SeaGreen              , "seagreen"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Aquamarine            , "aquamarine"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DeepPink              , "deep-pink"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DeepPink              , "deep_pink"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DeepPink              , "deeppink"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOliveGreen        , "dark-olive-green"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOliveGreen        , "dark_olive_green"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOliveGreen        , "darkolivegreen"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::AntiqueWhite          , "antique-white"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::AntiqueWhite          , "antique_white"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::AntiqueWhite          , "antiquewhite"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateGray             , "slate-gray"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateGray             , "slate_gray"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateGray             , "slategray"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateGray             , "slate-grey"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateGray             , "slate_grey"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateGray             , "slategrey"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Aqua                  , "aqua"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Aqua                  , "cyan"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Azure                 , "azure"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOrchid            , "dark-orchid"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOrchid            , "dark_orchid"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOrchid            , "darkorchid"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGray              , "dark-gray"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGray              , "dark_gray"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGray              , "darkgray"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGray              , "dark-grey"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGray              , "dark_grey"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGray              , "darkgrey"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Bisque                , "bisque"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Black                 , "black"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BlanchedAlmond        , "blanched-almond"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BlanchedAlmond        , "blanched_almond"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BlanchedAlmond        , "blanchedalmond"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Blue                  , "blue"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleTurquoise         , "pale-turquoise"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleTurquoise         , "pale_turquoise"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleTurquoise         , "paleturquoise"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BlueViolet            , "blue-violet"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BlueViolet            , "blue_violet"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BlueViolet            , "blueviolet"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Brown                 , "brown"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RebeccaPurple         , "rebecca-purple"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RebeccaPurple         , "rebecca_purple"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RebeccaPurple         , "rebeccapurple"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Magenta               , "magenta"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BurlyWood             , "burly-wood"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BurlyWood             , "burly_wood"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::BurlyWood             , "burlywood"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::CadetBlue             , "cadet-blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::CadetBlue             , "cadet_blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::CadetBlue             , "cadetblue"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GhostWhite            , "ghost-white"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GhostWhite            , "ghost_white"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GhostWhite            , "ghostwhite"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PeachPuff             , "peach-puff"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PeachPuff             , "peach_puff"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PeachPuff             , "peachpuff"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Chartreuse            , "chartreuse"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumCyan            , "medium-cyan"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumCyan            , "medium_cyan"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumCyan            , "mediumcyan"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "dark_slate_grey"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "dark-slate-gray"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "dark-slate-grey"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "dark_slate_gray"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "darkslategray"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateGray         , "darkslategrey"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Chocolate             , "chocolate"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkKhaki             , "dark-khaki"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkKhaki             , "dark_khaki"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkKhaki             , "darkkhaki"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Coral                 , "coral"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkMagenta           , "dark-magenta"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkMagenta           , "dark_magenta"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkMagenta           , "darkmagenta"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::CornflowerBlue        , "cornflower-blue"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::CornflowerBlue        , "cornflower_blue"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::CornflowerBlue        , "cornflowerblue"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Cornsilk              , "cornsilk"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Gray                  , "gray"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Gray                  , "grey"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Fuchsia               , "fuchsia"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkTurquoise         , "dark-turquoise"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkTurquoise         , "dark_turquoise"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkTurquoise         , "darkturquoise"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkCyan              , "dark-cyan"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkCyan              , "dark_cyan"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkCyan              , "darkcyan"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGoldenRod         , "dark-golden-rod"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGoldenRod         , "dark_golden_rod"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGoldenRod         , "darkgoldenrod"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Red                   , "red"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GreenYellow           , "green-yellow"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GreenYellow           , "green_yellow"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GreenYellow           , "greenyellow"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MistyRose             , "misty-rose"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MistyRose             , "misty_rose"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MistyRose             , "mistyrose"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGreen             , "dark-green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGreen             , "dark_green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkGreen             , "darkgreen"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Indigo                , "indigo"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Sienna                , "sienna"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOrange            , "dark-orange"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOrange            , "dark_orange"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkOrange            , "darkorange"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Green                 , "green"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkRed               , "dark-red"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkRed               , "dark_red"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkRed               , "darkred"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSalmon            , "dark-salmon"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSalmon            , "dark_salmon"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSalmon            , "darksalmon"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightPink             , "light-pink"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightPink             , "light_pink"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightPink             , "lightpink"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSeaGreen          , "dark-sea-green"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSeaGreen          , "dark_sea_green"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSeaGreen          , "darkseagreen"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateBlue         , "dark-slate-blue"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateBlue         , "dark_slate_blue"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkSlateBlue         , "darkslateblue"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkViolet            , "dark-violet"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkViolet            , "dark_violet"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DarkViolet            , "darkviolet"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DeepSkyBlue           , "deep-sky-blue"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DeepSkyBlue           , "deep_sky_blue"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DeepSkyBlue           , "deepskyblue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DimGray               , "dim-gray"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DimGray               , "dim_gray"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DimGray               , "dimgray"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DimGray               , "dim-grey"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DimGray               , "dim_grey"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DimGray               , "dimgrey"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DodgerBlue            , "dodger-blue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DodgerBlue            , "dodger_blue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::DodgerBlue            , "dodgerblue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::FireBrick             , "fire-brick"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::FireBrick             , "fire_brick"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::FireBrick             , "firebrick"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LawnGreen             , "lawn-green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LawnGreen             , "lawn_green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LawnGreen             , "lawngreen"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateBlue             , "slate-blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateBlue             , "slate_blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SlateBlue             , "slateblue"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Ivory                 , "ivory"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightCyan             , "light-cyan"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightCyan             , "light_cyan"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightCyan             , "lightcyan"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::FloralWhite           , "floral-white"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::FloralWhite           , "floral_white"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::FloralWhite           , "floralwhite"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LemonChiffon          , "lemon-chiffon"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LemonChiffon          , "lemon_chiffon"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LemonChiffon          , "lemonchiffon"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::ForestGreen           , "forest-green"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::ForestGreen           , "forest_green"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::ForestGreen           , "forestgreen"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Gold                  , "gold"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightBlue             , "light-blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightBlue             , "light_blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightBlue             , "lightblue"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Gainsboro             , "gainsboro"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GoldenRod             , "golden-rod"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GoldenRod             , "golden_rod"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::GoldenRod             , "goldenrod"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::HotPink               , "hot-pink"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::HotPink               , "hot_pink"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::HotPink               , "hotpink"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::HoneyDew              , "honey-dew"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::HoneyDew              , "honey_dew"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::HoneyDew              , "honeydew"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::IndianRed             , "indian-red"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::IndianRed             , "indian_red"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::IndianRed             , "indianred"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Khaki                 , "khaki"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Lavender              , "lavender"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LavenderBlush         , "lavender-blush"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LavenderBlush         , "lavender_blush"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LavenderBlush         , "lavenderblush"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightCoral            , "light-coral"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightCoral            , "light_coral"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightCoral            , "lightcoral"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGoldenRodYellow  , "light-golden-rod-yellow" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGoldenRodYellow  , "light_golden_rod_yellow" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGoldenRodYellow  , "lightgoldenrodyellow"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Lime                  , "lime"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGray             , "light-gray"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGray             , "light_gray"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGray             , "lightgray"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGray             , "light-grey"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGray             , "light_grey"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGray             , "lightgrey"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGreen            , "light-green"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGreen            , "light_green"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightGreen            , "lightgreen"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSalmon           , "light-salmon"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSalmon           , "light_salmon"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSalmon           , "lightsalmon"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Navy                  , "navy"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MidnightBlue          , "midnight-blue"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MidnightBlue          , "midnight_blue"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MidnightBlue          , "midnightblue"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSeaGreen         , "light-sea-green"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSeaGreen         , "light_sea_green"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSeaGreen         , "lightseagreen"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSkyBlue          , "light-sky-blue"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSkyBlue          , "light_sky_blue"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSkyBlue          , "lightskyblue"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LimeGreen             , "lime-green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LimeGreen             , "lime_green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LimeGreen             , "limegreen"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "light_slate_grey"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "light-slate-gray"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "light-slate-grey"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "light_slate_gray"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "lightslategray"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSlateGray        , "lightslategrey"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSteelBlue        , "light-steel-blue"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSteelBlue        , "light_steel_blue"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightSteelBlue        , "lightsteelblue"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightYellow           , "light-yellow"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightYellow           , "light_yellow"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::LightYellow           , "lightyellow"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Plum                  , "plum"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Orange                , "orange"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Linen                 , "linen"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Maroon                , "maroon"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumAquaMarine      , "medium-aqua-marine"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumAquaMarine      , "medium_aqua_marine"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumAquaMarine      , "mediumaquamarine"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumBlue            , "medium-blue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumBlue            , "medium_blue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumBlue            , "mediumblue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumOrchid          , "medium-orchid"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumOrchid          , "medium_orchid"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumOrchid          , "mediumorchid"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumPurple          , "medium-purple"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumPurple          , "medium_purple"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumPurple          , "mediumpurple"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSeaGreen        , "medium-sea-green"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSeaGreen        , "medium_sea_green"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSeaGreen        , "mediumseagreen"          );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSlateBlue       , "medium-slate-blue"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSlateBlue       , "medium_slate_blue"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSlateBlue       , "mediumslateblue"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSpringGreen     , "medium-spring-green"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSpringGreen     , "medium_spring_green"     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumSpringGreen     , "mediumspringgreen"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumTurquoise       , "medium-turquoise"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumTurquoise       , "medium_turquoise"        );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumTurquoise       , "mediumturquoise"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumVioletRed       , "medium-violet-red"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumVioletRed       , "mediumvioletred"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MediumVioletRed       , "medium_violet_red"       );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MintCream             , "mint-cream"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MintCream             , "mint_cream"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::MintCream             , "mintcream"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Moccasin              , "moccasin"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::NavajoWhite           , "navajo-white"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::NavajoWhite           , "navajo_white"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::NavajoWhite           , "navajowhite"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OldLace               , "old-lace"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OldLace               , "old_lace"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OldLace               , "oldlace"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Olive                 , "olive"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OliveDrab             , "olive-drab"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OliveDrab             , "olive_drab"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OliveDrab             , "olivedrab"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OrangeRed             , "orange-red"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OrangeRed             , "orange_red"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::OrangeRed             , "orangered"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Orchid                , "orchid"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleGoldenRod         , "pale-golden-rod"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleGoldenRod         , "pale_golden_rod"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleGoldenRod         , "palegoldenrod"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleGreen             , "pale-green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleGreen             , "pale_green"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleGreen             , "palegreen"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleVioletRed         , "pale-violet-red"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleVioletRed         , "pale_violet_red"         );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PaleVioletRed         , "palevioletred"           );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PapayaWhip            , "papaya-whip"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PapayaWhip            , "papaya_whip"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PapayaWhip            , "papayawhip"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Pink                  , "pink"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PowderBlue            , "powder-blue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PowderBlue            , "powder_blue"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::PowderBlue            , "powderblue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Purple                , "purple"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RosyBrown             , "rosy-brown"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RosyBrown             , "rosy_brown"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RosyBrown             , "rosybrown"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RoyalBlue             , "royal-blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RoyalBlue             , "royal_blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::RoyalBlue             , "royalblue"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SaddleBrown           , "saddle-brown"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SaddleBrown           , "saddle_brown"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SaddleBrown           , "saddlebrown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Salmon                , "salmon"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SandyBrown            , "sandy-brown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SandyBrown            , "sandy_brown"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SandyBrown            , "sandybrown"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SeaShell              , "sea-shell"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SeaShell              , "sea_shell"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SeaShell              , "seashell"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Silver                , "silver"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SkyBlue               , "sky-blue"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SkyBlue               , "sky_blue"                );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SkyBlue               , "skyblue"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Violet                , "violet"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Snow                  , "snow"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SpringGreen           , "spring-green"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SpringGreen           , "spring_green"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SpringGreen           , "springgreen"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SteelBlue             , "steel-blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SteelBlue             , "steel_blue"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::SteelBlue             , "steelblue"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Tan                   , "tan"                     );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Teal                  , "teal"                    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Thistle               , "thistle"                 );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Tomato                , "tomato"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Turquoise             , "turquoise"               );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Wheat                 , "wheat"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::White                 , "white"                   );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::WhiteSmoke            , "white-smoke"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::WhiteSmoke            , "white_smoke"             );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::WhiteSmoke            , "whitesmoke"              );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::Yellow                , "yellow"                  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::YellowGreen           , "yellow-green"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::YellowGreen           , "yellow_green"            );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( EColorRawEnum::YellowGreen           , "yellowgreen"             );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( EColorRawEnum, std::map, 1 )

} // namespace marty_draw_context

