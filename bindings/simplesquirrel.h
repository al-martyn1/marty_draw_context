/*! \file
    \brief Squirrel bindings for marty_draw_context types and interfaces (using al-martyn1/simplesquirrel)
*/

#pragma once



#include "marty_simplesquirrel/warnings_disable.h"
//
#include "marty_simplesquirrel/simplesquirrel.h"
#include "marty_simplesquirrel/class_info.h"
//
#include <simplesquirrel/simplesquirrel.hpp>

#include <cstdint>
#include <string>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
#include <algorithm>

// 
#include "../colorref.h"
#include "../draw_context_enums.h"
#include "../draw_context_types.h"
#include "../i_draw_context.h"
#include "../i_image_list.h"
#include "../../marty_dc_impl_win32/image_list_impl.h"


#if defined(MDC_USE_DOTNUT)
    #include "../dotNut/bindings/simplesquirrel/ObjectBase.h"
    #include "../dotNut/bindings/simplesquirrel/BinaryData.h"
#endif


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/*! \def MARTY_DC_BIND_SQUIRREL_ASSERT(expr)
    Проверка условия и аварийный выход (или сообщение с последующим продолжением работы).

    При компиляции под Qt или Win32 будут вызваны соответствующие функции Qt/Windows, отображающие диалог с сообщением об ошибке.

    При компиляции для железа и работе под отладчиком последний должен показать место, где произошел assert.
    \note Не факт что это всегда работает.
*/

#if defined(Q_ASSERT)

    #define MARTY_DC_BIND_SQUIRREL_ASSERT( statement )         Q_ASSERT(statement)

#elif defined(WIN32) || defined(_WIN32)

    #include <winsock2.h>
    #include <windows.h>
    #include <crtdbg.h>

    #define MARTY_DC_BIND_SQUIRREL_ASSERT( statement )         _ASSERTE(statement)

#else

    #include <cassert>

    #define MARTY_DC_BIND_SQUIRREL_ASSERT( statement )         assert(condition) 

#endif


//------------------------------
//! MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL срабатывает всегда, и ставится туда, куда, по идее, никогда попадать не должны
#define MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL()                        MARTY_DC_BIND_SQUIRREL_ASSERT( 0 )

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// #if !defined(_SC)
//  
// #endif
//  
// #define _SC(a) L##a
// #define _SC(a) a


//
#include "simplesquirrel/ImageSize.h"
//
#include "simplesquirrel/ImageInfo.h"
//
#include "simplesquirrel/DrawingColor.h"
//
#include "simplesquirrel/AddImageBandResult.h"
//
#include "simplesquirrel/ImageList.h"
//
#include "simplesquirrel/DrawingCoords.h"
//
#include "simplesquirrel/DrawingFontParams.h"
//
#include "simplesquirrel/DrawingGradientParams.h"
//
#include "simplesquirrel/DrawingDcResourcesState.h"
//
#include "simplesquirrel/DrawingDcOffsetScale.h"
//
#include "simplesquirrel/DrawingPenParams.h"
//
#include "simplesquirrel/DrawingContext.h"



//----------------------------------------------------------------------------

