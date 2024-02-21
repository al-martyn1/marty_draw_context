#pragma once

#include "marty_draw_context/i_draw_context.h"


namespace marty_draw_context{

namespace endianness {


inline
Endianness getHostEndianness()
{
#if defined(MARTY_IDC_ARCH_LITTLE_ENDIAN)

    return Endianness::littleEndian;

#else

    return Endianness::bigEndian;

#endif
}

//----------------------------------------------------------------------------
inline
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
inline
std::uint8_t* convertEndiannessToHost  (std::uint8_t *pData, std::size_t dataSize, Endianness srcEndianness)
{
    if (getHostEndianness()!=srcEndianness)
    {
        swapByteOrder(pData, dataSize);
    }

    return pData;
}

//----------------------------------------------------------------------------
inline
std::uint8_t* convertEndiannessFromHost(std::uint8_t *pData, std::size_t dataSize, Endianness dstEndianness)
{
    if (getHostEndianness()!=dstEndianness)
    {
        swapByteOrder(pData, dataSize);
    }

    return pData;
}


} // namespace endianness

} // namespace marty_draw_context{

