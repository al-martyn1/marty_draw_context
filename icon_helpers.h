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

// marty_draw_context::icon_helpers::

namespace marty_draw_context{
namespace icon_helpers {


// https://learn.microsoft.com/en-us/previous-versions/ms997538(v=msdn.10)

template<typename T> inline
void convertEndiannessToHost(T &t, Endianness srcEndianness)
{
    marty_draw_context::endianness::convertEndiannessToHost((std::uint8_t*)&t, sizeof(T), srcEndianness);
}

template<typename T> inline
void convertEndiannessFromHost(T &t, Endianness srcEndianness)
{
    marty_draw_context::endianness::convertEndiannessFromHost((std::uint8_t*)&t, sizeof(T), srcEndianness);
}

#include "pushpack1.h"
struct IconDirectoryEntry
{
    std::uint8_t         bWidth;          // Width, in pixels, of the image
    std::uint8_t         bHeight;         // Height, in pixels, of the image
    std::uint8_t         bColorCount;     // Number of colors in image (0 if >=8bpp)
    std::uint8_t         bReserved;       // Reserved ( must be 0)
    std::uint16_t        wPlanes;         // Color Planes
    std::uint16_t        wBitCount;       // Bits per pixel
    std::uint32_t        dwBytesInRes;    // How many bytes in this resource?
    std::uint32_t        dwImageOffset;   // Where in the file is this image?