// marty_draw_context::simplesquirrel::
namespace marty_draw_context {

namespace simplesquirrel {

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
ssq::sqstring enumsExposeMakeScript( marty_simplesquirrel::EnumScriptGenerationOptions generationOptions /* char itemSep, char enumSep */
                                   //, std::set<ssq::sqstring> *pKnownEnumNames = 0
                                   , const std::string &prefix = "Drawing"
                                   )
{

    // auto strVal = enum_serialize_flags(FontStyleFlags::italic);
    // //auto strVal = enum_serialize(val);
    // (void)strVal;

    //std::set<ssq::sqstring> knownEnumNames;

    // itemSep = enumSep;

    // ssq::sqstring makeEnumClassScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, const std::string &itemTypeString, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
    ssq::sqstring scriptText; // = 
                      //makeEnumScriptString( prefix, "Colors"   , itemSep, enumSep, knownEnumNames


    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "CallbackResultFlags", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , CallbackResultFlags::none               , CallbackResultFlags::repaint       
                                          , CallbackResultFlags::captureMouse       , CallbackResultFlags::releaseCapture
                                          , CallbackResultFlags::disableTimerUpdate , CallbackResultFlags::enableTimerUpdate
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseButtonEvent", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseButtonEvent::released   , MouseButtonEvent::pressed    , MouseButtonEvent::doubleClick
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseButton", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseButton::none
                                          , MouseButton::leftButton   , MouseButton::rightButton  
                                          , MouseButton::middleButton , MouseButton::midButton    
                                          , MouseButton::xButton1     , MouseButton::xButton2
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseButtonStateFlags", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseButtonStateFlags::none
                                          , MouseButtonStateFlags::leftButtonPressed   , MouseButtonStateFlags::rightButtonPressed  
                                          , MouseButtonStateFlags::shiftPressed        , MouseButtonStateFlags::controlPressed      
                                          , MouseButtonStateFlags::middleButtonPressed , MouseButtonStateFlags::midButtonPressed    
                                          , MouseButtonStateFlags::xButton1Pressed     , MouseButtonStateFlags::xButton2Pressed     
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "MouseMoveEventType", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , MouseMoveEventType::move , MouseMoveEventType::hover, MouseMoveEventType::leave //, MouseMoveEventType::enter
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "WindowSizingEventEdge", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , WindowSizingEventEdge::none       , WindowSizingEventEdge::left       , WindowSizingEventEdge::right
                                          , WindowSizingEventEdge::top        , WindowSizingEventEdge::topLeft    , WindowSizingEventEdge::topRigh
                                          , WindowSizingEventEdge::bottom     , WindowSizingEventEdge::bottomLeft , WindowSizingEventEdge::bottomRight
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "WindowSizeRequestType", ""   , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , WindowSizeRequestType::restored , WindowSizeRequestType::minimized, WindowSizeRequestType::maximized, WindowSizeRequestType::maxShow, WindowSizeRequestType::maxHide
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "HorAlign", ""       , generationOptions // itemSep, enumSep // , knownEnumNames
                                          //, std::vector<std::pair<std::string, int> >{ {"AlignLeft", HorAlign::alignLeft}, {"AlignCenter", HorAlign::alignCenter}, {"AlignRight", HorAlign::alignRight}, {"AlignWidth", HorAlign::alignWidth} }
                                          , HorAlign::left, HorAlign::center, HorAlign::right
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString(prefix + ".", "VertAlign", ""       , generationOptions // itemSep, enumSep // , knownEnumNames
                                          , VertAlign::top, VertAlign::center, VertAlign::bottom
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "FontStyleFlags", "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , FontStyleFlags::normal, FontStyleFlags::italic, FontStyleFlags::underlined, FontStyleFlags::strikeout // , FontStyleFlags::italic|FontStyleFlags::strikeout
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "ImageListBandFlags", "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"HorBand", (int)ImgListBandFlags::horBand}
                                                                                     , {"VertBand", (int)ImgListBandFlags::vertBand}
                                                                                     }
                                          , ImgListBandFlags::horizontalBand
                                          , ImgListBandFlags::verticalBand
                                          , ImgListBandFlags::skipMinSizeFrames
                                          , ImgListBandFlags::rescaleFrames
                                          , ImgListBandFlags::cutFrames
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "GradientRoundRectFillFlags" , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , GradientRoundRectFillFlags::round
                                          , GradientRoundRectFillFlags::squareBegin
                                          , GradientRoundRectFillFlags::squareEnd
                                          , GradientRoundRectFillFlags::noFillBegin
                                          , GradientRoundRectFillFlags::noFillEnd
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "FontWeight"     , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"Ultralight", (int)FontWeight::ultralight}
                                                                                     , {"Regular"   , (int)FontWeight::regular}
                                                                                     , {"Demibold"  , (int)FontWeight::demibold}
                                                                                     , {"Ultrabold" , (int)FontWeight::ultrabold}
                                                                                     , {"Black"     , (int)FontWeight::black}
                                                                                     }
                                          , FontWeight::thin, FontWeight::extralight, FontWeight::light, FontWeight::normal
                                          , FontWeight::semibold, FontWeight::bold, FontWeight::extrabold, FontWeight::heavy
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "GradientType"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , GradientType::vertical, GradientType::horizontal
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "LineType"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , LineType::diagonal, LineType::vertical, LineType::horizontal
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "DrawTextFlags" , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"DefMode", (int)DrawTextFlags::defMode}
                                                                                     , {"FitGlyphEntire", (int)DrawTextFlags::fitGlyphEntire}
                                                                                     , {"FitGlyphDefault", (int)DrawTextFlags::fitGlyphDefault}
                                                                                     }
                                          , DrawTextFlags::none                     , DrawTextFlags::calcOnly                 , DrawTextFlags::fitGlyphStartPos
                                          , DrawTextFlags::fitWidthDisable          , DrawTextFlags::fitHeightStartPos        , DrawTextFlags::fitHeightDisable
                                          , DrawTextFlags::endEllipsis              , DrawTextFlags::pathEllipsis             , DrawTextFlags::wordEllipsis
                                          , DrawTextFlags::dontExpandTabs           , DrawTextFlags::kerningDisable           , DrawTextFlags::combiningAsSeparateGlyph
                                          , DrawTextFlags::forceSpacesColoring      , DrawTextFlags::skipEmptyParas           , DrawTextFlags::stopOnLineBreaks
                                          , DrawTextFlags::stopOnTabs               , DrawTextFlags::keepLtSpaces             , DrawTextFlags::noLastLineSpacing
                                          , DrawTextFlags::coloringResetOnPara      , DrawTextFlags::coloringWords
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "LineDirection"    , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"FromTopToBottom" , (int)LineDirection::fromTopToBottom}
                                                                                     , {"FromBottomToTop" , (int)LineDirection::fromBottomToTop}
                                                                                     }
                                          , LineDirection::fromLeftToRight, LineDirection::fromRightToLeft
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "LineEndcapStyle"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"Butt" , (int)LineEndcapStyle::butt}
                                                                                     }
                                          , LineEndcapStyle::round, LineEndcapStyle::square, LineEndcapStyle::flat
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "LineJoinStyle"   , "", generationOptions // itemSep, enumSep// , knownEnumNames
                                          , LineJoinStyle::bevel, LineJoinStyle::mitter, LineJoinStyle::round
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "BkMode"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , BkMode::opaque, BkMode::transparent
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "ArcDirection"  , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"Ccw" , (int)ArcDirectionEnum::Ccw}
                                                                                     , {"Cw"  , (int)ArcDirectionEnum::Cw}
                                                                                     }
                                          , ArcDirectionEnum::CounterClockwise, ArcDirectionEnum::Clockwise
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptStringEx( prefix + ".", "SmoothingMode" , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , std::vector<std::pair<std::string, int> >{ {"LowQuality" , (int)SmoothingMode::lowQuality}
                                                                                     , {"LowSpeed"   , (int)SmoothingMode::lowSpeed}
                                                                                     , {"None"       , (int)SmoothingMode::none}
                                                                                     }
                                          , SmoothingMode::defMode, SmoothingMode::highSpeed, SmoothingMode::highQuality, SmoothingMode::noSmoothing, SmoothingMode::antiAlias
                                          )
                     );

    scriptText.append(marty_simplesquirrel::makeEnumClassScriptString( prefix + ".", "DrawingPrecise"   , "", generationOptions // itemSep, enumSep // , knownEnumNames
                                          , DrawingPrecise::defPrecise, DrawingPrecise::pixelPrecise, DrawingPrecise::textPrecise, DrawingPrecise::smoothingPrecise
                                          )
                     );

    scriptText.append(
                      marty_simplesquirrel::makeEnumClassScriptString( prefix+".", "Colors", prefix+".Color"   , generationOptions // enumSep /* itemSep */ , enumSep // , knownEnumNames
                                          , EColorRawEnum::AliceBlue       , EColorRawEnum::AntiqueWhite   , EColorRawEnum::Aqua             , EColorRawEnum::Aquamarine          
                                          , EColorRawEnum::Azure           , EColorRawEnum::Beige          , EColorRawEnum::Bisque           , EColorRawEnum::Black               
                                          , EColorRawEnum::BlanchedAlmond  , EColorRawEnum::Blue           , EColorRawEnum::BlueViolet       , EColorRawEnum::Brown               
                                          , EColorRawEnum::BurlyWood       , EColorRawEnum::CadetBlue      , EColorRawEnum::Chartreuse       , EColorRawEnum::Chocolate           
                                          , EColorRawEnum::Cyan            , EColorRawEnum::MediumCyan
                                          , EColorRawEnum::Coral           , EColorRawEnum::CornflowerBlue , EColorRawEnum::Cornsilk         , EColorRawEnum::DarkCyan            
                                          , EColorRawEnum::DarkGoldenRod   , EColorRawEnum::DarkGray       , EColorRawEnum::DarkGrey         , EColorRawEnum::DarkGreen           
                                          , EColorRawEnum::DarkKhaki       , EColorRawEnum::DarkMagenta    , EColorRawEnum::DarkOliveGreen   , EColorRawEnum::DarkOrange          
                                          , EColorRawEnum::DarkOrchid      , EColorRawEnum::DarkRed        , EColorRawEnum::DarkSalmon       , EColorRawEnum::DarkSeaGreen        
                                          , EColorRawEnum::DarkSlateBlue   , EColorRawEnum::DarkSlateGray  , EColorRawEnum::DarkSlateGrey    , EColorRawEnum::DarkTurquoise       
                                          , EColorRawEnum::DarkViolet      , EColorRawEnum::DeepPink       , EColorRawEnum::DeepSkyBlue      , EColorRawEnum::DimGray             
                                          , EColorRawEnum::DimGrey         , EColorRawEnum::DodgerBlue     , EColorRawEnum::FireBrick        , EColorRawEnum::FloralWhite         
                                          , EColorRawEnum::ForestGreen     , EColorRawEnum::Fuchsia        , EColorRawEnum::Gainsboro        , EColorRawEnum::GhostWhite          
                                          , EColorRawEnum::Gold            , EColorRawEnum::GoldenRod      , EColorRawEnum::Gray             , EColorRawEnum::Grey                
                                          , EColorRawEnum::Green           , EColorRawEnum::GreenYellow    , EColorRawEnum::HoneyDew         , EColorRawEnum::HotPink             
                                          , EColorRawEnum::IndianRed       , EColorRawEnum::Indigo         , EColorRawEnum::Ivory            , EColorRawEnum::Khaki               
                                          , EColorRawEnum::Lavender        , EColorRawEnum::LavenderBlush  , EColorRawEnum::LawnGreen        , EColorRawEnum::LemonChiffon        
                                          , EColorRawEnum::LightBlue       , EColorRawEnum::LightCoral     , EColorRawEnum::LightCyan        , EColorRawEnum::LightGoldenRodYellow
                                          , EColorRawEnum::LightGray       , EColorRawEnum::LightGrey      , EColorRawEnum::LightGreen       , EColorRawEnum::LightPink           
                                          , EColorRawEnum::LightSalmon     , EColorRawEnum::LightSeaGreen  , EColorRawEnum::LightSkyBlue     , EColorRawEnum::LightSlateGray      
                                          , EColorRawEnum::LightSlateGrey  , EColorRawEnum::LightSteelBlue , EColorRawEnum::LightYellow      , EColorRawEnum::Lime                
                                          , EColorRawEnum::LimeGreen       , EColorRawEnum::Linen          , EColorRawEnum::Magenta          , EColorRawEnum::Maroon              
                                          , EColorRawEnum::MediumAquaMarine, EColorRawEnum::MediumBlue     , EColorRawEnum::MediumOrchid     , EColorRawEnum::MediumPurple        
                                          , EColorRawEnum::MediumSeaGreen  , EColorRawEnum::MediumSlateBlue, EColorRawEnum::MediumSpringGreen, EColorRawEnum::MediumTurquoise     
                                          , EColorRawEnum::MediumVioletRed , EColorRawEnum::MidnightBlue   , EColorRawEnum::MintCream        , EColorRawEnum::MistyRose           
                                          , EColorRawEnum::Moccasin        , EColorRawEnum::NavajoWhite    , EColorRawEnum::Navy             , EColorRawEnum::OldLace             
                                          , EColorRawEnum::Olive           , EColorRawEnum::OliveDrab      , EColorRawEnum::Orange           , EColorRawEnum::OrangeRed           
                                          , EColorRawEnum::Orchid          , EColorRawEnum::PaleGoldenRod  , EColorRawEnum::PaleGreen        , EColorRawEnum::PaleTurquoise       
                                          , EColorRawEnum::PaleVioletRed   , EColorRawEnum::PapayaWhip     , EColorRawEnum::PeachPuff        , EColorRawEnum::Peru                
                                          , EColorRawEnum::Pink            , EColorRawEnum::Plum           , EColorRawEnum::PowderBlue       , EColorRawEnum::Purple              
                                          , EColorRawEnum::RebeccaPurple   , EColorRawEnum::Red            , EColorRawEnum::RosyBrown        , EColorRawEnum::RoyalBlue           
                                          , EColorRawEnum::SaddleBrown     , EColorRawEnum::Salmon         , EColorRawEnum::SandyBrown       , EColorRawEnum::SeaGreen            
                                          , EColorRawEnum::SeaShell        , EColorRawEnum::Sienna         , EColorRawEnum::Silver           , EColorRawEnum::SkyBlue             
                                          , EColorRawEnum::SlateBlue       , EColorRawEnum::SlateGray      , EColorRawEnum::SlateGrey        , EColorRawEnum::Snow                
                                          , EColorRawEnum::SpringGreen     , EColorRawEnum::SteelBlue      , EColorRawEnum::Tan              , EColorRawEnum::Teal                
                                          , EColorRawEnum::Thistle         , EColorRawEnum::Tomato         , EColorRawEnum::Turquoise        , EColorRawEnum::Violet
                                          , EColorRawEnum::Wheat           , EColorRawEnum::White          , EColorRawEnum::WhiteSmoke       , EColorRawEnum::Yellow
                                          , EColorRawEnum::YellowGreen         
                                          )
                     );



    // if (pKnownEnumNames)
    // {
    //     *pKnownEnumNames = knownEnumNames;
    // }

    return scriptText;
}

