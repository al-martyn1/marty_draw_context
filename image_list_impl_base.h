#pragma once

#include "i_image_list.h"
//
#include "mime.h"
//
#include "umba/filename.h"
#include "umba/utf8.h"
//

namespace marty_draw_context {


struct ImageListImplBase : public IImageList
{

    virtual std::string getMimeTypeByFileName(const std::string &fileName) override
    {
        return marty_draw_context::mime::getMimeTypeByExt(umba::filename::getExt(fileName));
    }

    virtual std::wstring getMimeTypeByFileName(const std::wstring &fileName) override
    {
        return umba::fromUtf8(marty_draw_context::mime::getMimeTypeByExt(umba::toUtf8(umba::filename::getExt(fileName))));
    }

    virtual std::vector<ImageSize> getAvailSizesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) override
    {
        return getAvailSizesByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext));
    }

    virtual std::size_t getNumberOfImagesByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     ) override
    {
        return getNumberOfImagesByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext));
    }

    virtual std::size_t findBestFitImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, ImageSize requestedSize, ImageSize *pFoundSize=0) override
    {
        return findBestFitImageByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext), requestedSize, pFoundSize);
    }

    virtual int addImageByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, std::size_t imageIdx) override
    {
        return addImageByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext), imageIdx);
    }

    virtual int addImageFitSizeByExt (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, ImageSize requestedSize, ImageSize *pFoundSize=0) override
    {
        return addImageFitSizeByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext), requestedSize, pFoundSize);
    }


    virtual int addImageBandFromMultipartImageByExtEx(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, const std::vector<std::size_t> &frameList) override
    {
        return addImageBandFromMultipartImageByMimeEx(imgDirectoryRawData, mime::getMimeTypeByExt(ext), frameMinSize, flags, pFrameSize, frameList);
    }

    virtual int addImageBandFromMultipartImageByExt  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize) override
    {
        return addImageBandFromMultipartImageByMime(imgDirectoryRawData, mime::getMimeTypeByExt(ext), frameMinSize, flags, pFrameSize);
    }

    virtual int addImageBandFromMultipartImageByExtRange(const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, std::size_t firstFrameIdx, std::size_t numFrames) override
    {
        return addImageBandFromMultipartImageByMimeRange(imgDirectoryRawData, mime::getMimeTypeByExt(ext), frameMinSize, flags, pFrameSize, firstFrameIdx, numFrames);
    }


}; // struct ImageListImplBase




} // namespace marty_draw_context

