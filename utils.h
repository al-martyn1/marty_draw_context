#pragma once

#include "i_draw_context.h"
#include "i_image_list.h"

//----------------------------------------------------------------------------
namespace marty_draw_context {


//----------------------------------------------------------------------------


namespace utils {

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename StringType> inline
std::vector<StringType> simpleStringSplit(const StringType &str, const StringType &delim, typename StringType::size_type nSplits = -1)
{
    std::vector<StringType> res;

    typename StringType::size_type curPos  = 0;
    typename StringType::size_type prevPos = 0;
    //StringType token;
    while (res.size()!=nSplits && (curPos = str.find(delim, prevPos)) != StringType::npos)
    {
        res.emplace_back(str, prevPos, curPos-prevPos);
        prevPos = curPos+delim.size();
    }

    res.emplace_back(str, prevPos);

    return res;
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
std::vector<StringType> simpleStringSplit(const StringType &str, const typename StringType::value_type *delim, typename StringType::size_type nSplits = -1)
{
    return simpleStringSplit( str, StringType(delim), nSplits);
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
std::vector<StringType> simpleStringSplit(const StringType &str, const typename StringType::value_type delim, typename StringType::size_type nSplits = -1)
{
    typename StringType::value_type tmpDelimStr[2] = { delim, 0 };
    return simpleStringSplit( str, tmpDelimStr, nSplits);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template <typename IteratorType, typename IteratorTypeCmpWith> inline
std::size_t startsWith(IteratorType b, IteratorType e, IteratorTypeCmpWith bCmpWith, IteratorTypeCmpWith eCmpWith)
{
    std::size_t idx = 0;
    for(; b!=e && bCmpWith!=eCmpWith && *bCmpWith==*b; ++bCmpWith, ++b, ++idx)
    {
    }

    if (bCmpWith==eCmpWith) // дошли до конца искомой строки
    {
        return idx;
    }

    return 0;
}



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




//----------------------------------------------------------------------------
inline
std::vector<int> findNearestImageSizeHelperMakeSizeDistances(const std::vector<ImageSize> &sizes)
{
    std::vector<int> sizeDistances; sizeDistances.reserve(sizes.size());

    for(auto sz : sizes)
    {
        sizeDistances.emplace_back(sz.sizeDistance());
    }

    return sizeDistances;
}

//----------------------------------------------------------------------------
//TODO: !!! Пока алгоритм такой, есть говнецо, но пока пусть так

inline
std::size_t findNearestImageSize(const std::vector<ImageSize> &sizes, ImageSize requestedSize)
{
    if (sizes.empty())
    {
        return (std::size_t)-1; // not found
    }

    if (sizes.size()<2)
    {
        // есть единственное изображение в коллеции
        return 0u;
    }

    std::vector<int> sizeDistances = findNearestImageSizeHelperMakeSizeDistances(sizes);


    // Ищем приближение для скалинга вниз - те минимально больше

    int requestedSizeDistance   = requestedSize.sizeDistance();
    // double requestedSizeVhScale = requestedSize.vhScale();
    
    int          minDelta     = 32767; // Вряд ли картинки в разумное время будут больше такого размера
    std::size_t  idxMinDelta  = (std::size_t)-1;

    std::size_t idx = 0u;

    auto isQuadratImage = [](ImageSize sz) -> bool
    {
        double vhScale = sz.vhScale();
        if (vhScale>0.8 && vhScale<1.2)
        {
            return true;
        }

        return false;
    };

    // Ищем большее изображение
    {
    
        idx = 0u;
        for (; idx!=sizes.size(); ++idx)
        {
            if (requestedSize.isVertical()!=sizes[idx].isVertical())
            {
                continue; // ориентация изображения не совпадает с запрошенной
            }
    
            if (sizeDistances[idx]<requestedSizeDistance) // Размеры текущей - меньше искомых?
            {
                continue;
            }
    
            // Here distances[i]>d
    
            int dDelta = sizeDistances[idx] - requestedSizeDistance;
    
            if (minDelta>dDelta)
            {
                minDelta    = dDelta;
                idxMinDelta = idx;
            }
        }
    
        if (idxMinDelta!=(std::size_t)-1) // нашли
        {
            return idxMinDelta;
        }
    
    
        // Изображение чуть больше не найдено, попробуем поискать другую ориентацию, если у нас ширина/высота не сильно отличаются
    
        if (isQuadratImage(requestedSize)) // запрошенное изображение близко к квадратному?
        {
            idx = 0u;
            for (; idx!=sizes.size(); ++idx)
            {
                if (requestedSize.isVertical()==sizes[idx].isVertical())
                {
                    continue; // ориентация изображения совпадает с запрошенной - но эти варианты мы уже проверили
                }
    
                if (isQuadratImage(sizes[idx]))
                {
                    continue; // слишком неквадратное, не подходит
                }
        
                if (sizeDistances[idx]<requestedSizeDistance) // Размеры текущей - меньше искомых?
                {
                    continue;
                }
        
                // Here distances[i]>d
        
                int dDelta = sizeDistances[idx] - requestedSizeDistance;
        
                if (minDelta>dDelta)
                {
                    minDelta    = dDelta;
                    idxMinDelta = idx;
                }
            }
        
            if (idxMinDelta!=(std::size_t)-1) // нашли
            {
                return idxMinDelta;
            }
        
        }

    }

    // будем искать меньшее изображение для upscaling'а
    {
        idx = 0u;
        for (; idx!=sizes.size(); ++idx)
        {
            if (requestedSize.isVertical()!=sizes[idx].isVertical())
            {
                continue; // ориентация изображения не совпадает с запрошенной
            }
    
            if (sizeDistances[idx]>requestedSizeDistance) // Размеры текущей - больше искомых?
            {
                continue;
            }
    
            int dDelta = requestedSizeDistance - sizeDistances[idx];
    
            if (minDelta>dDelta)
            {
                minDelta    = dDelta;
                idxMinDelta = idx;
            }
        }
    
        if (idxMinDelta!=(std::size_t)-1) // нашли
        {
            return idxMinDelta;
        }
    
    
        // Изображение чуть меньше не найдено, попробуем поискать другую ориентацию, если у нас ширина/высота не сильно отличаются
    
        if (isQuadratImage(requestedSize)) // запрошенное изображение близко к квадратному?
        {
            idx = 0u;
            for (; idx!=sizes.size(); ++idx)
            {
                if (requestedSize.isVertical()==sizes[idx].isVertical())
                {
                    continue; // ориентация изображения совпадает с запрошенной - но эти варианты мы уже проверили
                }
    
                if (isQuadratImage(sizes[idx]))
                {
                    continue; // слишком неквадратное, не подходит
                }
        
                if (sizeDistances[idx]>requestedSizeDistance) // Размеры текущей - больше искомых?
                {
                    continue;
                }
        
                int dDelta = requestedSizeDistance - sizeDistances[idx];
        
                if (minDelta<dDelta)
                {
                    minDelta    = dDelta;
                    idxMinDelta = idx;
                }
            }
        
            if (idxMinDelta!=(std::size_t)-1) // нашли
            {
                return idxMinDelta;
            }
        
        }
    
    
    }

    // Ничего не найдено, берём первый попавшийся размер

    return 0u;

}


} // namespace utils


//----------------------------------------------------------------------------

} // namespace marty_draw_context

