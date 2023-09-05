#pragma once

#include <cstddef>
#include <cstring>
#include <cwchar>
#include <type_traits>
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <string>
#include <sstream>
#include <iomanip>

#include "marty_decimal/marty_decimal.h"


namespace marty_draw_context {


struct IDebugStreamWritter
{

    virtual
    std::size_t writeImpl( const char* str, std::size_t len) = 0;

    virtual
    std::size_t writeImpl( const wchar_t* str, std::size_t len) = 0;

    virtual
    bool isNulStreamWritter() const = 0;

    virtual ~IDebugStreamWritter() {}

};


struct DebugStreamImplBase : public IDebugStreamWritter
{

    template<typename T> struct IsIntegralType
    {
       static bool const value = std::is_integral<T>::value; // && !std::is_enum<T>::value && !std::is_same<T, bool>::value;
    };

    template<typename T> struct IsIntegralNonBoolEnumType
    {
       static bool const value = std::is_integral<T>::value && !std::is_enum<T>::value && !std::is_same<T, bool>::value;
    };

    std::size_t write( const char* str, std::size_t len = (std::size_t)-1)
    {
        if (isNulStreamWritter())
            return 0;

        if (len==(std::size_t)-1)
            len = std::strlen(str);

        return writeImpl(str,len);
    }

    std::size_t write( const wchar_t* str, std::size_t len = (std::size_t)-1)
    {
        if (isNulStreamWritter())
            return 0;

        if (len==(std::size_t)-1)
            len = std::wcslen(str);

        return writeImpl(str,len);
    }

    // template<typename T>
    // std::size_t write(const T &t)
    // {
    //     throw std::exception(std::string("DebugStreamImplBase::write not implemented for '") + typeid(t).name() + "'");
    //     return 0;
    // }

    template<typename T>
    std::enable_if_t<!IsIntegralType<T>::value, std::size_t> write(const T &t)
    //std::size_t write(const T &t)
    {
        if (isNulStreamWritter())
            return 0;

        //throw std::exception(std::string("DebugStreamImplBase::write not implemented for '") + typeid(t).name() + "'");
        //return 0;
        std::ostringstream oss;
        oss<<t;
        //const auto &str = oss.str();
        return write(oss.str().data(), oss.str().size());
    }

    template<typename T>
    std::enable_if_t<IsIntegralNonBoolEnumType<T>::value, std::size_t> write(T t)
    {
        if (isNulStreamWritter())
            return 0;

        std::string str = std::to_string(t);
        return write(str.data(), str.size());
    }

    template<typename T>
    std::enable_if_t<std::is_same<T,bool>::value, std::size_t> write(T t)
    {
        if (isNulStreamWritter())
            return 0;

        std::string str = t ? "true" : "false";
        return write(str.data(), str.size());
    }

    template<>
    std::size_t write /* <std::string> */ (const std::string &s)
    {
        if (isNulStreamWritter())
            return 0;

        return write(s.data(), s.size());
    }

    template<>
    std::size_t write /* <std::wstring> */ (const std::wstring &s)
    {
        if (isNulStreamWritter())
            return 0;

        return write(s.data(), s.size());
    }

    template<>
    std::size_t write /* <marty::Decimal> */ (const double &d)
    {
        if (isNulStreamWritter())
            return 0;

        std::ostringstream oss;
        oss << /* std::setprecision(4) << */ d;

        return write(oss.str().data(), oss.str().size());
    }

    template<>
    std::size_t write /* <marty::Decimal> */ (const marty::Decimal &d)
    {
        if (isNulStreamWritter())
            return 0;

        auto rounded = d.rounded( 4, marty::Decimal::RoundingMethod::roundMath );

        auto s = rounded.to_string(4);
        s += " (" + d.to_string() + ")";
        return write(s.data(), s.size());
    }


    //typedef marty::Decimal  value_type;


    template<typename T>
    DebugStreamImplBase& operator<<(const T &t)
    {
        write(t);
        return *this;
    }


}; // struct DebugStreamImplBase


} // namespace marty_draw_context

