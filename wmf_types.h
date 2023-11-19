#pragma once

#include "wmf_emf_enums.h"
#include "wmf_emf_basic_types.h"
#include "utils.h"

#include <cstdint>
#include <utility>


namespace marty_draw_context {

namespace wmf {

#include "pushpack1.h"
struct Ciexyz
{
    int_t             ciexyzX; //!< A 32-bit 2.30 fixed point type that defines the x chromaticity value.
    int_t             ciexyzY; //!< A 32-bit 2.30 fixed point type that defines the y chromaticity value.
    int_t             ciexyzZ; //!< A 32-bit 2.30 fixed point type that defines the z chromaticity value.
};
#include "packpop.h"

inline void convertEndiannessToHost(Ciexyz &v)
{
    utils::convertEndiannessToHost(v.ciexyzX, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.ciexyzY, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.ciexyzZ, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, Ciexyz &v)
{
    utils::convertEndiannessToDc(pDc, v.ciexyzX, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.ciexyzY, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.ciexyzZ, Endianness::littleEndian);
}


#include "pushpack1.h"
struct CiexyzTriple
{
    Ciexyz            ciexyzRed  ; //!< A 96-bit CIEXYZ Object (section 2.2.2.6) that defines the red chromaticity values.
    Ciexyz            ciexyzGreen; //!< A 96-bit CIEXYZ Object that defines the green chromaticity values.
    Ciexyz            ciexyzBlue ; //!< A 96-bit CIEXYZ Object that defines the blue chromaticity values.
};
#include "packpop.h"

inline void convertEndiannessToHost(CiexyzTriple &v)
{
    convertEndiannessToHost(v.ciexyzRed  );
    convertEndiannessToHost(v.ciexyzGreen);
    convertEndiannessToHost(v.ciexyzBlue );
}

inline void convertEndiannessToDc(const IDrawContext *pDc, CiexyzTriple &v)
{
    convertEndiannessToDc(pDc, v.ciexyzRed  );
    convertEndiannessToDc(pDc, v.ciexyzGreen);
    convertEndiannessToDc(pDc, v.ciexyzBlue );
}


#include "pushpack1.h"
struct Bitmap16
{
    short_t     type      ; //!< the bitmap type
    short_t     width     ;
    short_t     height    ;
    short_t     widthBytes;
    byte_t      planes    ; //!< The value of this field MUST be 0x01.
    byte_t      bitsPixel ; //!< the number of adjacent color bits on each plane.

    // bits
    // A variable length array of bytes that defines the bitmap pixel data. The length of this field in bytes can be computed as follows.
    // (((Width * BitsPixel + 15) >> 4) << 1) * Height
};
#include "packpop.h"

inline void convertEndiannessToHost(Bitmap16 &v)
{
    utils::convertEndiannessToHost(v.type      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.width     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.height    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.widthBytes, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.planes    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.bitsPixel , Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, Bitmap16 &v)
{
    utils::convertEndiannessToDc(pDc, v.type      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.width     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.height    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.widthBytes, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.planes    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bitsPixel , Endianness::littleEndian);
}


#include "pushpack1.h"
struct BitmapCoreHeader
{
    dword_t     headerSize;
    word_t      width     ;
    word_t      height    ;
    word_t      planes    ; //!< A 16-bit unsigned integer that defines the number of planes for the target device. This value MUST be 0x0001.
    word_t      bitsCount ; //!< A 16-bit unsigned integer that defines the format of each pixel, and the maximum number of colors in the DIB. This value MUST be in the BitCount Enumeration (WMF: section 2.1.1.3).
};
#include "packpop.h"

inline void convertEndiannessToHost(BitmapCoreHeader &v)
{
    utils::convertEndiannessToHost(v.headerSize, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.width     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.height    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.planes    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.bitsCount , Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, BitmapCoreHeader &v)
{
    utils::convertEndiannessToDc(pDc, v.headerSize, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.width     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.height    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.planes    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bitsCount , Endianness::littleEndian);
}



#include "pushpack1.h"
struct BitmapInfoHeader
{
    dword_t     headerSize    ;
    int_t       width         ; //!< A 32-bit signed integer that defines the width of the DIB, in pixels. This value MUST be positive. This field SHOULD specify the width of the decompressed image file, if the Compression value specifies JPEG or PNG format.
    int_t       height        ; //!< 0x00000000 < value. If this value is positive, the DIB is a bottom-up bitmap, and its origin is the lower-left corner.
                                //   This field SHOULD specify the height of the decompressed image file, if the Compression value specifies JPEG or PNG format.
                                //   value < 0x00000000. If this value is negative, the DIB is a top-down bitmap, and its origin is the upper-left corner. Top-down bitmaps do not support compression.
    word_t      planes        ; //!< A 16-bit unsigned integer that defines the number of planes for the target device. This value MUST be 0x0001.
    word_t      bitsCount     ; //!< A 16-bit unsigned integer that defines the format of each pixel, and the maximum number of colors in the DIB. This value MUST be in the BitCount Enumeration (WMF: section 2.1.1.3).
    dword_t     compression   ; //!< A 32-bit unsigned integer that defines the compression mode of the DIB. This value MUST be in the Compression Enumeration (section 2.1.1.7).
                                //   This value MUST NOT specify a compressed format if the DIB is a top-down bitmap, as indicated by the Height value.
    dword_t     imageSize     ; //!< A 32-bit unsigned integer that defines the size, in bytes, of the image.
                                // If the Compression value is BI_RGB, this value SHOULD be zero and MUST be ignored.<45>
                                // If the Compression value is BI_JPEG or BI_PNG, this value MUST specify the size of the JPEG or PNG image buffer, respectively.
    int_t       xPelsPerMeter ; //!< A 32-bit signed integer that defines the horizontal resolution, in pixels-per-meter, of the target device for the DIB.
    int_t       yPelsPerMeter ; //!< A 32-bit signed integer that defines the vertical resolution, in pixels-per-meter, of the target device for the DIB.
    dword_t     colorUsed     ; //!< A 32-bit unsigned integer that specifies the number of indexes in the color table used by the DIB, as follows:
                                // If this value is zero, the DIB uses the maximum number of colors that correspond to the BitCount value.
                                // If this value is nonzero and the BitCount value is less than 16, this value specifies the number of colors used by the DIB.
                                // If this value is nonzero and the BitCount value is 16 or greater, this value specifies the size of the color table used to optimize performance of the system palette.
                                // Note If this value is nonzero and greater than the maximum possible size of the color table based on the BitCount value, the maximum color table size SHOULD be assumed.
    dword_t     colorImportant; //!< A 32-bit unsigned integer that defines the number of color indexes that are required for displaying the DIB. If this value is zero, all color indexes are required.
                               // When the array of pixels in the DIB immediately follows the BitmapInfoHeader, the DIB is a packed bitmap. In a packed bitmap, the ColorUsed value MUST be either 0x00000000 or the actual size of the color table.
};
#include "packpop.h"

inline void convertEndiannessToHost(BitmapInfoHeader &v)
{
     utils::convertEndiannessToHost(v.headerSize    , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.width         , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.height        , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.planes        , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.bitsCount     , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.compression   , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.imageSize     , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.xPelsPerMeter , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.yPelsPerMeter , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.colorUsed     , Endianness::littleEndian);
     utils::convertEndiannessToHost(v.colorImportant, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, BitmapInfoHeader &v)
{
    utils::convertEndiannessToDc(pDc, v.headerSize    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.width         , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.height        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.planes        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bitsCount     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.compression   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.imageSize     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.xPelsPerMeter , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.yPelsPerMeter , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorUsed     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorImportant, Endianness::littleEndian);
}


#include "pushpack1.h"
struct BitmapV4Header
{
    BitmapInfoHeader  bitmapInfoHeader;
    dword_t           redMask         ; //!< A 32-bit unsigned integer that defines the color mask that specifies the red component of each pixel. If the Compression value in the BitmapInfoHeader object is not BI_BITFIELDS, this value MUST be ignored.
    dword_t           greenMask       ; //!< A 32-bit unsigned integer that defines the color mask that specifies the green component of each pixel. If the Compression value in the BitmapInfoHeader object is not BI_BITFIELDS, this value MUST be ignored.
    dword_t           blueMask        ; //!< A 32-bit unsigned integer that defines the color mask that specifies the blue component of each pixel. If the Compression value in the BitmapInfoHeader object is not BI_BITFIELDS, this value MUST be ignored.
    dword_t           alphaMask       ; //!< A 32-bit unsigned integer that defines the color mask that specifies the alpha component of each pixel.
    dword_t           colorSpaceType  ; //!< A 32-bit unsigned integer that defines the color space of the DeviceIndependentBitmap Object (section 2.2.2.9). If this value is LCS_CALIBRATED_RGB from the LogicalColorSpace Enumeration (section 2.1.1.14), the color values in the DIB are calibrated RGB values, and the endpoints and gamma values in this structure SHOULD be used to translate the color values before they are passed to the device.
                                        // See the LogColorSpace (section 2.2.2.11) and LogColorSpace ObjectW (section 2.2.2.12) objects for details concerning a logical color space.
    CiexyzTriple      endpoints       ; //!< A CIEXYZTriple Object (section 2.2.2.7) that defines the CIE chromaticity x, y, and z coordinates of the three colors that correspond to the red, green, and blue endpoints for the logical color space associated with the DIB. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.

                      // The gamma value format is an unsigned "8.8" fixed-point integer that is then left-shifted by 8 bits. "8.8" means "8 integer bits followed by 8 fraction bits": nnnnnnnnffffffff. Taking the shift into account, the required format of the 32-bit DWORD is: 00000000nnnnnnnnffffffff00000000.
    int_t             gammaRed        ; //!< A 32-bit fixed point value that defines the toned response curve for red. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaGreen      ; //!< A 32-bit fixed point value that defines the toned response curve for green. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaBlue       ; //!< A 32-bit fixed point value that defines the toned response curve for blue. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
};
#include "packpop.h"

inline void convertEndiannessToHost(BitmapV4Header &v)
{
     /* utils:: */ convertEndiannessToHost(v.bitmapInfoHeader);
    utils::convertEndiannessToHost(v.redMask         , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.greenMask       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.blueMask        , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.alphaMask       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.colorSpaceType  , Endianness::littleEndian);
     /* utils:: */ convertEndiannessToHost(v.endpoints       );
    utils::convertEndiannessToHost(v.gammaRed        , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.gammaGreen      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.gammaBlue       , Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, BitmapV4Header &v)
{
     /* utils:: */ convertEndiannessToDc(pDc, v.bitmapInfoHeader);
    utils::convertEndiannessToDc(pDc, v.redMask         , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.greenMask       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.blueMask        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.alphaMask       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorSpaceType  , Endianness::littleEndian);
     /* utils:: */ convertEndiannessToDc(pDc, v.endpoints       );
    utils::convertEndiannessToDc(pDc, v.gammaRed        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.gammaGreen      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.gammaBlue       , Endianness::littleEndian);
}


#include "pushpack1.h"
struct BitmapV5Header
{
    BitmapV4Header    bitmapV4Header; //!< When it is part of a BitmapV5Header, the ColorSpaceType field of a BitmapV4Header can be a logical color space value in the LogicalColorSpaceV5 Enumeration
    dword_t           intent        ; //!< A 32-bit unsigned integer that defines the rendering intent for the DIB. This MUST be a value defined in the GamutMappingIntent Enumeration (section 2.1.1.11).
    dword_t           profileData   ; //!< A 32-bit unsigned integer that defines the offset, in bytes, from the beginning of this structure to the start of the color profile data.
                                      // If the color profile is embedded in the DIB, ProfileData is the offset to the actual color profile; if the color profile is linked, ProfileData is the offset to the null-terminated file name of the color profile. This MUST NOT be a Unicode string, but MUST be composed exclusively of characters from the Windows character set (code page 1252).
                                      // If the ColorSpaceType field in the BitmapV4Header does not specify LCS_PROFILE_LINKED or LCS_PROFILE_EMBEDDED, the color profile data SHOULD be ignored.
    dword_t           profileSize   ; //!< A 32-bit unsigned integer that defines the size, in bytes, of embedded color profile data.
    dword_t           reserved      ; //!< A 32-bit unsigned integer that is undefined and SHOULD be ignored.
};
#include "packpop.h"

inline void convertEndiannessToHost(BitmapV5Header &v)
{
     /* utils:: */ convertEndiannessToHost(v.bitmapV4Header);
    utils::convertEndiannessToHost(v.intent        , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.profileData   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.profileSize   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.reserved      , Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, BitmapV5Header &v)
{
     /* utils:: */ convertEndiannessToDc(pDc, v.bitmapV4Header);
    utils::convertEndiannessToDc(pDc, v.intent        , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.profileData   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.profileSize   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.reserved      , Endianness::littleEndian);
}


#include "pushpack1.h"
struct DeviceIndependentBitmap
{
    BitmapCoreHeader dibHeaderInfo;
    // Colors (variable): An optional array of either RGBQuad Objects (section 2.2.2.20) or 16-bit unsigned integers that define a color table.
    // BitmapBuffer (variable): A buffer containing the image, which is not required to be contiguous with the DIB header, unless this is a packed bitmap.
    // UndefinedSpace (variable)
    // aData (variable): An array of bytes that define the image.
    // The size and format of this data is determined by information in the DIBHeaderInfo field. If it is a BitmapCoreHeader, the size in bytes MUST be calculated as follows:
    // (((Width * Planes * BitCount + 31) & ~31) / 8) * abs(Height)
    // This formula SHOULD also be used to calculate the size of aData when DIBHeaderInfo is a BitmapInfoHeader Object, using values from that object, but only if its Compression value is BI_RGB, BI_BITFIELDS, or BI_CMYK.
    // Otherwise, the size of aData MUST be the BitmapInfoHeader Object value ImageSize.
};
#include "packpop.h"

inline void convertEndiannessToHost(DeviceIndependentBitmap &v)
{
    convertEndiannessToHost(v.dibHeaderInfo);
    //convertEndiannessToHost(v., Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, DeviceIndependentBitmap &v)
{
    convertEndiannessToDc(pDc, v.dibHeaderInfo);
    //convertEndiannessToDc(pDc, v., Endianness::littleEndian);
}


#include "pushpack1.h"
struct LogBrush
{
    word_t            brushStyle;
    dword_t           colorRef  ;
    word_t            brushHatch;

};
#include "packpop.h"

inline void convertEndiannessToHost(LogBrush &v)
{
    utils::convertEndiannessToHost(v.brushStyle, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.colorRef  , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.brushHatch, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, LogBrush &v)
{
    utils::convertEndiannessToDc(pDc, v.brushStyle, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorRef  , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.brushHatch, Endianness::littleEndian);
}


#include "pushpack1.h"
struct LogColorSpace
{
    dword_t           signature     ; //!< A 32-bit unsigned integer that specifies the signature of color space objects; it MUST be set to the value 0x50534F43, which is the ASCII encoding of the string "PSOC".
    dword_t           version       ; //!< A 32-bit unsigned integer that defines a version number; it MUST be 0x00000400.
    dword_t           size          ; //!< A 32-bit unsigned integer that defines the size of this object, in bytes.
    int_t             colorSpaceType; //!< A 32-bit signed integer that specifies the color space type. It MUST be defined in the LogicalColorSpace Enumeration (section 2.1.1.14). If this value is LCS_sRGB or LCS_WINDOWS_COLOR_SPACE, the sRGB color space MUST be used.
    int_t             intent        ; //!< A 32-bit signed integer that defines the gamut mapping intent. It MUST be defined in the GamutMappingIntent Enumeration (section 2.1.1.11).
    // See [WMF: 2.2.2.11]
    CiexyzTriple      endpoints     ; //!< A CIEXYZTriple Object (section 2.2.2.7) that defines the CIE chromaticity x, y, and z coordinates of the three colors that correspond to the RGB endpoints for the logical color space associated with the bitmap. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaRed      ; //!< A 32-bit fixed point value that defines the toned response curve for red. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaGreen    ; //!< A 32-bit fixed point value that defines the toned response curve for green. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaBlue     ; //!< A 32-bit fixed point value that defines the toned response curve for blue. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    byte_t            filename[260] ; //!< An optional, ASCII charactger string that specifies the name of a file that contains a color profile. If a file name is specified, and the ColorSpaceType field is set to LCS_CALIBRATED_RGB, the other fields of this structure SHOULD be ignored.
};
#include "packpop.h"

inline void convertEndiannessToHost(LogColorSpace &v)
{
    utils::convertEndiannessToHost(v.signature     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.version       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.size          , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.colorSpaceType, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.intent        , Endianness::littleEndian);
     /* utils:: */ convertEndiannessToHost(v.endpoints     );
    utils::convertEndiannessToHost(v.gammaRed      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.gammaGreen    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.gammaBlue     , Endianness::littleEndian);
    //convertEndiannessToHost(v., Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, LogColorSpace &v)
{
    utils::convertEndiannessToDc(pDc, v.signature     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.version       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.size          , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorSpaceType, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.intent        , Endianness::littleEndian);
     /* utils:: */ convertEndiannessToDc(pDc, v.endpoints     );
    utils::convertEndiannessToDc(pDc, v.gammaRed      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.gammaGreen    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.gammaBlue     , Endianness::littleEndian);
    //convertEndiannessToDc(pDc, v., Endianness::littleEndian);
}


#include "pushpack1.h"
struct LogColorSpaceW
{
    dword_t           signature     ; //!< A 32-bit unsigned integer that specifies the signature of color space objects; it MUST be set to the value 0x50534F43, which is the ASCII encoding of the string "PSOC".
    dword_t           version       ; //!< A 32-bit unsigned integer that defines a version number; it MUST be 0x00000400.
    dword_t           size          ; //!< A 32-bit unsigned integer that defines the size of this object, in bytes.
    int_t             colorSpaceType; //!< A 32-bit signed integer that specifies the color space type. It MUST be defined in the LogicalColorSpace Enumeration (section 2.1.1.14). If this value is LCS_sRGB or LCS_WINDOWS_COLOR_SPACE, the sRGB color space MUST be used.
    int_t             intent        ; //!< A 32-bit signed integer that defines the gamut mapping intent. It MUST be defined in the GamutMappingIntent Enumeration (section 2.1.1.11).
    // See [WMF: 2.2.2.12]
    CiexyzTriple      endpoints     ; //!< A CIEXYZTriple Object (section 2.2.2.7) that defines the CIE chromaticity x, y, and z coordinates of the three colors that correspond to the RGB endpoints for the logical color space associated with the bitmap. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaRed      ; //!< A 32-bit fixed point value that defines the toned response curve for red. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaGreen    ; //!< A 32-bit fixed point value that defines the toned response curve for green. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    int_t             gammaBlue     ; //!< A 32-bit fixed point value that defines the toned response curve for blue. If the ColorSpaceType field does not specify LCS_CALIBRATED_RGB, this field MUST be ignored.
    word_t            filename[260] ; //!< An optional, UTF16-LE charactger string that specifies the name of a file that contains a color profile. If a file name is specified, and the ColorSpaceType field is set to LCS_CALIBRATED_RGB, the other fields of this structure SHOULD be ignored.
};
#include "packpop.h"

inline void convertEndiannessToHost(LogColorSpaceW &v)
{
    utils::convertEndiannessToHost(v.signature     , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.version       , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.size          , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.colorSpaceType, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.intent        , Endianness::littleEndian);
     /* utils:: */ convertEndiannessToHost(v.endpoints     );
    utils::convertEndiannessToHost(v.gammaRed      , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.gammaGreen    , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.gammaBlue     , Endianness::littleEndian);
    for(auto i=0u; i<260u; ++i)
    {
        utils::convertEndiannessToHost(v.filename[i], Endianness::littleEndian);
    }
}

inline void convertEndiannessToDc(const IDrawContext *pDc, LogColorSpaceW &v)
{
    utils::convertEndiannessToDc(pDc, v.signature     , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.version       , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.size          , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.colorSpaceType, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.intent        , Endianness::littleEndian);
     /* utils:: */ convertEndiannessToDc(pDc, v.endpoints     );
    utils::convertEndiannessToDc(pDc, v.gammaRed      , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.gammaGreen    , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.gammaBlue     , Endianness::littleEndian);
    for(auto i=0u; i<260u; ++i)
    {
        utils::convertEndiannessToHost(v.filename[i], Endianness::littleEndian);
    }
}


#include "pushpack1.h"
struct PointL
{
    int_t             x;
    int_t             y;
};
#include "packpop.h"

inline void convertEndiannessToHost(PointL &v)
{
    utils::convertEndiannessToHost(v.x, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.y, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, PointL &v)
{
    utils::convertEndiannessToDc(pDc, v.x, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.y, Endianness::littleEndian);
}


#include "pushpack1.h"
struct PointS
{
    short_t           x;
    short_t           y;
};
#include "packpop.h"

inline void convertEndiannessToHost(PointS &v)
{
    utils::convertEndiannessToHost(v.x, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.y, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, PointS &v)
{
    utils::convertEndiannessToDc(pDc, v.x, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.y, Endianness::littleEndian);
}


#include "pushpack1.h"
struct Rect
{
    short_t           left  ;
    short_t           top   ;
    short_t           right ;
    short_t           bottom;
};
#include "packpop.h"

inline void convertEndiannessToHost(Rect &v)
{
    utils::convertEndiannessToHost(v.left  , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.top   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.right , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.bottom, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, Rect &v)
{
    utils::convertEndiannessToDc(pDc, v.left  , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.top   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.right , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bottom, Endianness::littleEndian);
}


#include "pushpack1.h"
struct RectL
{
    int_t             left  ;
    int_t             top   ;
    int_t             right ;
    int_t             bottom;
};
#include "packpop.h"

inline void convertEndiannessToHost(RectL &v)
{
    utils::convertEndiannessToHost(v.left  , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.top   , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.right , Endianness::littleEndian);
    utils::convertEndiannessToHost(v.bottom, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, RectL &v)
{
    utils::convertEndiannessToDc(pDc, v.left  , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.top   , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.right , Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.bottom, Endianness::littleEndian);
}


#include "pushpack1.h"
struct RGBQuad
{
    byte_t            blue    ;
    byte_t            green   ;
    byte_t            red     ;
    byte_t            reserved;
};
#include "packpop.h"

inline void convertEndiannessToHost(RGBQuad &v)
{
    //convertEndiannessToHost(v., Endianness::littleEndian);
    MARTY_ARG_USED(v);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, RGBQuad &v)
{
    //convertEndiannessToDc(pDc, v., Endianness::littleEndian);
    MARTY_ARG_USED(pDc);
    MARTY_ARG_USED(v);
}


#include "pushpack1.h"
struct SizeL
{
    int_t             cx;
    int_t             cy;
};
#include "packpop.h"

inline void convertEndiannessToHost(SizeL &v)
{
    utils::convertEndiannessToHost(v.cx, Endianness::littleEndian);
    utils::convertEndiannessToHost(v.cy, Endianness::littleEndian);
}

inline void convertEndiannessToDc(const IDrawContext *pDc, SizeL &v)
{
    utils::convertEndiannessToDc(pDc, v.cx, Endianness::littleEndian);
    utils::convertEndiannessToDc(pDc, v.cy, Endianness::littleEndian);
}



} // namespace wmf

} // namespace marty_draw_context

