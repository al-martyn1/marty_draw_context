#pragma once


#include "marty_draw_context/i_draw_context.h"
//#include "dc_utility_endianness.h"
#include "utils.h"

//
#include <cstdint>
#include <cstring>
#include <cmath>
#include <string>
#include <memory>

#if defined(WIN32) || defined(_WIN32)

    #include <windows.h>

#endif

// marty_draw_context::bitmap_helpers::

namespace marty_draw_context{
namespace bitmap_helpers {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename T> inline
void convertEndiannessToHost(T &t, Endianness srcEndianness)
{
    endianness::convertEndiannessToHost((std::uint8_t*)&t, sizeof(T), srcEndianness);
}

template<typename T> inline
void convertEndiannessFromHost(T &t, Endianness srcEndianness)
{
    endianness::convertEndiannessFromHost((std::uint8_t*)&t, sizeof(T), srcEndianness);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
// See https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
#include "pushpack1.h"
struct BitmapFileHeader
{
    std::uint16_t    bfType     ; // The file type; must be 0x4d42 (the ASCII string "BM").
    std::uint32_t    bfSize     ; // The size, in bytes, of the bitmap file.
    std::uint16_t    bfReserved1; // Reserved; must be zero.
    std::uint16_t    bfReserved2; // Reserved; must be zero.
    std::uint32_t    bfOffBits  ; // The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.

    void convertEndiannessToHost()
    {
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(bfType     , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(bfSize     , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(bfReserved1, Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(bfReserved2, Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(bfOffBits  , Endianness::littleEndian);
    }

    void convertEndiannessFromHost()
    {
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(bfType     , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(bfSize     , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(bfReserved1, Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(bfReserved2, Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(bfOffBits  , Endianness::littleEndian);
    }

    bool extractFromRawData(const std::vector<std::uint8_t> &imgRawData, std::size_t offset)
    {
        if (offset>=imgRawData.size())
        {
            return false;
        }

        std::size_t size = sizeof(*this);

        if ((offset+size)>imgRawData.size())
        {
            return false;
        }

        std::memcpy( (void*)this, (const void*)&imgRawData[offset], size);

        convertEndiannessToHost();

        return true;
    }

}; // struct BitmapFileHeader
#include "packpop.h"
//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// See https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfoheader
#include "pushpack1.h"
struct BitmapInfoHeader
{
    std::uint32_t    biSize         ;  
    std::int32_t     biWidth        ;  // Specifies the width of the bitmap, in pixels.
    std::int32_t     biHeight       ;  // Specifies the height of the bitmap, in pixels. For uncompressed RGB bitmaps, if biHeight is positive, the bitmap is a bottom-up DIB with the origin at the lower left corner. If biHeight is negative, the bitmap is a top-down DIB with the origin at the upper left corner.
    std::uint16_t    biPlanes       ;  // Specifies the number of planes for the target device. This value must be set to 1.
    std::uint16_t    biBitCount     ;  // Specifies the number of bits per pixel (bpp).
    std::uint32_t    biCompression  ;  // 
    std::uint32_t    biSizeImage    ;  // Specifies the size, in bytes, of the image.
    std::uint32_t    biXPelsPerMeter;  // Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap.
    std::uint32_t    biYPelsPerMeter;  // Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap.
    std::uint32_t    biClrUsed      ;  // Specifies the number of color indices in the color table that are actually used by the bitmap.
    std::uint32_t    biClrImportant ;  // Specifies the number of color indices that are considered important for displaying the bitmap.

    void convertEndiannessToHost()
    {
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biSize          , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biWidth         , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biHeight        , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biPlanes        , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biBitCount      , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biCompression   , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biSizeImage     , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biXPelsPerMeter , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biYPelsPerMeter , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biClrUsed       , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessToHost(biClrImportant  , Endianness::littleEndian);
    }

    void convertEndiannessFromHost()
    {
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biSize          , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biWidth         , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biHeight        , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biPlanes        , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biBitCount      , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biCompression   , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biSizeImage     , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biXPelsPerMeter , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biYPelsPerMeter , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biClrUsed       , Endianness::littleEndian);
        marty_draw_context::bitmap_helpers::convertEndiannessFromHost(biClrImportant  , Endianness::littleEndian);
    }
    
    bool extractFromRawData(const std::vector<std::uint8_t> &imgRawData, std::size_t offset)
    {
        if (offset>=imgRawData.size())
        {
            return false;
        }

        std::size_t size = sizeof(*this);

        if ((offset+size)>imgRawData.size())
        {
            return false;
        }

        std::memcpy( (void*)this, (const void*)&imgRawData[offset], size);

        convertEndiannessToHost();

        return true;
    }

}; // struct BitmapInfoHeader
#include "packpop.h"






//----------------------------------------------------------------------------
// See https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapinfo
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapv4header
// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapv5header





} // namespace bitmap_helpers {
} // namespace marty_draw_context{
