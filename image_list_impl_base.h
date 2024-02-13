
#include "i_image_list.h"
#include "mime.h"


namespace marty_draw_context {


struct ImageListImplBase : public IImageList
{


    std::vector<ImageSize> getAvailSizesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) override
    {
        return getAvailSizesByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext));
    }

    std::size_t getNumberOfImagesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) override
    {
        return getNumberOfImagesByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext));
    }

    std::size_t findBestFitImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, ImageSize requestedSize, ImageSize *pFoundSize=0) override
    {
        return findBestFitImageByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext), requestedSize, pFoundSize);
    }

    virtual int addImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, std::size_t imageIdx) override
    {
        return addImageByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext), imageIdx);
    }

}; // struct ImageListImplBase




} // namespace marty_draw_context

