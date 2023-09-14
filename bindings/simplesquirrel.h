/*! \file
    \brief Squirrel bindings for marty_draw_context types and interfaces (using al-martyn1/simplesquirrel)
*/

#pragma once


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

// marty_draw_context::simplesquirrel::
namespace marty_draw_context {

namespace simplesquirrel {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace utils {

//------------------------------
inline
std::string to_ascii(const char* str)
{
    return str ? std::string(str) : std::string();
}

//------------------------------
inline
std::string to_ascii(const std::string &str)
{
    return str;
}

//------------------------------
inline
std::string to_ascii(const std::wstring &str)
{
    std::string strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (char)(unsigned char)ch);
    return strRes;
}

//------------------------------
inline
std::string to_ascii(const wchar_t* str)
{
    return str ? to_ascii(std::wstring(str)) : std::string();
}

//------------------------------
struct CToAscii
{
    std::string operator()(const char* str) const
    {
        return to_ascii(str);
    }

    std::string operator()(const std::string &str) const
    {
        return to_ascii(str);
    }

    std::string operator()(const std::wstring &str) const
    {
        return to_ascii(str);
    }

    std::string operator()(const wchar_t* str) const
    {
        return to_ascii(str);
    }

    std::string operator()() const
    {
    }

}; // struct CToAscii

//------------------------------



//------------------------------
inline
std::wstring to_wide(const wchar_t* str)
{
    return str ? std::wstring(str) : std::wstring();
}

//------------------------------
inline
std::wstring to_wide(const std::wstring &str)
{
    return str;
}

//------------------------------
inline
std::wstring to_wide(const std::string &str)
{
    std::wstring strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (wchar_t)ch);
    return strRes;
}

//------------------------------
inline
std::wstring to_wide(const char* str)
{
    return str ? to_wide(std::string(str)) : std::wstring();
}

//------------------------------
struct CToWide
{
    std::wstring operator()(const wchar_t* str) const
    {
        return to_wide(str);
    }

    std::wstring operator()(const std::wstring &str) const
    {
        return to_wide(str);
    }

    std::wstring operator()(const std::string &str) const
    {
        return to_wide(str);
    }

    std::wstring operator()(const char* str) const
    {
        return to_wide(str);
    }

}; // struct CToWide

//------------------------------



//------------------------------
#if !defined(SQUNICODE)

    template<typename CharType>
    inline std::string to_sqstring(const CharType* pStr)
    {
        return to_ascii(pStr);
    }

    template<typename StringType>
    inline std::string to_sqstring(const StringType &str)
    {
        return to_ascii(str);
    }

#else

    template<typename CharType>
    inline std::wstring to_sqstring(const CharType* pStr)
    {
        return to_wide(pStr);
    }

    template<typename StringType>
    inline std::wstring to_sqstring(const StringType &str)
    {
        return to_wide(str);
    }

#endif

//------------------------------




} // namespace utils

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
struct DrawColor : public ColorRef
{

    DrawColor() : ColorRef() {}
    DrawColor(ColorRef clr) : ColorRef(clr) {}
    DrawColor(const DrawColor &clr) : ColorRef(clr) {}
    DrawColor(DrawColor &&clr)      : ColorRef(clr) {}


    static
    DrawColor fromString(const ssq::Class&, const ssq::sqstring &colorName)
    {
        try
        {
            #if !defined(SQUNICODE)

                return (DrawColor)ColorRef::deserialize(colorName);

            #else

                std::string colorNameAscii = utils::to_ascii(colorName);
                return (DrawColor)ColorRef::deserialize(colorNameAscii);

            #endif
        }
        catch(...)
        {
        }

        return DrawColor();
    }

    static
    DrawColor fromUnsignedBindHelper( const ssq::Class&, std::uint32_t uclr )
    {
        return (DrawColor)ColorRef::fromUnsigned(uclr);
    }

    static
    DrawColor fromIntBindHelper( const ssq::Class&, int iclr )
    {
        return (DrawColor)ColorRef::fromUnsigned((std::uint32_t)(std::int32_t)iclr);
    }

    int toIntBindHelper() const
    {
        return (int)(std::int32_t)toUnsigned();
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("DrawColor"))
    {
        const bool staticMethod = true ;
        const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , []() -> DrawColor*
                                {
                                    return new DrawColor();
                                }
                              , true // release
                              );

