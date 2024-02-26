#pragma once


namespace marty_draw_context {
namespace simplesquirrel {


#if defined(MDC_USE_DOTNUT)

struct ImageListWrapper : public dotNut::simplesquirrel::ObjectBase
{
    static const inline std::string        className = "ImageList";

    typedef dotNut::simplesquirrel::ObjectBase  ObjectBase;

    std::shared_ptr<marty_draw_context::IImageList> m_pImgList;

    ImageListWrapper(HSQUIRRELVM hVm) : ObjectBase(hVm), m_pImgList(marty_draw_context::createSharedImageList()) {}
    ImageListWrapper(HSQUIRRELVM hVm, std::shared_ptr<marty_draw_context::IImageList> pList) : ObjectBase(hVm), m_pImgList(pList) {}

    ImageListWrapper() = delete;
    ImageListWrapper(const ImageListWrapper &) = default;
    ImageListWrapper& operator=(const ImageListWrapper &) = default;
    ImageListWrapper(ImageListWrapper &&) = default;
    ImageListWrapper& operator=(ImageListWrapper &&) = default;


    bool checkPtr(const char* methodName) const
    {
        return checkPtrImpl< std::shared_ptr<marty_draw_context::IImageList> >(m_pImgList, methodName);
    }

    marty_draw_context::IImageList* getCheckedPtr(const char* methodName) const
    {
        return getCheckedPtrImpl<marty_draw_context::IImageList, std::shared_ptr<marty_draw_context::IImageList> >(m_pImgList, methodName);
    }

    bool isSet() const
    {
        return checkPtr("");
    }

    void clear()
    {
        getCheckedPtr("clear")->clear();
    }

    int  size() const
    {
        return getCheckedPtr("size")->size();
    }

    bool empty() const
    {
        return getCheckedPtr("")->empty();
    }


    marty_draw_context::ImageListImageInfo getImageInfo(int imageIdx) const
    {
        marty_draw_context::ImageListImageInfo info;
        getCheckedPtr("getImageInfo")->getImageInfo(imageIdx, &info);
        return info;
    }


    ssq::Array getAvailSizesByMime(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring mimeType) const
    {
        std::string strMime = marty_simplesquirrel::fromSqStringToUtf8(mimeType);

        std::vector<marty_draw_context::ImageSize> sizes = getCheckedPtr("getAvailSizesByMime")->getAvailSizesByMime(binData.data, strMime);

        ssq::Array res = ssq::Array(getHandle());

        for(auto s: sizes)
        {
            res.push(s);
        }

        return res;
    }

    ssq::Array getAvailSizesByExt(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring ext) const
    {
        std::string strExt = marty_simplesquirrel::fromSqStringToUtf8(ext);

        std::vector<marty_draw_context::ImageSize> sizes = getCheckedPtr("getAvailSizesByExt")->getAvailSizesByExt(binData.data, strExt);

        ssq::Array res = ssq::Array(getHandle());

        for(auto s: sizes)
        {
            res.push(s);
        }

        return res;
    }


    int getNumberOfImagesByMime(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring mimeType) const
    {
        std::string strMime = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        return (int)getCheckedPtr("getNumberOfImagesByMime")->getNumberOfImagesByMime(binData.data, strMime);
    }

    int getNumberOfImagesByExt(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring ext) const
    {
        std::string strExt = marty_simplesquirrel::fromSqStringToUtf8(ext);
        return (int)getCheckedPtr("getNumberOfImagesByExt")->getNumberOfImagesByExt(binData.data, strExt);
    }


    int findBestFitImageByMime(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring mimeType, marty_draw_context::ImageSize requestedSize) const
    {
        std::string strMime = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        return (int)getCheckedPtr("findBestFitImageByMime")->findBestFitImageByMime(binData.data, strMime, requestedSize, 0);
    }

    int findBestFitImageByExt(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring ext, marty_draw_context::ImageSize requestedSize) const
    {
        std::string strExt = marty_simplesquirrel::fromSqStringToUtf8(ext);
        return (int)getCheckedPtr("findBestFitImageByExt")->findBestFitImageByMime(binData.data, strExt, requestedSize, 0);
    }


    marty_draw_context::ImageSize findBestFitImageByMimeGetFoundSize(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring mimeType, marty_draw_context::ImageSize requestedSize) const
    {
        std::string strMime = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        marty_draw_context::ImageSize foundSize;
        getCheckedPtr("findBestFitImageByMimeGetFoundSize")->findBestFitImageByMime(binData.data, strMime, requestedSize, &foundSize);
        return foundSize;
    }

