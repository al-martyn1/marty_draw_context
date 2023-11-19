#pragma once

// #include "wmf_emf_enums.h"
#include "emf_enums.h"

#include "wmf_emf_basic_types.h"
#include "wmf_types.h"

#include <cstdint>
#include <utility>


namespace marty_draw_context {

namespace emf {

// typedef WMF types here

using  PointL  = wmf::PointL  ;
using  PointS  = wmf::PointS  ;
using  Rect    = wmf::Rect    ;
using  RectL   = wmf::RectL   ;
using  RGBQuad = wmf::RGBQuad ;
using  SizeL   = wmf::SizeL   ;

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
#include "pushpack1.h"
struct Header
{
    RectL                  bounds         ; //!< A RectL object ([MS-WMF] section 2.2.2.19) that specifies the rectangular inclusive-inclusive bounds in logical units of the smallest rectangle that can be drawn around the image stored in the metafile.
    RectL                  frame          ; //!< A RectL object that specifies the rectangular inclusive-inclusive dimensions, in .01 millimeter units, of a rectangle that surrounds the image stored in the metafile.
    EmfFormatSignature     recordSignature; //!< An unsigned integer that specifies the record signature. This MUST be ENHMETA_SIGNATURE, from the FormatSignature enumeration (section 2.1.14).
    dword_t                version        ; //!< An unsigned integer that specifies the EMF version for interoperability. This MAY be 0x00010000.
    dword_t                bytes          ; //!< (4 bytes): An unsigned integer that specifies the size of the metafile in bytes.
    dword_t                records        ; //!< (4 bytes): An unsigned integer that specifies the number of records in the metafile.
    word_t                 handles        ; //!< (2 bytes): An unsigned integer that specifies the number of graphics objects that are used during the processing of the metafile.
    word_t                 reserved       ; //!< (2 bytes): An unsigned integer that MUST be 0x0000 and MUST be ignored.
    dword_t                nDescription   ; //!< (4 bytes): An unsigned integer that specifies the number of characters in the array that contains the description of the metafile's contents. This is zero if there is no description string.
    dword_t                offDescription ; //!< (4 bytes): An unsigned integer that specifies the offset from the beginning of this record to the array that contains the description of the metafile's contents.
    dword_t                nPalEntries    ; //!< (4 bytes): An unsigned integer that specifies the number of entries in the metafile palette. The palette is located in the EMR_EOF record.
    SizeL                  device         ; //!< (8 bytes): A SizeL object ([MS-WMF] section 2.2.2.22) that specifies the size of the reference device, in pixels.
    SizeL                  millimeters    ; //!< (8 bytes): A SizeL object that specifies the size of the reference device, in millimeters.

    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        return sizeof(Header) <= rawDataRestSize;
    }

    static Header extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static Header extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);

};
#include "packpop.h"

inline void convertEndiannessToHost(Header &v)
{
    convertEndiannessToHost(v.bounds         );
    convertEndiannessToHost(v.frame          );
    utils::convertEndiannessToHost(v.recordSignature, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.version        , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.bytes          , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.records        , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.handles        , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.reserved       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.nDescription   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.offDescription , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.nPalEntries    , Endianness::littleEndian);
    convertEndiannessToHost(v.device         );
    convertEndiannessToHost(v.millimeters    );
}

inline void convertEndiannessToDc(const IDrawContext *pDc, Header &v)
{
    convertEndiannessToDc(pDc, v.bounds         );
    convertEndiannessToDc(pDc, v.frame          );
    utils::convertEndiannessToDc(pDc, v.recordSignature, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.version        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bytes          , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.records        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.handles        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.reserved       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.nDescription   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.offDescription , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.nPalEntries    , Endianness::littleEndian);
    convertEndiannessToDc(pDc, v.device         );
    convertEndiannessToDc(pDc, v.millimeters    );
}

inline Header Header::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    Header v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline Header Header::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    Header v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToDc(pDc, v);
    return v;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
#include "pushpack1.h"
struct HeaderExtension1
{
    dword_t                   cbPixelFormat ; //!< (4 bytes): An unsigned integer that specifies the size of the PixelFormatDescriptor object. This value is 0x00000000 if no pixel format is set.
    dword_t                   offPixelFormat; //!< (4 bytes): An unsigned integer that specifies the offset to the PixelFormatDescriptor object. This value is 0x00000000 if no pixel format is set.
    OpenGlPresenceFlag        bOpenGL       ; //!< (4 bytes): An unsigned integer that indicates whether OpenGL commands are present in the metafile.

    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        return sizeof(HeaderExtension1) <= rawDataRestSize;
    }

    static HeaderExtension1 extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static HeaderExtension1 extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);

};
#include "packpop.h"