        cls.addFunc( _SC("toUnsigned")  , &DrawColor::toUnsigned);
        cls.addFunc( _SC("fromUnsigned"), &DrawColor::fromUnsignedBindHelper);

        cls.addFunc( _SC("toInt")       , &DrawColor::toIntBindHelper);
        cls.addFunc( _SC("fromInt")     , &DrawColor::fromIntBindHelper, staticMethod);

        cls.addFunc( _SC("fromString")  , &DrawColor::fromString);
        cls.addFunc( _SC("toString")
                   , [](DrawColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);
                         return utils::to_sqstring(self->serialize());
                     }
                   );


        cls.addVar(_SC("r")     , &DrawColor::r);
        cls.addVar(_SC("g")     , &DrawColor::g);
        cls.addVar(_SC("b")     , &DrawColor::b);
        cls.addVar(_SC("a")     , &DrawColor::a);


        // алиасы с динными именами для r/g/b
        // может, не делать с длинными именами?
        // может, стоит сделать кучу статиков-алисов для именованных цветов?

        // Пока не буду добавлять
        // cls.addVar(_SC("red")   , &DrawColor::r);
        // cls.addVar(_SC("green") , &DrawColor::g);
        // cls.addVar(_SC("blue")  , &DrawColor::b);
        // cls.addVar(_SC("alpha") , &DrawColor::a);

        return cls;
    }


}; // struct DrawColor

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
struct DrawCoords
{
    float x;
    float y;

    // DrawCoords() : x(0.0), y(0.0) {}
    // DrawCoords(float x_, float y_) : x(x_), y(y_) {}
    // DrawCoords(const DrawCoords &c) : x(c.x), y(c.y) {}
    // DrawCoords(DrawCoords&&) = default;

