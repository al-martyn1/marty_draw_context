#pragma once

#include "i_draw_context.h"

//----------------------------------------------------------------------------
namespace marty_draw_context {


//----------------------------------------------------------------------------


namespace utils {


//----------------------------------------------------------------------------
Endianness getHostEndianness()
{
#if defined(UMBA_ARCH_LITTLE_ENDIAN)

    return Endianness::littleEndian;

#else

    return Endianness::bigEndian;

#endif
}
//----------------------------------------------------------------------------

std::uint8_t* swapByteOrder(std::uint8_t *pData, std::size_t dataSize)
{
    if (dataSize<2)
    {
        return pData; // nothing to swap
    }

    std::uint8_t *pRes = pData;

    std::uint8_t *pLastData = pData + (std::intptr_t)(dataSize - 1);

    const std::size_t iMax = dataSize/2;
    for(std::size_t i=0u; i!=iMax /* pData<pLastData */ ; ++pData, --pLastData)
    {
        std::swap(*pData, *pLastData);
    }

    return pRes;
}

//----------------------------------------------------------------------------
std::uint8_t* convertEndiannessToHost  (std::uint8_t *pData, std::size_t dataSize, Endianness srcEndianness)
{
    if (getHostEndianness()!=srcEndianness)
    {
        swapByteOrder(pData, dataSize);
    }

    return pData;
}

//----------------------------------------------------------------------------
std::uint8_t* convertEndiannessFromHost(std::uint8_t *pData, std::size_t dataSize, Endianness dstEndianness)
{
    if (getHostEndianness()!=dstEndianness)
    {
        swapByteOrder(pData, dataSize);
    }

    return pData;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template<typename T> inline
std::enable_if_t<std::is_integral<T>::value || std::is_enum<T>::value, void> convertEndiannessToDc(const IDrawContext *pDc, T &t, Endianness srcEndianness)
{
    pDc->convertEndiannessToHost  ((std::uint8_t*)&t, sizeof(T), srcEndianness);
}

//------------------------------
template<typename T> inline
std::enable_if_t<std::is_integral<T>::value || std::is_enum<T>::value, void> convertEndiannessToHost(T &t, Endianness srcEndianness)
{
    convertEndiannessToHost  ((std::uint8_t*)&t, sizeof(T), srcEndianness);
}

//----------------------------------------------------------------------------
template<typename T> inline
std::enable_if_t<std::is_integral<T>::value || std::is_enum<T>::value, void> convertEndiannessFromDc(const IDrawContext *pDc, T &t, Endianness dstEndianness)
{
    pDc->convertEndiannessFromHost((std::uint8_t*)&t, sizeof(T), dstEndianness);
}

//------------------------------
template<typename T> inline
std::enable_if_t<std::is_integral<T>::value || std::is_enum<T>::value, void> convertEndiannessFromHost(T &t, Endianness dstEndianness)
{
    convertEndiannessFromHost((std::uint8_t*)&t, sizeof(T), dstEndianness);
}

//----------------------------------------------------------------------------
template<typename T> inline
const std::uint8_t* copyFromRawBytesEx( T &t, const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
{
    const auto sizeofT = sizeof(T);

    if (rawDataRestSize<sizeofT)
    {
        throw std::runtime_error("marty_draw_context::copyFromRawBytesEx: Not enough raw data to copy from");
    }

    std::memcpy( (void*)&t, (const void*)pRawData, sizeofT );

    rawDataRestSize -= sizeofT;
    pRawData        += sizeofT;

    return pRawData;
}

//----------------------------------------------------------------------------
template<typename T> inline
void copyFromRawBytes( T &t, const std::uint8_t* pRawData)
{
    const auto sizeofT = sizeof(T);
    std::memcpy( (void*)&t, (const void*)pRawData, sizeofT );
}

//----------------------------------------------------------------------------



} // namespace utils


//----------------------------------------------------------------------------

} // namespace marty_draw_context

