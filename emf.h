#pragma once

#include "emf_types.h"

#include <cstdint>
#include <utility>
#include <exception>
#include <stdexcept>


namespace marty_draw_context {

namespace emf {

// https://olegus28.narod.ru/wmf/wmfile.htm
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-emf/de081cd7-351f-4cc2-830b-d03fb55e89ab?redirectedfrom=MSDN


// EmfMetafileHeader
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-emf/80c0684b-9a0e-4bdb-8d6d-0e5a9e9673e7
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-emf/2caf0f47-81a4-4079-931d-fca6fa499869
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-emf/de081cd7-351f-4cc2-830b-d03fb55e89ab


// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-wmf/4813e7fd-52d0-4f42-965f-228c8b7488d2
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-emf/91c257d7-c39d-4a36-9b1f-63e3f73d30ca





#if 0
#include "pushpack1.h"
struct RecordType
{
    RecordType    type;

    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        return sizeof(RecordType) <= rawDataRestSize;
    }

    static RecordType extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static RecordType extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);

};
#include "packpop.h"

inline void convertEndiannessToHost(RecordType &v)
{
    utils::convertEndiannessToHost(v.type, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, RecordType &v)
{
    utils::convertEndiannessToDc(pDc, v.type, Endianness::littleEndian);
}

inline RecordType RecordType::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    RecordType v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline RecordType RecordType::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    RecordType v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToDc(pDc, v);
    return v;
}
#endif


#include "pushpack1.h"
struct RecordTypeSize
{
    RecordType    type;
    dword_t       size;

    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        return sizeof(RecordTypeSize) <= rawDataRestSize;
    }

    static RecordTypeSize extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static RecordTypeSize extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);
};
#include "packpop.h"

inline void convertEndiannessToHost(RecordTypeSize &v)
{
    utils::convertEndiannessToHost(v.type, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, RecordTypeSize &v)
{
    utils::convertEndiannessToDc(pDc, v.type, Endianness::littleEndian);
}

inline RecordTypeSize RecordTypeSize::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    RecordTypeSize v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline RecordTypeSize RecordTypeSize::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    RecordTypeSize v;
    pRawData = utils::copyFromRawBytesEx( v, pRawData, rawDataRestSize);
    convertEndiannessToDc(pDc, v);
    return v;
}


#include "pushpack1.h"
struct MetafileHeader
{
    RecordType           type            = RecordType::header;
    dword_t              size            ;
    Header               header          ;
    HeaderExtension1     headerExtension1;
    HeaderExtension2     headerExtension2;

    // Not serialized
    EmfMetafileHeaderOptions headerOptions = EmfMetafileHeaderOptions::basicHeader; // headerExt1/headerExt2

protected:
    static const std::uint8_t* extractHeaderExtentions(MetafileHeader &v, const std::uint8_t* pRawData, std::size_t &rawDataRestSize);
    static const std::uint8_t* extractDescriptionAndPixelFormat(MetafileHeader &v, const std::uint8_t* pRawData, std::size_t &rawDataRestSize, std::size_t alreadyReadedBytes);

public:
    static bool canExtractFromRawBytes(const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
    {
        MARTY_ARG_USED(pRawData);
        const auto  szHdr  = sizeof(RecordType) + sizeof(dword_t) + sizeof(Header);
        return szHdr <= rawDataRestSize;
    }

    static MetafileHeader extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize);
    static MetafileHeader extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc);
 
};
#include "packpop.h"