    marty_draw_context::ImageSize findBestFitImageByExtGetFoundSize(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring ext, marty_draw_context::ImageSize requestedSize) const
    {
        std::string strExt = marty_simplesquirrel::fromSqStringToUtf8(ext);
        marty_draw_context::ImageSize foundSize;
        getCheckedPtr("findBestFitImageByExtGetFoundSize")->findBestFitImageByMime(binData.data, strExt, requestedSize, &foundSize);
        return foundSize;
    }

    int addImageByMime(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring mimeType, int imageRawIdx)
    {
        std::string strMime = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        return getCheckedPtr("addImageByMime")->addImageByMime(binData.data, strMime, (std::size_t )imageRawIdx);
    }

    int addImageByExt(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring ext, int imageRawIdx)
    {
        std::string strExt = marty_simplesquirrel::fromSqStringToUtf8(ext);
        return getCheckedPtr("addImageByExt")->addImageByExt(binData.data, strExt, (std::size_t )imageRawIdx);
    }

    int addImageFitSizeByMime(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring mimeType, marty_draw_context::ImageSize requestedSize)
    {
        std::string strMime = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        return getCheckedPtr("addImageFitSizeByMime")->addImageFitSizeByMime(binData.data, strMime, requestedSize, 0);
    }

    int addImageFitSizeByExt(dotNut::simplesquirrel::BinaryData binData, ssq::sqstring ext, marty_draw_context::ImageSize requestedSize)
    {
        std::string strExt = marty_simplesquirrel::fromSqStringToUtf8(ext);
        return getCheckedPtr("addImageFitSizeByMime")->addImageFitSizeByMime(binData.data, strExt, requestedSize, 0);
    }

    //bool createMaskRgb(int imageIdx, std::uint8_t r, std::uint8_t g, std::uint8_t b) = 0;
    bool createMaskByColor(int imageIdx, DrawingColor clr)
    {
        return getCheckedPtr("createMaskByColor")->createMaskByColor(imageIdx, clr);
    }

    bool createMaskByPos(int imageIdx, marty_draw_context::ImageSize maskColorPixelPos)
    {
        return getCheckedPtr("createMaskByPos")->createMaskByPos(imageIdx, maskColorPixelPos);
    }

    dotNut::simplesquirrel::BinaryData saveImageAsBmp(int imageIdx) const
    {
        dotNut::simplesquirrel::BinaryData bmpData(getHandle());
        if (!getCheckedPtr("saveImageAsBmp")->saveImageAsBmp(imageIdx, bmpData.data))
        {
            bmpData.data.clear();
        }

        return bmpData;
    }

    // std::string strType = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
    // std::string strType = marty_simplesquirrel::fromSqStringToUtf8(ext);
    // getCheckedPtr("")->

    AddImageBandResult addImageBandFromMultipartImageByMime( dotNut::simplesquirrel::BinaryData imageData, ssq::sqstring mimeType, ImageSize frameMinSize, int flags_)
    {
        std::string strType = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        auto flags = (ImgListBandFlags)flags_;
        AddImageBandResult res;
        res.verticalBand = (flags & ImgListBandFlags::verticalBand)!=0;
        res.imageId = getCheckedPtr("addImageBandFromMultipartImageByMime")->addImageBandFromMultipartImageByMime(imageData.data, strType, frameMinSize, (ImgListBandFlags)flags, &res.frameSize);
        return res;
    }

    AddImageBandResult addImageBandFromMultipartImageByExt( dotNut::simplesquirrel::BinaryData imageData, ssq::sqstring ext, ImageSize frameMinSize, int flags_)
    {
        std::string strType = marty_simplesquirrel::fromSqStringToUtf8(ext);
        auto flags = (ImgListBandFlags)flags_;
        AddImageBandResult res;
        res.verticalBand = (flags & ImgListBandFlags::verticalBand)!=0;
        res.imageId = getCheckedPtr("addImageBandFromMultipartImageByExt")->addImageBandFromMultipartImageByExt(imageData.data, strType, frameMinSize, (ImgListBandFlags)flags, &res.frameSize);
        return res;
    }