    static 
    float convertHelper(ssq::Object &o, const SQChar *paramName)
    {
        (void)paramName;

        if (o.isNull() || o.isEmpty())
        {
            return 0.0;
        }

        ssq::Type t = o.getType();
        switch(t)
        {
            case ssq::Type::INTEGER:
                return (float)o.toInt();
            case ssq::Type::FLOAT:
                return o.toFloat();
            case ssq::Type::STRING:
                {
                    auto str = o.toString();
                    try
                    {
                        return std::stof(str);
                    }
                    catch(const std::invalid_argument &)
                    {
                        throw ssq::TypeException("invalid argument", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                    }
                    catch(const std::out_of_range &)
                    {
                        throw ssq::TypeException("out of range", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                    }
                    catch(...)
                    {
                        throw ssq::TypeException("unknown error", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));
                    }
                }

            case ssq::Type::BOOL:
            case ssq::Type::NULLPTR:
            case ssq::Type::TABLE:
            case ssq::Type::ARRAY:
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

        throw ssq::TypeException("bad cast", ssq::typeToStr(ssq::Type::FLOAT), ssq::typeToStr(t));

    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("DrawCoords"))
    {
        const bool staticMethod = true ;
        const bool classMethod  = false;

        auto cls = vm.addClass( className.c_str()
                              , []( ssq::Object ox, ssq::Object oy  /* float x, float y */  ) -> DrawCoords*
                                {
                                    return new DrawCoords{convertHelper(ox, _SC("x")), convertHelper(oy, _SC("y"))};
                                }
                              , true // release
                              );

        cls.addVar(_SC("x"), &DrawCoords::x);
        cls.addVar(_SC("y"), &DrawCoords::y);

        return cls;
    }

}; // struct DrawCoords

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// https://learn.microsoft.com/ru-ru/cpp/cpp/ellipses-and-variadic-templates?view=msvc-170

inline
void makeEnumValuesVectorHelper( std::vector< std::pair<std::string, int> > &vec)
{
    (void)vec;
}

template<typename EnumVal> inline
void makeEnumValuesVectorHelper( std::vector< std::pair<std::string, int> > &vec, EnumVal val)
{
    auto strVal = enum_serialize(val);
    if (strVal.empty() || strVal=="0")
    {
        strVal = "None";
    }
    vec.emplace_back(strVal, (int)val);
}

template<typename First, typename... EnumVal> inline
void makeEnumValuesVectorHelper( std::vector< std::pair<std::string, int> > &vec, First first, EnumVal... vals)
{
    makeEnumValuesVectorHelper(vec, first);
    makeEnumValuesVectorHelper(vec, vals...);
}

template<typename... EnumVal> inline
std::vector< std::pair<std::string, int> > makeEnumValuesVector( EnumVal... vals )
{
    std::vector< std::pair<std::string, int> > vec;
    makeEnumValuesVectorHelper(vec, vals...);
    return vec;
}

template<typename First, typename... EnumVal> inline
std::vector< std::pair<std::string, int> > makeEnumValuesVector( First first, EnumVal... vals )
{
    std::vector< std::pair<std::string, int> > vec;
    makeEnumValuesVectorHelper(vec, first);
    makeEnumValuesVectorHelper(vec, vals...);
    return vec;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename... EnumVal> inline
ssq::sqstring makeEnumScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
{
    known.insert(utils::to_sqstring(enumNameOnly));

    std::string enumName = enumPrefix+enumNameOnly;

    std::vector< std::pair<std::string, int> > valNameVec = makeEnumValuesVector(vals...);

    std::string res = "enum " + enumName + "{";

    for(auto p: valNameVec)
    {
        res.append(p.first);
        res.append("=");
        res.append(std::to_string(p.second));
        res.append(1, itemSep );
    }

    res.append("}");
    res.append(1, enumSep );

    return utils::to_sqstring(res);
}

//----------------------------------------------------------------------------
template<typename... EnumVal> inline
ssq::sqstring makeFlagScriptString( const std::string &enumPrefix, const std::string &enumNameOnly, char itemSep, char enumSep, std::set<ssq::sqstring> &known, EnumVal... vals)
{
    known.insert(utils::to_sqstring(enumNameOnly));

    std::string enumName = enumPrefix+enumNameOnly;

    std::vector< std::pair<std::string, int> > valNameVec = makeFlagValuesVector(vals...);

    std::string res = "enum " + enumName + "{";

    for(auto p: valNameVec)
    {
        res.append(p.first);
        res.append("=");
        res.append(std::to_string(p.second));
        res.append(1, itemSep );
    }

    res.append("}");
    res.append(1, enumSep );

    return utils::to_sqstring(res);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
ssq::sqstring enumsExposeMakeScript(char itemSep, char enumSep, std::set<ssq::sqstring> *pKnownEnumNames = 0, const std::string &prefix = "DrawContext")
{

    // auto strVal = enum_serialize_flags(FontStyleFlags::italic);
    // //auto strVal = enum_serialize(val);
    // (void)strVal;

    std::set<ssq::sqstring> knownEnumNames;

    ssq::sqstring scriptText = 
                      makeEnumScriptString( prefix, "HorAlign"       , itemSep, enumSep, knownEnumNames
                                          , HorAlign::left, HorAlign::center, HorAlign::right
                                          );

    scriptText.append(makeEnumScriptString( prefix, "FontWeight"     , itemSep, enumSep, knownEnumNames
                                          , FontWeight::thin, FontWeight::extralight, FontWeight::light, FontWeight::normal
                                          , FontWeight::semibold, FontWeight::bold, FontWeight::extrabold, FontWeight::heavy
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "GradientType"   , itemSep, enumSep, knownEnumNames
                                          , GradientType::vertical, GradientType::horizontal
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "FontStyleFlags" , itemSep, enumSep, knownEnumNames
                                          , FontStyleFlags::normal, FontStyleFlags::italic, FontStyleFlags::underlined, FontStyleFlags::strikeout // , FontStyleFlags::italic|FontStyleFlags::strikeout
                                          )
                     );

    scriptText.append(makeEnumScriptString( prefix, "GradientRoundRectFillFlags" , itemSep, enumSep, knownEnumNames
                                          , GradientRoundRectFillFlags::round
                                          , GradientRoundRectFillFlags::squareBegin
                                          , GradientRoundRectFillFlags::squareEnd
                                          , GradientRoundRectFillFlags::noFillBegin
                                          , GradientRoundRectFillFlags::noFillEnd
                                          )
                     );

    //scriptText.append(makeEnumScriptString( prefix+"", ));

    if (pKnownEnumNames)
    {
        *pKnownEnumNames = knownEnumNames;
    }

    return scriptText;
}

//----------------------------------------------------------------------------
inline
void exposeEnums(ssq::VM &vm, const std::string &prefix = "DrawContext")
{
    ssq::sqstring scriptText = enumsExposeMakeScript('\n', '\n', 0, prefix);
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
*/
inline
ssq::sqstring prepareScriptEnums(const ssq::sqstring &scriptText, const std::string &prefix = "DrawContext",  bool prependWithEnums = true)
{
    std::set<ssq::sqstring> knownEnumNames;
    ssq::sqstring scriptEnumsStr = enumsExposeMakeScript(' ', ';', &knownEnumNames, prefix);

    ssq::sqstring sqPrefix = utils::to_sqstring(prefix);

    // first - индекс текст. фрагмента, second - найденное положение
    std::vector< std::pair<std::size_t, std::size_t> > allOccurencies;

    // переделываем в вектор, чтобы обращаться по индексу
    std::vector<ssq::sqstring> knownEnumNamesVec = std::vector<ssq::sqstring>(knownEnumNames.begin(), knownEnumNames.end());
    std::vector<ssq::sqstring> replaceToNamesVec; replaceToNamesVec.reserve(knownEnumNamesVec.size());
    for(const auto n: knownEnumNamesVec)
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


//TODO: !!! Надо попробовать сериализацию флагов через enum_serialize, а не через enum_serialize_flags - 
// нам не нужно наборы флагов сериализовывать, а только отдельные флаги
// Заодно, если установлено несколько флагов, то по идее, должна выскочить ошибка, надо проверить

//----------------------------------------------------------------------------
struct HorAlignEnumStruct
{
    typedef marty_draw_context::HorAlign   EnumType;

    const int   invalid = (int)EnumType::invalid;
    const int   left    = (int)EnumType::left   ;
    const int   center  = (int)EnumType::center ;
    const int   right   = (int)EnumType::right  ;

    static int fromString(const ssq::Class&, const ssq::sqstring &str)
    {
        return (int)enum_deserialize(utils::to_ascii(str), EnumType::invalid);
    }

    static ssq::sqstring toString(const ssq::Class&, int v)
    {
        return utils::to_sqstring(enum_serialize((EnumType)v));
    }

    static ssq::Class expose(ssq::Table /* VM */ & vm, const ssq::sqstring &className = _SC("HorAlign"))
    {
        auto cls = vm.addClass( className.c_str(), []() { return new HorAlign(); }, true /* release */ );

        cls.addFunc( _SC("fromString"), &HorAlignEnumStruct::fromString);
        cls.addFunc( _SC("toString"  ), &HorAlignEnumStruct::toString  );

        cls.addConstVar(_SC("Invalid"), &HorAlignEnumStruct::invalid, true);
        cls.addConstVar(_SC("Left"   ), &HorAlignEnumStruct::left   , true);
        cls.addConstVar(_SC("Center" ), &HorAlignEnumStruct::center , true);
        cls.addConstVar(_SC("Right"  ), &HorAlignEnumStruct::right  , true);

        return cls;
    }

}; // struct HorAlignEnumStruct

// static SQInteger base_getconsttable(HSQUIRRELVM v)
// {
//     v->Push(_ss(v)->_consts);
//     return 1;
// }

#if 0

    Table::Table(HSQUIRRELVM vm):Object(vm) {
        sq_newtable(vm);
        sq_getstackobj(vm, -1, &obj);
        sq_addref(vm, &obj);
        sq_pop(vm,1); // Pop table
    }

    Enum::Enum(HSQUIRRELVM vm):Object(vm) {
        sq_newtable(vm);
        sq_getstackobj(vm, -1, &obj);
        sq_addref(vm, &obj);
        sq_pop(vm,1); // Pop enum table
    }

    Enum VM::addEnum(const SQChar* name) {
        Enum enm(vm);
        sq_pushconsttable(vm);
        sq_pushstring(vm, name, scstrlen(name));
        detail::push<Object>(vm, enm);
        sq_newslot(vm, -3, false);
        sq_pop(vm,1); // pop table
        return std::move(enm);
    }

        template<typename T, typename... Args>
        Class addClass(const SQChar* name, const std::function<T*(Args...)>& allocator = std::bind(&detail::defaultClassAllocator<T>), bool release = true){
            sq_pushobject(vm, obj);
            Class cls(detail::addClass(vm, name, allocator, release));
            sq_pop(vm, 1);
            return cls;
        }

NewSlotA
NEW_SLOT_STATIC_FLAG

#endif

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

} // namespace simplesquirrel {

} // namespace marty_draw_context {





