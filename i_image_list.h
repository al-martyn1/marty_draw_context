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
    int width  = 0; // xSize
    int height = 0; // ySize


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

    ImageSize operator+(const ImageSize s) const
    {
        return ImageSize{width+s.width, height+s.height};
    }

    ImageSize& operator+=(const ImageSize s)
    {
        width  += s.width ;
        height += s.height;
        return *this;
    }


}; // struct ImageSize



//----------------------------------------------------------------------------



struct ImageListImageInfo
{
    ImageSize            imageSize;
    std::string          mimeType ;
    bool                 hasAlpha = false;
    bool                 hasMask  = false;

}; // struct ImageListImageInfo


typedef const ImageListImageInfo* ImageListImageInfoConstPtr;
typedef       ImageListImageInfo* ImageListImageInfoPtr;


//----------------------------------------------------------------------------

struct IImageList
{

    virtual ~IImageList() {}



    virtual void clear() = 0;
    virtual int  size()  const = 0;
    virtual bool empty() const = 0;


    virtual bool getImageInfo( int imageIdx, ImageListImageInfo *pInfo ) const = 0;

    // Файл/данные изображения могут содержать коллекцию изображений, как разного размера (.ico), так и одинакового (.gif)

    virtual std::vector<ImageSize> getAvailSizesByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType) = 0;
    virtual std::vector<ImageSize> getAvailSizesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) = 0;

    virtual std::size_t getNumberOfImagesByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType) = 0;
    virtual std::size_t getNumberOfImagesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) = 0;

    virtual std::size_t findBestFitImageByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize requestedSize, ImageSize *pFoundSize=0) = 0;
    virtual std::size_t findBestFitImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize requestedSize, ImageSize *pFoundSize=0) = 0;

    // Возвращает индекс нового изображения в списке, или <0
    virtual int addImageByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, std::size_t imageRawIdx) = 0;
    virtual int addImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , std::size_t imageRawIdx) = 0;

    virtual int addImageFitSizeByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize requestedSize, ImageSize *pFoundSize=0) = 0;
    virtual int addImageFitSizeByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize requestedSize, ImageSize *pFoundSize=0) = 0;

    // Only for images without alpha
    virtual bool createMaskRgb(int imageIdx, std::uint8_t r, std::uint8_t g, std::uint8_t b) = 0;
    virtual bool createMaskByColor(int imageIdx, ColorRef clr) = 0;
    virtual bool createMaskByPos(int imageIdx, ImageSize maskColorPixelPos) = 0;

    virtual int addImageBandFromMultipartImageByMimeEx (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, const std::vector<std::size_t> &frameList) = 0;
    virtual int addImageBandFromMultipartImageByExtEx  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, const std::vector<std::size_t> &frameList) = 0;

    virtual int addImageBandFromMultipartImageByMime (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize) = 0;
    virtual int addImageBandFromMultipartImageByExt  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize) = 0;

    virtual int addImageBandFromMultipartImageByMimeRange (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, std::size_t firstFrameIdx, std::size_t numFrames) = 0;
    virtual int addImageBandFromMultipartImageByExtRange  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, std::size_t firstFrameIdx, std::size_t numFrames) = 0;

    virtual bool saveImageAsBmp(int imageIdx, std::vector<std::uint8_t> &bmpData) = 0;

    virtual std::string getMimeTypeByFileName(const std::string &fileName) = 0;
    virtual std::wstring getMimeTypeByFileName(const std::wstring &fileName) = 0;

    virtual int addImageBandFromImageListEx   (const IImageList *pImageList, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, const std::vector<int> &frameList) = 0;
    virtual int addImageBandFromImageList     (const IImageList *pImageList, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize) = 0;
    virtual int addImageBandFromImageListRange(const IImageList *pImageList, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, int firstFrameIdx, std::size_t numFrames) = 0;

    virtual int addImageAllFramesByMime(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, std::size_t *pNumLoadedFrames) = 0;
    virtual int addImageAllFramesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , std::size_t *pNumLoadedFrames) = 0;



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