    AddImageBandResult addImageBandFromMultipartImageByMimeRange( dotNut::simplesquirrel::BinaryData imageData, ssq::sqstring mimeType, ImageSize frameMinSize, int flags_, int firstFrameIdx, int numFrames)
    {
        std::string strType = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        auto flags = (ImgListBandFlags)flags_;
        AddImageBandResult res;
        res.verticalBand = (flags & ImgListBandFlags::verticalBand)!=0;
        res.imageId = getCheckedPtr("addImageBandFromMultipartImageByMimeRange")->addImageBandFromMultipartImageByMimeRange(imageData.data, strType, frameMinSize, (ImgListBandFlags)flags, &res.frameSize, (std::size_t)firstFrameIdx, (std::size_t)numFrames);
        return res;
    }

    AddImageBandResult addImageBandFromMultipartImageByExtRange( dotNut::simplesquirrel::BinaryData imageData, ssq::sqstring ext, ImageSize frameMinSize, int flags_, int firstFrameIdx, int numFrames)
    {
        std::string strType = marty_simplesquirrel::fromSqStringToUtf8(ext);
        auto flags = (ImgListBandFlags)flags_;
        AddImageBandResult res;
        res.verticalBand = (flags & ImgListBandFlags::verticalBand)!=0;
        res.imageId = getCheckedPtr("addImageBandFromMultipartImageByExtRange")->addImageBandFromMultipartImageByExtRange(imageData.data, strType, frameMinSize, (ImgListBandFlags)flags, &res.frameSize, (std::size_t)firstFrameIdx, (std::size_t)numFrames);
        return res;
    }

    AddImageBandResult addImageBandFromMultipartImageByMimeEx( dotNut::simplesquirrel::BinaryData imageData, ssq::sqstring mimeType, ImageSize frameMinSize, int flags_, ssq::Object frames_)
    {
        std::vector<std::size_t> frames = marty_simplesquirrel::fromArrayObjectToVectorConvertEx<std::size_t,int>(frames_, _SC("frames"), false);
        std::string strType = marty_simplesquirrel::fromSqStringToUtf8(mimeType);
        auto flags = (ImgListBandFlags)flags_;
        AddImageBandResult res;
        res.verticalBand = (flags & ImgListBandFlags::verticalBand)!=0;
        res.imageId = getCheckedPtr("addImageBandFromMultipartImageByMimeEx")->addImageBandFromMultipartImageByMimeEx(imageData.data, strType, frameMinSize, (ImgListBandFlags)flags, &res.frameSize, frames);
        return res;
    }

    AddImageBandResult addImageBandFromMultipartImageByExtEx( dotNut::simplesquirrel::BinaryData imageData, ssq::sqstring ext, ImageSize frameMinSize, int flags_, ssq::Object frames_)
    {
        std::vector<std::size_t> frames = marty_simplesquirrel::fromArrayObjectToVectorConvertEx<std::size_t,int>(frames_, _SC("frames"), false);
        std::string strType = marty_simplesquirrel::fromSqStringToUtf8(ext);
        auto flags = (ImgListBandFlags)flags_;
        AddImageBandResult res;
        res.verticalBand = (flags & ImgListBandFlags::verticalBand)!=0;
        res.imageId = getCheckedPtr("addImageBandFromMultipartImageByExtEx")->addImageBandFromMultipartImageByExtEx(imageData.data, strType, frameMinSize, (ImgListBandFlags)flags, &res.frameSize, frames);
        return res;
    }

    ssq::sqstring getMimeTypeByFileName(ssq::sqstring name) const
    {
        return marty_simplesquirrel::to_sqstring(getCheckedPtr("getMimeTypeByFileName")->getMimeTypeByFileName(marty_simplesquirrel::fromSqStringToUtf8(name)));
    }


// struct AddImageBandResult
// {
//     int                imageId = -1;
//     bool               verticalBand = false;
//     ImageSize          frameSize{0,0};

    // int addImageBandFromMultipartImageByMimeEx (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, const std::vector<std::size_t> &frameList) = 0;
    // int addImageBandFromMultipartImageByExtEx  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, const std::vector<std::size_t> &frameList) = 0;
    //  
    // int addImageBandFromMultipartImageByMime (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize) = 0;
    // int addImageBandFromMultipartImageByExt  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize) = 0;
    //  
    // int addImageBandFromMultipartImageByMimeRange (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &mimeType, ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, std::size_t firstFrameIdx, std::size_t numFrames) = 0;
    // int addImageBandFromMultipartImageByExtRange  (const std::vector<std::uint8_t> &imgDirectoryRawData, const std::string &ext     , ImageSize frameMinSize, ImgListBandFlags flags, ImageSize *pFrameSize, std::size_t firstFrameIdx, std::size_t numFrames) = 0;


