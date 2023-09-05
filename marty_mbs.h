#pragma once

/*
  Умеем определять длину символа в char'ах (в wchar_t'ах)
  Не умеем узнавать composite, поэтому стараемся использовать precomposed
  Надо бы в FileSystem интерфейс в реализацию readFile добавить эту фичу по конвертации composite->precomposed
 */

// https://ru.stackoverflow.com/questions/299930/%D0%9A%D0%B0%D0%BA-%D0%BE%D0%BF%D1%80%D0%B5%D0%B4%D0%B5%D0%BB%D0%B8%D1%82%D1%8C-%D1%8F%D0%B2%D0%BB%D1%8F%D0%B5%D1%82%D1%81%D1%8F-%D0%BB%D0%B8-utf8-%D1%81%D0%B8%D0%BC%D0%B2%D0%BE%D0%BB-%D0%B1%D1%83%D0%BA%D0%B2%D0%B5%D0%BD%D0%BD%D1%8B%D0%BC

// Вроде бы про отрисовку - https://learn.microsoft.com/en-us/windows/win32/gdi/character-widths
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getcharwidth32a
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getcharabcwidthsa


// https://www.codeproject.com/Articles/2995/The-Complete-Guide-to-C-Strings-Part-I-Win32-Chara



// https://ru.wikipedia.org/wiki/UTF-32

// https://ru.wikipedia.org/wiki/UTF-16

// https://ru.wikipedia.org/wiki/UTF-8

// https://ru.wikipedia.org/wiki/TrueType#.D0.A1.D0.BE.D1.81.D1.82.D0.B0.D0.B2.D0.BD.D0.BE.D0.B9_.D1.81.D0.B8.D0.BC.D0.B2.D0.BE.D0.BB

// http://www.nubaria.com/en/blog/?p=289


// https://learn.microsoft.com/en-us/windows/win32/intl/unicode-and-character-set-functions
// https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-getstringtypew
// https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-getstringtypeexw

// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/mbrtoc16-mbrtoc323?view=msvc-170
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/interpretation-of-multibyte-character-sequences?view=msvc-170
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/mbstowcs-s-mbstowcs-s-l?redirectedfrom=MSDN&view=msvc-170


#include <cstddef>
#include <exception>
#include <stdexcept>


#if defined(WIN32) || defined(_WIN32)

    // #include <uchar.h>

#endif



//----------------------------------------------------------------------------
namespace marty_mbs {




//----------------------------------------------------------------------------
// https://ru.wikipedia.org/wiki/UTF-8
// Если для кодирования требуется больше одного октета, то в октетах 2-4 два старших бита всегда
// устанавливаются равными 0b10 (0b10xxxxxx). Это позволяет легко отличать первый октет в потоке,
// потому что его старшие биты никогда не равны 0b10.
inline
bool isNextByteUtf8(std::uint8_t byte)
{
    const std::uint8_t nextOctetsHigh2Bits     = 0x80u;
    const std::uint8_t nextOctetsHigh2BitsMask = 0xC0u;

    auto maskedByte = byte & nextOctetsHigh2BitsMask;
    return maskedByte==nextOctetsHigh2Bits;
}

//----------------------------------------------------------------------------
inline
bool isFirstByteUtf8(std::uint8_t byte)
{
    return !isNextByteUtf8(byte);
}

//----------------------------------------------------------------------------
inline
std::size_t getCharLenUtf8(const char* utf8Str, std::size_t utf8StrLen)
{
    if (!utf8StrLen)
        return 0;

    const std::uint8_t *pBytePtr = (const std::uint8_t*)utf8Str;

    std::size_t len = 0;
    if (isFirstByteUtf8(*pBytePtr))
    {
        len++;
        pBytePtr++;
        utf8StrLen--;
    }

    while(utf8StrLen && isNextByteUtf8(*pBytePtr))
    {
        len++;
        pBytePtr++;
        utf8StrLen--;
    }

    return len;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

// https://ru.wikipedia.org/wiki/UTF-16
// https://habr.com/ru/post/544084/

inline
bool isSingleWordUtf16(std::uint16_t word)
{
    // Исключенный диапазон D800..DFFF

    const std::uint16_t mask = (std::uint16_t)0xF800u;

    auto maskedWord = word & mask;

    if (maskedWord<0xD800 || maskedWord>0xDFFF)
        return true;

    return false;
}

//----------------------------------------------------------------------------
inline
std::size_t getCharLenUtf16(const std::uint16_t* utf16Str, std::size_t utf16StrLen) // len - in std::uint16_t
{
    if (!utf16StrLen)
        return 0;

    if (isSingleWordUtf16(*utf16Str))
        return 1;

    if (utf16StrLen>1)
        return 2;

    return 1;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline
std::size_t getCharLen(const char* str, std::size_t strLen, bool bUtf = true /* else - single byte encoding */ )
{
    if (bUtf)
    {
        return getCharLenUtf8(str, strLen);
    }
    else
    {
        return 1;
    }
}

//----------------------------------------------------------------------------



#if defined(WIN32) || defined(_WIN32)

    inline
    std::size_t getCharLen(const wchar_t* str, std::size_t strLen, bool ignored = false)
    {
        MARTY_ARG_USED(ignored);
        return getCharLenUtf16((const std::uint16_t*)str, strLen); // len - in std::uint16_t
    }

#else

    // Кроме винды, вроде у всех систем wchar_t - 32 бита

    inline
    std::size_t getCharLen(const wchar_t* str, std::size_t strLen, bool ignored = false)
    {
        if (!strLen)
            return 0;
        else
            return 1;
    }


#endif



#if 0
const char* decodeUtf8Symbol(const char* utf8Str, std::size_t utf8StrLen /* in bytes */, std::uint32_t *pUtf32 = 0, std::size_t *pCharLen)
{
    // https://habr.com/ru/post/138173/

    std::uint8_t *pBytePtr = (std::uint8_t)utf8Str;

    std::size_t processedBytes = 0;

    const std::uint8_t nextOctetsHigh2Bits     = 0x80u;
    const std::uint8_t nextOctetsHigh2BitsMask = 0xC0u;


    // Ищем первый байт последовательности
    while(processedBytes!=utf8StrLen && )
    {

    }

}
#endif





} // namespace marty_mbs