//----------------------------------------------------------------------------
inline
void exposeEnums(ssq::VM &vm, const marty_simplesquirrel::EnumScriptGenerationOptions& generationOptions, const std::string &prefix = "Drawing")
{
    //ssq::sqstring scriptText = enumsExposeMakeScript('\n', '\n', 0, prefix);
    ssq::sqstring scriptText = enumsExposeMakeScript(generationOptions, prefix);
    ssq::Script script = vm.compileSource(scriptText.c_str());
    vm.run(script);
}

//----------------------------------------------------------------------------
// first - индекс текст. фрагмента, second - найденное положение
inline
std::vector< std::pair<std::size_t, std::size_t> > findAllOccurencies(const ssq::sqstring &text, const ssq::sqstring &item, std::size_t itemIndex)
{
    std::vector< std::pair<std::size_t, std::size_t> > resVec;

    std::size_t pos = text.find(item, 0);
    while(pos!=text.npos)
    {
        resVec.emplace_back(itemIndex, pos);
        pos = text.find(item, pos+item.size());
    }

    return resVec;
}

//----------------------------------------------------------------------------
inline
std::vector< std::pair<std::size_t, std::size_t> > mergeOccurenciesVectors( const std::vector< std::pair<std::size_t, std::size_t> > &v1
                                                                          , const std::vector< std::pair<std::size_t, std::size_t> > &v2
                                                                          )
{
    std::vector< std::pair<std::size_t, std::size_t> > resVec; resVec.reserve(v1.size()+v2.size());

    std::vector< std::pair<std::size_t, std::size_t> >::const_iterator it1 = v1.begin();
    std::vector< std::pair<std::size_t, std::size_t> >::const_iterator it2 = v2.begin();

    // Основной цикл - пока оба итератора не дошли до конца - так мы можем обращаться по любому из них
    while(it1!=v1.end() && it2!=v2.end())
    {
        if (it1->second < it2->second)
        {
            resVec.emplace_back(*it1);
            ++it1;
        }
        else
        {
            resVec.emplace_back(*it2);
            ++it2;
        }
    }

    // Добавляем хвосты, если есть

    resVec.insert(resVec.end(), it1, v1.end());
    resVec.insert(resVec.end(), it2, v2.end());

    return resVec;
}

