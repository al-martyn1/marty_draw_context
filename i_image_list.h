#pragma once

#include <exception>
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <memory>
#include <utility>
#include <sstream>

#include "marty_decimal/marty_decimal.h"

#include "dc_debug/uw_log.h"

#include "draw_context_types.h"


// #include "mimes.h"






namespace marty_draw_context {


//----------------------------------------------------------------------------
struct ImageSize
{
    int width ; // xSize
    int height; // ySize


    int sizeDistance() const
    {
        return (int)(0.5+std::sqrt((double)(width*width + height*height)));
    }

    bool isVertical() const
    {
        return width > height
               ? false  // horizontal - ширина больше высоты - горизонтальная картинка
               : true   // vertiacal
               ;
    }

    double vhScale() const // коэффициент вертикальности, >1 - вертикально, <1 - горизонтально
    {
        if (width==0)
        {
            return (double)1.0;
        }

        return (double)height / (double)width;
    }

    std::string toString() const
    {
        std::ostringstream oss;
        oss << width << "," << height;
        return oss.str();
    }


}; // struct ImageSize

//----------------------------------------------------------------------------





//----------------------------------------------------------------------------

struct IImageList
{

    virtual ~IImageList() {}


    // Файл/данные изображения могут содержать коллекцию изображений, как разного размера (.ico), так и одинакового (.gif)

    virtual std::vector<ImageSize> getAvailSizesByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType) = 0;
    virtual std::vector<ImageSize> getAvailSizesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) = 0;

    virtual std::size_t getNumberOfImagesByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType) = 0;
    virtual std::size_t getNumberOfImagesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) = 0;

    virtual std::size_t findBestFitImageByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize requestedSize, ImageSize *pFoundSize=0) = 0;
    virtual std::size_t findBestFitImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize requestedSize, ImageSize *pFoundSize=0) = 0;

    // Возвращает индекс нового изображения в списке, или <0
    virtual int addImageByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, std::size_t imageIdx) = 0;
    virtual int addImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , std::size_t imageIdx) = 0;


}; // struct IImageList


#if 0

        , { ".gif"    , "image/gif"     }
        , { ".png"    , "image/png"     }
        , { ".jpg"    , "image/jpeg"    }
        , { ".ico"    , "image/x-icon"  }
        , { ".svg"    , "image/svg+xml" }

        , { ".jpeg"   , "image/jpeg"    }
        , { ".jpe"    , "image/jpeg"    }
        , { ".bmp"    , "image/bmp"     }
        , { ".tiff"   , "image/tiff"    }
        , { ".tif"    , "image/tiff"    }
        , { ".pcx"    , "image/x-pcx"   }
        , { ".djvu"   , "image/vnd.djvu"}
        , { ".djv"    , "image/vnd.djvu"}
        , { ".wbmp"   , "image/vnd.wap.wbmp"}
        , { ".xbm"    , "image/x-xbitmap"}
        , { ".xpm"    , "image/x-xpixmap"}


#endif

} // namespace marty_draw_context


