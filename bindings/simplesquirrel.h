/*! \file
    \brief Squirrel bindings for marty_draw_context types and interfaces (using al-martyn1/simplesquirrel)
*/

#pragma once


#include <simplesquirrel/simplesquirrel.hpp>

#include <cstdint>

// 
#include "../colorref.h"


// ATLASSERT(IsWindow());



//---------------------------------------------------------
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


//---------------------------------------------------------
//! MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL срабатывает всегда, и ставится туда, куда, по идее, никогда попадать не должны
#define MARTY_DC_BIND_SQUIRREL_ASSERT_FAIL()                        MARTY_DC_BIND_SQUIRREL_ASSERT( 0 )






// marty_draw_context::simplesquirrel::
namespace marty_draw_context {

namespace simplesquirrel {

namespace utils {

//----------------------------------------------------------------------------
inline
std::string to_ascii(const char* str)
{
    return str ? std::string(str) : std::string();
}

//----------------------------------------------------------------------------
inline
std::string to_ascii(const std::string &str)
{
    return str;
}

//----------------------------------------------------------------------------
inline
std::string to_ascii(const std::wstring &str)
{
    std::string strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (char)(unsigned char)ch);
    return strRes;
}

//----------------------------------------------------------------------------
inline
std::string to_ascii(const wchar_t* str)
{
    return str ? to_ascii(std::wstring(str)) : std::string();
}

//----------------------------------------------------------------------------
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

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
inline
std::wstring to_wide(const wchar_t* str)
{
    return str ? std::wstring(str) : std::wstring();
}

//----------------------------------------------------------------------------
inline
std::wstring to_wide(const std::wstring &str)
{
    return str;
}

//----------------------------------------------------------------------------
inline
std::wstring to_wide(const std::string &str)
{
    std::wstring strRes; strRes.reserve(str.size());
    for(auto ch : str)
        strRes.append(1, (wchar_t)ch);
    return strRes;
}

//----------------------------------------------------------------------------
inline
std::wstring to_wide(const char* str)
{
    return str ? to_wide(std::string(str)) : std::wstring();
}

//----------------------------------------------------------------------------
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


} // namespace utils






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

    static
    int rotate() { return 10; }

    static
    int rotateI(int i) { return i; }

    // std::uint32_t toUnsigned() const
    // static ColorRef fromUnsigned(std::uint32_t crul)
    // static ColorRef deserialize(std::string str)
    // std::string serialize() const

    static ssq::Class expose(ssq::VM& vm, const ssq::sqstring &className = _SC("DrawColor"))
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

        cls.addFunc(_SC("toUnsigned")  , &DrawColor::toUnsigned);
        cls.addFunc(_SC("fromUnsigned"), &DrawColor::fromUnsignedBindHelper);


        // cls.addFunc(_SC("rotate") , &DrawColor::rotate);
        // cls.addFunc(_SC("rotateI"), &DrawColor::rotateI);


        cls.addFunc(_SC("toInt")       , &DrawColor::toIntBindHelper);
        cls.addFunc(_SC("fromInt")     , &DrawColor::fromIntBindHelper, staticMethod);

        cls.addFunc(_SC("fromString")  , &DrawColor::fromString);
        cls.addFunc( _SC("toString")
                   , [](DrawColor* self) -> ssq::sqstring
                     {
                         MARTY_DC_BIND_SQUIRREL_ASSERT(self);

                         std::string strName = self->serialize();
                         #if !defined(SQUNICODE)
                             return strName;
                         #else
                             return utils::to_wide(strName);
                         #endif
                     }
                   );


        // cls.addFunc(_SC("getMessage"), &DrawColor::getMessage);

        // Это тоже - тут какая-то рекурсия возникает
        // cls.addFunc(_SC("getMessageLowerCase"), [](CppClass* self) -> ssq::sqstring {
        //     ssq::sqstring data = self->message;
        //     //std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        //     return data;
        // });

        //cls.addVar(_SC("message"), &DrawColor::message);
        cls.addVar(_SC("r")     , &DrawColor::r);
        cls.addVar(_SC("g")     , &DrawColor::g);
        cls.addVar(_SC("b")     , &DrawColor::b);
        cls.addVar(_SC("a")     , &DrawColor::a);

        cls.addVar(_SC("red")   , &DrawColor::r);
        cls.addVar(_SC("green") , &DrawColor::g);
        cls.addVar(_SC("blue")  , &DrawColor::b);
        cls.addVar(_SC("alpha") , &DrawColor::a);

        return cls;
    }

    // We will leave them public so Squirrel 
    // can access them for the purpose of this example
    // ssq::sqstring message;
    // const int integer;



};




} // namespace simplesquirrel {

} // namespace marty_draw_context {