inline void convertEndiannessToHost(MetafileHeader &v)
{
    utils::convertEndiannessToHost(v.type, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.size, Endianness::littleEndian);
    convertEndiannessToHost(v.header);
    if (v.headerOptions==EmfMetafileHeaderOptions::headerExt1 || v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
    {
        convertEndiannessToHost(v.headerExtension1);
        if (v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
        {
            convertEndiannessToHost(v.headerExtension2);
        }
    }
}

inline void convertEndiannessToDc(const IDrawContext *pDc, MetafileHeader &v)
{
    utils::convertEndiannessToDc(pDc, v.type, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.size, Endianness::littleEndian);
    convertEndiannessToDc(pDc, v.header);
    if (v.headerOptions==EmfMetafileHeaderOptions::headerExt1 || v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
    {
        convertEndiannessToHost(v.headerExtension1);
        if (v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
        {
            convertEndiannessToHost(v.headerExtension2);
        }
    }
}

inline const std::uint8_t* MetafileHeader::extractHeaderExtentions(MetafileHeader &v, const std::uint8_t* pRawData, std::size_t &rawDataRestSize)
{
    dword_t  headerSize = v.size;
    utils::convertEndiannessToHost(headerSize, Endianness::littleEndian);

    // Header   headerCopy = header;
    // convertEndiannessToHost(headerCopy);

    const auto  szHdr  = sizeof(v.type) + sizeof(v.size) + sizeof(v.header);
    const auto  szHdr1 = sizeof(v.headerExtension1);
    const auto  szHdr2 = sizeof(v.headerExtension2);

    const auto  szHdrHdr1     = szHdr + szHdr1;
    const auto  szHdrHdr1Hdr2 = szHdr + szHdr1 + szHdr2;

    MARTY_ARG_USED(szHdr        );
    MARTY_ARG_USED(szHdr1       );
    MARTY_ARG_USED(szHdr2       );
    MARTY_ARG_USED(szHdrHdr1    );
    MARTY_ARG_USED(szHdrHdr1Hdr2);

    if (headerSize<szHdr)
    {
        throw std::runtime_error("marty_draw_context::emf::MetafileHeader::extractFromRawBytes failed (1)");
    }

    /*
    if ((header.offDescription>=szHdr) && ((header.offDescription+(header.nDescription*2))<=headerSize))
    {
        headerSize = header.offDescription;
    }
    */

    v.headerOptions = EmfMetafileHeaderOptions::basicHeader;
    if (headerSize>=szHdrHdr1)
    {
        v.headerOptions = EmfMetafileHeaderOptions::headerExt1;
        if (headerSize>=szHdrHdr1Hdr2)
        {
            v.headerOptions = EmfMetafileHeaderOptions::headerExt2;
        }
    }

    if (v.headerOptions==EmfMetafileHeaderOptions::headerExt1 || v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
    {
        if (rawDataRestSize<szHdr1)
        {
            throw std::runtime_error("marty_draw_context::emf::MetafileHeader::extractFromRawBytes failed (2)");
        }

        pRawData = utils::copyFromRawBytesEx( v.headerExtension1, pRawData, rawDataRestSize);

        if (v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
        {
            if (rawDataRestSize<szHdr1)
            {
                throw std::runtime_error("marty_draw_context::emf::MetafileHeader::extractFromRawBytes failed (3)");
            }

            pRawData = utils::copyFromRawBytesEx( v.headerExtension2, pRawData, rawDataRestSize);
        }
    }

    return pRawData;
}

inline const std::uint8_t* MetafileHeader::extractDescriptionAndPixelFormat(MetafileHeader &v, const std::uint8_t* pRawData, std::size_t &rawDataRestSize, std::size_t alreadyReadedBytes)
{
    MARTY_ARG_USED(rawDataRestSize);
    MARTY_ARG_USED(pRawData);

    dword_t offDescription = 0;
    dword_t nDescription   = 0;
    if (v.header.offDescription>=(dword_t)alreadyReadedBytes)
    {
        offDescription = v.header.offDescription - (dword_t)alreadyReadedBytes;
        nDescription   = v.header.nDescription;
    }

    dword_t offPixelFormat = 0;
    dword_t cbPixelFormat  = 0;

    if (v.headerOptions==EmfMetafileHeaderOptions::headerExt1 || v.headerOptions==EmfMetafileHeaderOptions::headerExt2)
    {
        if (v.headerExtension1.offPixelFormat>=(dword_t)alreadyReadedBytes)
        {
            offPixelFormat = v.headerExtension1.offPixelFormat - (dword_t)alreadyReadedBytes;
            cbPixelFormat  = v.headerExtension1.cbPixelFormat;
        }
    }

    return pRawData;

    // Ненулевые nDescription и cbPixelFormat говорят о том, что эти части присутствуют

// struct HeaderExtension1
// {
//     dword_t                   cbPixelFormat ; //!< (4 bytes): An unsigned integer that specifies the size of the PixelFormatDescriptor object. This value is 0x00000000 if no pixel format is set.
//     dword_t                   offPixelFormat; //!< (4 bytes): An unsigned integer that specifies the offset to the PixelFormatDescriptor object. This value is 0x00000000 if no pixel format is set.


// struct Header
// {
    // ... 
    // dword_t                nDescription   ; //!< (4 bytes): An unsigned integer that specifies the number of characters in the array that contains the description of the metafile's contents. This is zero if there is no description string.
    // dword_t                offDescription ; //!< (4 bytes): An unsigned integer that specifies the offset from the beginning of this record to the array that contains the description of the metafile's contents.



}

inline MetafileHeader MetafileHeader::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize)
{
    std::size_t rawDataRestSizeOrg = rawDataRestSize;

    MetafileHeader v;
    pRawData = utils::copyFromRawBytesEx( v.type  , pRawData, rawDataRestSize);
    pRawData = utils::copyFromRawBytesEx( v.size  , pRawData, rawDataRestSize);
    pRawData = utils::copyFromRawBytesEx( v.header, pRawData, rawDataRestSize);
    pRawData = extractHeaderExtentions(v, pRawData, rawDataRestSize);
    pRawData = extractDescriptionAndPixelFormat(v, pRawData, rawDataRestSize, rawDataRestSizeOrg-rawDataRestSize);
    convertEndiannessToHost(v);
    return v;
}

inline MetafileHeader MetafileHeader::extractFromRawBytes( const std::uint8_t* &pRawData, std::size_t &rawDataRestSize, const IDrawContext *pDc)
{
    std::size_t rawDataRestSizeOrg = rawDataRestSize;

    MetafileHeader v;
    pRawData = utils::copyFromRawBytesEx( v.type  , pRawData, rawDataRestSize);
    pRawData = utils::copyFromRawBytesEx( v.size  , pRawData, rawDataRestSize);
    pRawData = utils::copyFromRawBytesEx( v.header, pRawData, rawDataRestSize);
    pRawData = extractHeaderExtentions(v, pRawData, rawDataRestSize);
    pRawData = extractDescriptionAndPixelFormat(v, pRawData, rawDataRestSize, rawDataRestSizeOrg-rawDataRestSize);

    std::size_t readedBytes = rawDataRestSizeOrg-rawDataRestSize;
    MARTY_ARG_USED(readedBytes);

    convertEndiannessToDc(pDc, v);
    return v;
}

// #include "pushpack1.h"
// struct Header
// {
//  
// };
// #include "packpop.h"


} // namespace emf

} // namespace marty_draw_context