//----------------------------------------------------------------------------
//! Производит переименование enum'ов, также может добавлять в начало скрипта скрипт задания enum'ов
/*!
Мы можем обращаться с enum'ам только через "namespace" DrawContext.EnumName.value
Или, мы сделали алиас таблицы:
local dc = DrawContext

Используем так
... = dc.EnumName.value

Или с полным именем namespace:
... = DrawContext.EnumName.value


Других вариантов вроде нет

Когда обращаемся по имени голобального enum, это выглядит так:
... = DrawContextEnumName.value
... = DrawContext_EnumName.value

Enum'ы у нас зарегистрированы как DrawContextEnumName (или DrawContext_EnumName?)
При обращении к EnumName через namespace перед EnumName должна быть точка.
Если точки нет - то это ображение через глобальное имя, ничего не делаем.
Если точка есть - то идем к началу строки, допустимые символы A-Zaz0-9 и символ подчеркивания, 
останавливаемся, если достигли начало строки, или встретили недопустимый символ.
После этого заменяем подстроку xxx.EnumName.value на DrawContext_EnumName.value

Замену производим с конца, так как, если менять с начала, то "поедут" последующие индексы

!!! Могут быть проблемы, если где-то в строковых литералах будут встречаться строки вида xxx.EnumName.
Но это довольно маловероятная ситуация


//TODO: !!! Попробовать переделать через static поля классов - http://www.squirrel-lang.org/squirreldoc/reference/language/classes.html#static-variables
Надо будет нагенерить классов
*/
#if 0
inline
ssq::sqstring prepareScriptEnums(const ssq::sqstring &scriptText, const std::string &prefix = "Drawing",  bool prependWithEnums = true)
{
    std::set<ssq::sqstring> knownEnumNames;
    ssq::sqstring scriptEnumsStr = enumsExposeMakeScript(' ', ';', &knownEnumNames, prefix);

    ssq::sqstring sqPrefix = marty_simplesquirrel::to_sqstring(prefix);

    // first - индекс текст. фрагмента, second - найденное положение
    std::vector< std::pair<std::size_t, std::size_t> > allOccurencies;

    // переделываем в вектор, чтобы обращаться по индексу
    std::vector<ssq::sqstring> knownEnumNamesVec = std::vector<ssq::sqstring>(knownEnumNames.begin(), knownEnumNames.end());
    std::vector<ssq::sqstring> replaceToNamesVec; replaceToNamesVec.reserve(knownEnumNamesVec.size());
    for(const auto &n: knownEnumNamesVec)
    {
        replaceToNamesVec.emplace_back(sqPrefix+n);
    }

    for( std::size_t nameIdx=0; nameIdx!=knownEnumNamesVec.size(); ++nameIdx )
    {
        //std::vector< std::pair<std::size_t, std::size_t> > tmp = findAllOccurencies(scriptText, knownEnumNamesVec[nameIdx], nameIdx);
        allOccurencies = mergeOccurenciesVectors(allOccurencies, findAllOccurencies(scriptText, knownEnumNamesVec[nameIdx], nameIdx));
    }

    // У нас тут есть вектор вхождений всех интересующих нас имён, отсортированный по возрастанию позиции
    std::reverse(allOccurencies.begin(), allOccurencies.end());
    // А теперь вектор отсортирован по убыванию позиции

    // A-Zaz0-9 и символ подчеркивания
    auto isValidNameChar = [](SQChar ch) -> bool
    {
        if ((ch>=_SC('A') && ch<=_SC('Z')) || (ch>=_SC('a') && ch<=_SC('z')) || (ch>=_SC('0') && ch<=_SC('9')) || ch==_SC('_'))
        {
            return true;
        }

        return false;
    };

    

    ssq::sqstring scriptTextResult = scriptText;

    for(std::vector< std::pair<std::size_t, std::size_t> >::const_iterator ait = allOccurencies.begin(); ait!=allOccurencies.end(); ++ait)
    {
        std::size_t nameIdx = ait->first;
        const ssq::sqstring &name = knownEnumNamesVec[nameIdx];
        std::size_t nameLen = name.size();
        std::size_t pos     = ait->second;
        std::size_t namePos = pos;

        if (pos==0)
        {
            continue; // Имя найдено в самом начале, тут ничего не заменить
        }

        --pos;
        if (scriptTextResult[pos]!=_SC('.'))
        {
            continue; // Точка не найдена перед именем enum'а
        }

        if (pos==0)
        {
            continue; // Точка найдена в самом начале, тут ничего не заменить
        }

        --pos;

        while(true)
        {
            if (!isValidNameChar(scriptTextResult[pos]))
            {
                ++pos; // Откатываемся вперёд на первый символ имени
                break;
            }

            if (pos==0)
            {
                break; // вниз двигаться больше нельзя, стоим на нулевой позиции, вперёд откат не нужен
            }

            --pos; // идём дальше "вниз"
        }

        std::size_t foundExtraLen = namePos - pos;

        if (foundExtraLen<2)
        {
            continue; // найдена только точка или вообще ничего
        }

        scriptTextResult.replace(pos, foundExtraLen+nameLen, replaceToNamesVec[nameIdx]);

    } // for

    if (prependWithEnums)
    {
        scriptTextResult = scriptEnumsStr + scriptTextResult;
    }
    
    return scriptTextResult;
}
#endif


