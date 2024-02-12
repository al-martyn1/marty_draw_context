
#include <exception>
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <memory>
#include <utility>

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

};
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

    virtual std::size_t findBestFitImageByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize *pFoundSize=0) = 0;
    virtual std::size_t findBestFitImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize *pFoundSize=0) = 0;

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