inline void convertEndiannessToHost(HeaderExtension1 &v)
{
    utils::convertEndiannessToHost(v.cbPixelFormat , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.offPixelFormat, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.bOpenGL       , Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, HeaderExtension1 &v)
{
    utils::convertEndiannessToDc(pDc, v.cbPixelFormat , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.offPixelFormat, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bOpenGL       , Endianness::littleEndian);
}

inline HeaderExtension1 HeaderExtension1::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    HeaderExtension1 v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline HeaderExtension1 HeaderExtension1::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    HeaderExtension1 v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToDc(pDc, v);
    return v;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
#include "pushpack1.h"
struct HeaderExtension2
{
    dword_t       micrometersX; //!< (4 bytes): The 32-bit horizontal size of the display device for which the metafile image was generated, in micrometers.
    dword_t       micrometersY; //!< (4 bytes): The 32-bit vertical size of the display device for which the metafile image was generated, in micrometers.

    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        return sizeof(HeaderExtension2) <= rawDataRestSize;
    }

    static HeaderExtension2 extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static HeaderExtension2 extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);
};
#include "packpop.h"

inline void convertEndiannessToHost(HeaderExtension2 &v)
{
    utils::convertEndiannessToHost(v.micrometersX, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.micrometersY, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, HeaderExtension2 &v)
{
    utils::convertEndiannessToDc(pDc, v.micrometersX, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.micrometersY, Endianness::littleEndian);
}

inline HeaderExtension2 HeaderExtension2::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    HeaderExtension2 v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline HeaderExtension2 HeaderExtension2::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    HeaderExtension2 v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToDc(pDc, v);
    return v;
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
#include "pushpack1.h"
struct PixelFormatDescriptor
{
    word_t                     size           ;
    word_t                     version        ;
    PixelFormatDescriptorFlags flags          ;
    PfdPixelType               pixelType      ;
    byte_t                     colorBits      ;
    byte_t                     redBits        ;
    byte_t                     redShift       ;
    byte_t                     greenBits      ;
    byte_t                     greenShift     ;
    byte_t                     blueBits       ;
    byte_t                     blueShift      ;
    byte_t                     alphaBits      ;
    byte_t                     alphaShift     ;
    byte_t                     accumBits      ;
    byte_t                     accumRedBits   ;
    byte_t                     accumGreenBits ;
    byte_t                     accumBlueBits  ;
    byte_t                     accumAlphaBits ;
    byte_t                     depthBits      ;
    byte_t                     stencilBits    ;
    byte_t                     auxBuffers     ;
    byte_t                     layerType      ;
    byte_t                     reserved       ;
    dword_t                    layerMask      ;
    dword_t                    visibleMask    ;
    dword_t                    damageMask     ;

    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        return sizeof(PixelFormatDescriptor) <= rawDataRestSize;
    }

    static PixelFormatDescriptor extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static PixelFormatDescriptor extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);

};
#include "packpop.h"

inline void convertEndiannessToHost(PixelFormatDescriptor &v)
{
    utils::convertEndiannessToHost(v.size          , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.version       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.flags         , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.pixelType     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.colorBits     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.redBits       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.redShift      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.greenBits     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.greenShift    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.blueBits      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.blueShift     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.alphaBits     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.alphaShift    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.accumBits     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.accumRedBits  , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.accumGreenBits, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.accumBlueBits , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.accumAlphaBits, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.depthBits     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.stencilBits   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.auxBuffers    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.layerType     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.reserved      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.layerMask     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.visibleMask   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.damageMask    , Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, PixelFormatDescriptor &v)
{
    utils::convertEndiannessToDc(pDc, v.size          , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.version       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.flags         , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.pixelType     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorBits     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.redBits       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.redShift      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.greenBits     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.greenShift    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.blueBits      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.blueShift     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.alphaBits     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.alphaShift    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.accumBits     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.accumRedBits  , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.accumGreenBits, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.accumBlueBits , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.accumAlphaBits, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.depthBits     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.stencilBits   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.auxBuffers    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.layerType     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.reserved      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.layerMask     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.visibleMask   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.damageMask    , Endianness::littleEndian);
}

inline PixelFormatDescriptor PixelFormatDescriptor::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    PixelFormatDescriptor v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline PixelFormatDescriptor PixelFormatDescriptor::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    PixelFormatDescriptor v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToDc(pDc, v);
    return v;
}


/*
#include "pushpack1.h"
struct 
{
};
#include "packpop.h"


#include "pushpack1.h"
struct 
{
};
#include "packpop.h"
*/



} // namespace emf

} // namespace marty_draw_context