//TODO: !!! Надо попробовать сериализацию флагов через enum_serialize, а не через enum_serialize_flags - 
// нам не нужно наборы флагов сериализовывать, а только отдельные флаги
// Заодно, если установлено несколько флагов, то по идее, должна выскочить ошибка, надо проверить

//----------------------------------------------------------------------------





//----------------------------------------------------------------------------
template<typename TVM>
ssq::sqstring performBinding(TVM &vm, const ssq::sqstring &scriptText, const std::string &ns, const marty_simplesquirrel::EnumScriptGenerationOptions &generationOptions)
{
    //ssq::sqstring preparedScriptText1 = marty_draw_context::simplesquirrel::prepareScriptEnums(scriptText, ns, true);
    std::set<ssq::sqstring> knownEnumNames;
    ssq::sqstring preparedScriptText1 = enumsExposeMakeScript( generationOptions
                                                             //, &knownEnumNames
                                                             , ns /* prefix */
                                                             );
    preparedScriptText1 += scriptText;

    ssq::sqstring sqNs = marty_simplesquirrel::to_sqstring(ns);

    // lout << encoding::toUtf8(preparedScriptText1);
    // lout << "\n----------\n\n";

    ssq::Table tDraw = 
    vm.addTable(sqNs.c_str());
    marty_draw_context::simplesquirrel::DrawingCoords          ::expose(tDraw /*vm*/, _SC("Coords"));
    marty_draw_context::simplesquirrel::DrawingCoords          ::expose(tDraw /*vm*/, _SC("Scale"));
    //marty_draw_context::simplesquirrel::DrawingCoords          ::expose(tDraw /*vm*/, _SC(""));
    marty_draw_context::simplesquirrel::DrawingFontParams      ::expose(tDraw /*vm*/, _SC("FontParams"));
    marty_draw_context::simplesquirrel::DrawingGradientParams  ::expose(tDraw /*vm*/, _SC("GradientParams"));
    marty_draw_context::simplesquirrel::DrawingPenParams       ::expose(tDraw /*vm*/, _SC("PenParams"));
    marty_draw_context::simplesquirrel::DrawingContext         ::expose(tDraw /*vm*/, _SC("Context"));
    marty_draw_context::simplesquirrel::DrawingColor           ::expose(tDraw /*vm*/, _SC("Color"));

    exposeImageSize(tDraw);
    exposeImageInfo(tDraw);
    marty_draw_context::simplesquirrel::AddImageBandResult     ::expose(tDraw /*vm*/, _SC("AddImageBandResult"));

#if defined(MDC_USE_DOTNUT)

    ImageListWrapper::expose(tDraw);

#endif

    return preparedScriptText1;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
marty_simplesquirrel::ClassInfo getDrawingCoreClassesInfo()
{
    //std::vector<marty_simplesquirrel::ClassInfo> res;
    auto rootNs = marty_simplesquirrel::ClassInfo(true);

    auto nsDrawing = marty_simplesquirrel::ClassInfo("Drawing", true);
    //nsDrawing.addClass( DrawingColor                   ::getClassInfo("Color") );
    //nsDrawing.addClass( DrawingCoords                  ::getClassInfo("Coords") );
    //nsDrawing.addClass( DrawingCoords                  ::getClassInfo("Scale") );
    //nsDrawing.addClass( DrawingFontParams              ::getClassInfo("FontParams") );
    //nsDrawing.addClass( DrawingGradientParams          ::getClassInfo("GradientParams") );
    //nsDrawing.addClass( DrawingPenParams               ::getClassInfo("PenParams") );
    //nsDrawing.addClass( DrawingContext                 ::getClassInfo("Context") );

    rootNs.addClass(nsDrawing);

    return rootNs;
}
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

} // namespace simplesquirrel {

} // namespace marty_draw_context {



#include "marty_simplesquirrel/warnings_restore.h"