    static
    ssq::Class expose(ssq::Table /* VM */ & vm, ssq::sqstring clsName = _SC("ImageList"))
    {
        if (clsName.empty())
        {
            clsName = marty_simplesquirrel::to_sqstring(className);
        }

        auto hvm = vm.getHandle();

        auto cls = vm.addClass( clsName.c_str()
                              , [&]()
                                {
                                    return new ImageListWrapper(hvm);
                                }
                              , true // release
                              );

        cls.addFunc( _SC("isSet")                              , &ImageListWrapper::isSet);
        cls.addFunc( _SC("clear")                              , &ImageListWrapper::clear);
        cls.addFunc( _SC("size")                               , &ImageListWrapper::size);
        cls.addFunc( _SC("empty")                              , &ImageListWrapper::empty);
        cls.addFunc( _SC("getMimeTypeByFileName")              , &ImageListWrapper::getMimeTypeByFileName);
        cls.addFunc( _SC("getImageInfo")                       , &ImageListWrapper::getImageInfo);
        cls.addFunc( _SC("getAvailSizesByMime")                , &ImageListWrapper::getAvailSizesByMime);
        cls.addFunc( _SC("getAvailSizesByExt")                 , &ImageListWrapper::getAvailSizesByExt);
        cls.addFunc( _SC("getNumberOfImagesByMime")            , &ImageListWrapper::getNumberOfImagesByMime);
        cls.addFunc( _SC("getNumberOfImagesByExt")             , &ImageListWrapper::getNumberOfImagesByExt);
        cls.addFunc( _SC("findBestFitImageByMime")             , &ImageListWrapper::findBestFitImageByMime);
        cls.addFunc( _SC("findBestFitImageByExt")              , &ImageListWrapper::findBestFitImageByExt);
        cls.addFunc( _SC("findBestFitImageByMimeGetFoundSize") , &ImageListWrapper::findBestFitImageByMimeGetFoundSize);
        cls.addFunc( _SC("findBestFitImageByExtGetFoundSize")  , &ImageListWrapper::findBestFitImageByExtGetFoundSize);
        cls.addFunc( _SC("findBestFitImageByMimeGetFoundSize") , &ImageListWrapper::findBestFitImageByMimeGetFoundSize);
        cls.addFunc( _SC("findBestFitImageByExtGetFoundSize")  , &ImageListWrapper::findBestFitImageByExtGetFoundSize);
        cls.addFunc( _SC("addImageByMime")                     , &ImageListWrapper::addImageByMime);
        cls.addFunc( _SC("addImageByExt")                      , &ImageListWrapper::addImageByExt);
        cls.addFunc( _SC("addImageFitSizeByMime")              , &ImageListWrapper::addImageFitSizeByMime);
        cls.addFunc( _SC("addImageFitSizeByExt")               , &ImageListWrapper::addImageFitSizeByExt);
        cls.addFunc( _SC("createMaskByColor")                  , &ImageListWrapper::createMaskByColor);
        cls.addFunc( _SC("createMaskByPos")                    , &ImageListWrapper::createMaskByPos);
        cls.addFunc( _SC("saveImageAsBmp")                     , &ImageListWrapper::saveImageAsBmp);
        cls.addFunc( _SC("addImageBandFromMultipartImageByMime")      , &ImageListWrapper::addImageBandFromMultipartImageByMime);
        cls.addFunc( _SC("addImageBandFromMultipartImageByExt")       , &ImageListWrapper::addImageBandFromMultipartImageByExt);
        cls.addFunc( _SC("addImageBandFromMultipartImageByMimeRange") , &ImageListWrapper::addImageBandFromMultipartImageByMimeRange);
        cls.addFunc( _SC("addImageBandFromMultipartImageByExtRange")  , &ImageListWrapper::addImageBandFromMultipartImageByExtRange);
        cls.addFunc( _SC("addImageBandFromMultipartImageByMimeEx")    , &ImageListWrapper::addImageBandFromMultipartImageByMimeEx);
        cls.addFunc( _SC("addImageBandFromMultipartImageByExtEx")     , &ImageListWrapper::addImageBandFromMultipartImageByExtEx);
        //cls.addFunc( _SC("")     , &ImageListWrapper::);

        return cls;
    }

}; // struct ImageListWrapper


// dotNut::simplesquirrel::BinaryData
// struct BinaryData : public ObjectBase
// {
//     static const inline std::string        className = "BinaryData";
//     std::vector<std::uint8_t>              data;

    
#endif



} // namespace simplesquirrel {
} // namespace marty_draw_context {