    void convertEndiannessToHost()
    {
        marty_draw_context::icon_helpers::convertEndiannessToHost(wPlanes      , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessToHost(wBitCount    , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessToHost(dwBytesInRes , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessToHost(dwImageOffset, Endianness::littleEndian);
    }

    void convertEndiannessFromHost()
    {
        marty_draw_context::icon_helpers::convertEndiannessFromHost(wPlanes      , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessFromHost(wBitCount    , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessFromHost(dwBytesInRes , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessFromHost(dwImageOffset, Endianness::littleEndian);
    }

};
#include "packpop.h"


#include "pushpack1.h"
struct IconDirectoryHeader
{
    std::uint16_t        idReserved;   // Reserved (must be 0)
    std::uint16_t        idType    ;       // Resource Type (1 for icons)
    std::uint16_t        idCount   ;      // How many images?

    void convertEndiannessToHost()
    {
        marty_draw_context::icon_helpers::convertEndiannessToHost(idReserved, Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessToHost(idType    , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessToHost(idCount   , Endianness::littleEndian);
    }

    void convertEndiannessFromHost()
    {
        marty_draw_context::icon_helpers::convertEndiannessFromHost(idReserved, Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessFromHost(idType    , Endianness::littleEndian);
        marty_draw_context::icon_helpers::convertEndiannessFromHost(idCount   , Endianness::littleEndian);
    }

};
#include "packpop.h"


#include "pushpack1.h"
struct IconDirectory
{
    // IconDirectoryHeader
    std::uint16_t        idReserved;   // Reserved (must be 0)
    std::uint16_t        idType;       // Resource Type (1 for icons)
    std::uint16_t        idCount;      // How many images?

    IconDirectoryEntry   idEntries[1]; // An entry for each image (idCount of 'em)
};
#include "packpop.h"


// inline
// bool extractIconDirectoryEntries(const std::vector<std::uint8_t> &iconsRawData, std::vector<IconDirectoryEntry> &entries)
// {
//     if (iconsRawData.size()<sizeof(IconDirectoryHeader))
//     {
//         return false;
//     }
//  
//     IconDirectoryHeader hdr;
//     std::memcpy( (void*)&hdr, (const void*)&iconsRawData[0], sizeof(hdr));
//  
//  
// }

inline
bool findIconInDirectory( const std::vector<std::uint8_t> &iconsDirectoryRawData
                        , int xSize
                        , int ySize
                        , std::size_t &offset
                        , std::size_t &size
                        )
{
    if (iconsDirectoryRawData.size()<sizeof(IconDirectoryHeader))
    {
        return false;
    }
 
    IconDirectoryHeader hdr;
    std::memcpy( (void*)&hdr, (const void*)&iconsDirectoryRawData[0], sizeof(hdr));

    hdr.convertEndiannessToHost();

    if (hdr.idReserved!=0u)
    {
        return false;
    }

    if (hdr.idType!=1u) // Resource Type (1 for icons)
    {
        return false;
    }

    // hdr.idCount - max
    std::size_t idCount = (std::size_t)hdr.idCount;

    std::size_t entryBaseOffset = sizeof(hdr);
    std::size_t entrySize       = sizeof(IconDirectoryEntry);

    std::vector<IconDirectoryEntry> vecEntries;
    std::vector<int>                distances;
    //std::size_t numEntries = 0;
    std::size_t i = 0;

    for(; i!=idCount; ++i)
    {
        std::size_t entryOffset = entryBaseOffset+entrySize*i;

        // Смещение за пределами вектора?
        if (entryOffset>=iconsDirectoryRawData.size())
        {
            break;
        }

        // Последний байт entry за пределами вектора?
        if ((entryOffset+entrySize)>iconsDirectoryRawData.size())
        {
            break;
        }

        const IconDirectoryEntry *pEntry = (const IconDirectoryEntry*)&iconsDirectoryRawData[entryOffset];

        IconDirectoryEntry entry;
        std::memcpy( (void*)&entry, (const void*)pEntry, sizeof(entry));
        entry.convertEndiannessToHost();

        if ((std::size_t)(entry.dwImageOffset)>=iconsDirectoryRawData.size())
        {
           break;
        }

        if ((std::size_t)(entry.dwImageOffset+entry.dwBytesInRes)>iconsDirectoryRawData.size())
        {
           break;
        }

        vecEntries.emplace_back(entry);

        int d = (int)(0.5+std::sqrt((double)(entry.bWidth*entry.bWidth + entry.bHeight*entry.bHeight)));
        distances.emplace_back(d);

    }

    if (vecEntries.empty())
    {
        return false;
    }

    // Размер не задан - берем первую попавшуюся
    if (!xSize || !ySize)
    {
        offset = vecEntries[0].dwImageOffset;
        size   = vecEntries[0].dwBytesInRes;
        return true;
    }

    // Ищем точное соответстие заданному размеру, заодно

    // А если точного нет, надо искать что-то побольше, но минимально отличающееся по размеру.
    // А если большего нет, то ищем меньшее

    // Считаем дистанцию по размеру картинки, как корень из суммы квадратов?

    for(i=0; i!=vecEntries.size(); ++i)
    {
        if (vecEntries[i].bWidth==xSize && vecEntries[i].bHeight==ySize)
        {
            offset = vecEntries[i].dwImageOffset;
            size   = vecEntries[i].dwBytesInRes;
            return true;
        }
    }

    int          minDelta     = 32767; // Вряд ли иконки в разумное время будут больше такого размера
    std::size_t  idxFoundDelta  = (std::size_t)-1;

    int d = (int)(0.5+std::sqrt((double)(xSize*xSize + ySize*ySize)));

    // Ищем что побольше
    for (i=0; i!=vecEntries.size(); ++i)
    {
        if (distances[i]<d) // Размеры текущей - меньше искомых?
        {
            continue;
        }

        // Here distances[i]>d

        int dDelta = distances[i] - d;

        if (minDelta>dDelta)
        {
            minDelta    = dDelta;
            idxFoundDelta = i;
        }
    }

    if (idxFoundDelta!=(std::size_t)-1)
    {
        offset = vecEntries[idxFoundDelta].dwImageOffset;
        size   = vecEntries[idxFoundDelta].dwBytesInRes;
        return true;
    }

    // Ищем что поменьше
    for (i=0; i!=vecEntries.size(); ++i)
    {
        if (distances[i]>d) // Размеры текущей - больше искомых?
        {
            continue;
        }

        // Here distances[i]>d

        int dDelta = d - distances[i];

        if (minDelta<dDelta)
        {
            minDelta    = dDelta;
            idxFoundDelta = i;
        }
    }

    if (idxFoundDelta!=(std::size_t)-1)
    {
        offset = vecEntries[idxFoundDelta].dwImageOffset;
        size   = vecEntries[idxFoundDelta].dwBytesInRes;
        return true;
    }


    offset = vecEntries[0].dwImageOffset;
    size   = vecEntries[0].dwBytesInRes;
    return true;

}


#if defined(WIN32) || defined(_WIN32)

inline
HICON createIconFromIconDirectory( const std::vector<std::uint8_t> &iconsDirectoryRawData
                                 , int xSize
                                 , int ySize
                                 , DWORD dwVer = 0x30000 // 0x20000
                                 )
{
    std::size_t offset = 0;
    std::size_t size   = 0;

    if (!findIconInDirectory(iconsDirectoryRawData, xSize, ySize, offset, size))
    {
        return (HICON)0;
    }

    std::vector<DWORD> dwAlignedData;
    dwAlignedData.resize(size/4+1, 0);
    std::memcpy( (void*)&dwAlignedData[0], (const void*)&iconsDirectoryRawData[offset], size);

    return CreateIconFromResource( (PBYTE)&dwAlignedData[0], (DWORD)size
                                 , TRUE // fIcon
                                 , dwVer
                                 );
}

#endif


} // namespace icon_helpers
} // namespace marty_draw_context{

