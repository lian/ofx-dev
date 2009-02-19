/**
 * File:          $RCSfile: dpx_io.h,v $
 * Module:        DPX format image file I/O functions
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.28 $
 * Last edited:   $Date: 2006/05/04 11:21:46 $
 * Author:        $Author: nicolas $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _GAN_IMAGE_DPX_IO_H
#define _GAN_IMAGE_DPX_IO_H

#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/image/image_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup ImagePackage
 * \{
 */

/**
 * \addtogroup ImageIO
 * \{
 */

/**
 * \brief DPX Transfer characteristics
 */
typedef enum Gan_DPXTransferCharacteristic
{
    GAN_DPXTRANSFER_USER_DEFINED      =  0,
    GAN_DPXTRANSFER_PRINTING_DENSITY  =  1,
    GAN_DPXTRANSFER_LINEAR            =  2,
    GAN_DPXTRANSFER_LOGARITHMIC       =  3,
    GAN_DPXTRANSFER_UNSPECIFIED_VIDEO =  4,
    GAN_DPXTRANSFER_SMPTE240M         =  5,
    GAN_DPXTRANSFER_CCIR709_1         =  6,
    GAN_DPXTRANSFER_CCIR601_2BG       =  7,
    GAN_DPXTRANSFER_CCIR601_2M        =  8,
    GAN_DPXTRANSFER_NTSC              =  9,
    GAN_DPXTRANSFER_PAL               = 10,
    GAN_DPXTRANSFER_ZLINEAR           = 11,
    GAN_DPXTRANSFER_ZHOMOGENEOUS      = 12,
    GAN_DPXTRANSFER_DEFAULT
} Gan_DPXTransferCharacteristic;

/**
 * \brief DPX Colorimetric characteristics
 */
typedef enum Gan_DPXColorimetricCharacteristics
{
    GAN_DPXCOLORIMETRIC_USER_DEFINED      =  0,
    GAN_DPXCOLORIMETRIC_PRINTING_DENSITY  =  1,
    GAN_DPXCOLORIMETRIC_UNSPECIFIED_VIDEO =  4,
    GAN_DPXCOLORIMETRIC_SMPTE240M         =  5,
    GAN_DPXCOLORIMETRIC_CCIR709_1         =  6,
    GAN_DPXCOLORIMETRIC_CCIR601_2BG       =  7,
    GAN_DPXCOLORIMETRIC_CCIR601_2M        =  8,
    GAN_DPXCOLORIMETRIC_NTSC              =  9,
    GAN_DPXCOLORIMETRIC_PAL               = 10,
    GAN_DPXCOLORIMETRIC_DEFAULT
} Gan_DPXColorimetricCharacteristics;

/// Generic DPX image data header
typedef struct Gan_DPXGenericImageDataHeader
{
   /// header version
   char version[8];

   /// read time short cut - 0 = same, 1 = new
   gan_uint32 ditto_key;

   /// image file name
   char file_name[100];

   /// file creation date
   char create_time[24];

   /// file creator's name
   char creator[100];

   /// project name
   char project[200];

   /// right to use or copyright info
   char copyright[200];

   /// encryption key
   gan_uint32 encryption_key;
} Gan_DPXGenericImageDataHeader;

/// DPX image information header
typedef struct Gan_DPXImageInfoHeader
{
   /// whether the data is signed or not
   Gan_Bool data_sign;

   /// reference low data code value
   gan_uint32 ref_low_data;
   
   /// reference low quantity represented
   gan_float32 ref_low_quantity;
   
   /// reference high data code value
   gan_uint32 ref_high_data;
   
   /// reference high quantity represented
   gan_float32 ref_high_quantity;

   /// descriptor of image element
   gan_uint8 descriptor;

   /// transfer characteristic
   Gan_DPXTransferCharacteristic transfer;

   /// colorimetric characteristic
   Gan_DPXColorimetricCharacteristics colorimetric;

   /// bit size; 0 means default
   unsigned int bit_size;

   /// whether to data is packed
   Gan_Bool packed;

   /// encoding for element
   gan_uint16 encoding;

   /// desciption of element
   char description[32];
} Gan_DPXImageInfoHeader;

/**
 * \brief DPX orientation header section structure
 */
typedef struct Gan_DPXOrientationHeader
{
   gan_uint32 x_offset, y_offset;
   gan_uint32 x_centre, y_centre;
   gan_uint32 x_orig_size, y_orig_size;

   /// source image file name
   char file_name[100];

   // source image creation date and time
   char creation_time[24];

   /// input device name
   char input_dev[32];

   /// input device serial number
   char input_serial[32];

   /// border validity (XL, XR, YT, YR)
   gan_uint16 border[4];

   /// pixel aspect ration (H:V)
   gan_uint32 pixel_aspect[2];
} Gan_DPXOrientationHeader;

/**
 * \brief DPX film Header section structure
 */
typedef struct Gan_DPXFilmHeader
{
   /// film manufacturer ID code (6 digits from film edge code)
   char film_mfg_id[2];

   /// film type (6 digits from film edge code)
   char film_type[2];

   /// offset in perfs (2 digits from film edge code)
   char offset[2];

   /// prefix (6 digits from film edge code)
   char prefix[6];

   /// count (4 digits from film edge code)
   char count[4];

   /// format (e.g. academy)
   char format[32];

   /// frame position in sequence
   gan_uint32 frame_position;

   /// sequence length in frames
   gan_uint32 sequence_len;

   /// held count (1 = default)
   gan_uint32 held_count;

   /// frame rate of original in frames/sec
   gan_float32 frame_rate;

   /// shutter angle of camera in degrees
   gan_float32 shutter_angle;

   /// frame identification
   char frame_id[32];

   /// slate information
   char slate_info[100];
} Gan_DPXFilmHeader;

/**
 * \brief DPX TV Header section structure
 */
typedef struct Gan_DPXTVHeader
{
   /// field number
   gan_uint8 field_num;

   /// video signal standard
   gan_uint8 video_signal;

   /// horizontal sampling rate in Hz
   gan_float32 hor_sample_rate;

   /// vertical sample rate in Hz
   gan_float32 ver_sample_rate;

   /// temporal sampling rate or frame rate in Hz
   gan_float32 frame_rate;

   /// time offset from sync to first pixel
   gan_float32 time_offset;

   /// gamma value
   gan_float32 gamma;

   /// black level code value
   gan_float32 black_level;

   /// black gain
   gan_float32 black_gain;

   /// breakpoint
   gan_float32 break_point;

   /// reference white level code value
   gan_float32 white_level;

   /// integration time(s)
   gan_float32 integration_times;
} Gan_DPXTVHeader;

/**
 * \brief DPX Header structure
 */
typedef struct Gan_DPXHeaderStruct
{
   Gan_DPXGenericImageDataHeader generic;
   Gan_DPXImageInfoHeader        image_info;
   Gan_DPXOrientationHeader      orientation;
   Gan_DPXFilmHeader             film;
   Gan_DPXTVHeader               tv;
} Gan_DPXHeaderStruct;

/* functions exported so that Cineon I/O can use them */
GANDALF_API void vReverseEndianness32(gan_uint32* pui32Val);
GANDALF_API void vReverseEndianness16(gan_uint16* pui16Val);
GANDALF_API gan_uint32 ui32ReverseEndianness(gan_uint32 ui32Val);
GANDALF_API gan_uint16 ui16ReverseEndianness(gan_uint16 ui16Val);
GANDALF_API void vReverseEndiannessArray16(gan_uint16* aui16Val, unsigned int uiNumberOfVals);
GANDALF_API void vReverseEndiannessArray32(gan_uint32* aui32Val, unsigned int uiNumberOfVals);
GANDALF_API Gan_Image *pgiRead1BitDPXImageData(FILE* pfInFile,
                                               gan_uint32 ui32eolPadding, gan_uint32 ui32eoImagePadding,
                                               Gan_ImageFormat eFormat, Gan_Type eType,
                                               gan_uint32 ui32PixelsPerLine, gan_uint32 ui32LinesPerImageEle,
                                               Gan_Image* pgiImage, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Image *pgiRead8BitDPXImageData(FILE* pfInFile,
                                               gan_uint32 ui32eolPadding, gan_uint32 ui32eoImagePadding,
                                               Gan_ImageFormat eFormat, Gan_Type eType,
                                               gan_uint32 ui32PixelsPerLine, gan_uint32 ui32LinesPerImageEle,
                                               Gan_Image* pgiImage, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Image *pgiRead10BitDPXImageData(FILE* pfInFile, Gan_Bool bReversedEndianness, Gan_Bool bPacked,
                                                gan_uint32 ui32eolPadding, gan_uint32 ui32eoImagePadding,
                                                Gan_ImageFormat eFormat, Gan_Type eType,
                                                gan_uint32 ui32PixelsPerLine, gan_uint32 ui32LinesPerImageEle,
                                                Gan_Image* pgiImage, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Image *pgiRead12BitDPXImageData(FILE* pfInFile, Gan_Bool bReversedEndianness, Gan_Bool bPacked,
                                                gan_uint32 ui32eolPadding, gan_uint32 ui32eoImagePadding,
                                                Gan_ImageFormat eFormat, Gan_Type eType,
                                                gan_uint32 ui32PixelsPerLine, gan_uint32 ui32LinesPerImageEle,
                                                Gan_Image* pgiImage, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Image *pgiRead16BitDPXImageData(FILE* pfInFile, Gan_Bool bReversedEndianness,
                                                gan_uint32 ui32eolPadding, gan_uint32 ui32eoImagePadding,
                                                Gan_ImageFormat eFormat, Gan_Type eType,
                                                gan_uint32 ui32PixelsPerLine, gan_uint32 ui32LinesPerImageEle,
                                                Gan_Image* pgiImage, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Image *pgiRead32BitFloatDPXImageData(FILE* pfInFile, Gan_Bool bReversedEndianness,
                                                     gan_uint32 ui32eolPadding, gan_uint32 ui32eoImagePadding,
                                                     Gan_ImageFormat eFormat, Gan_Type eType,
                                                     gan_uint32 ui32PixelsPerLine, gan_uint32 ui32LinesPerImageEle,
                                                     Gan_Image* pgiImage, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API gan_uint32 ui32DPXFileSize(unsigned int uiImageDataOffset,
                           Gan_ImageFormat eFormat, gan_uint8 ui8BitSize, Gan_Bool bPacked, unsigned int uiHeight, unsigned int uiWidth,
                           gan_uint32* pui32eolPadding);
GANDALF_API Gan_Bool bWrite1BitDPXImageData(FILE* pfOutFile, const Gan_Image* pgiImage, Gan_Bool bNewFile, unsigned int uieolPadding,
                                            Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Bool bWrite8BitDPXImageData(FILE* pfOutFile, const Gan_Image* pgiImage, Gan_Bool bNewFile, unsigned int uieolPadding,
                                            Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Bool bWrite10BitDPXImageData(FILE* pfOutFile, const Gan_Image* pgiImage, Gan_Bool bNewFile, Gan_Bool bReverseBytes, unsigned int uieolPadding,
                                             Gan_Bool bPacked, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Bool bWrite12BitDPXImageData(FILE* pfOutFile, const Gan_Image* pgiImage, Gan_Bool bNewFile, Gan_Bool bReverseBytes, unsigned int uieolPadding,
                                             Gan_Bool bPacked, Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Bool bWrite16BitDPXImageData(FILE* pfOutFile, const Gan_Image* pgiImage, Gan_Bool bNewFile, Gan_Bool bReverseBytes, unsigned int uieolPadding,
                                             Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);
GANDALF_API Gan_Bool bWrite32BitFloatDPXImageData(FILE* pfOutFile, const Gan_Image* pgiImage, Gan_Bool bNewFile, Gan_Bool bReverseBytes, unsigned int uieolPadding,
                                                  Gan_Bool bFlip, Gan_Bool bSingleField, Gan_Bool bUpper, Gan_Bool bWholeImage);

/* forward declaration */
struct Gan_ImageReadControlStruct;
struct Gan_ImageHeaderStruct;
struct Gan_ImageWriteControlStruct;

/* Prototypes for public functions in dpx_io.c */
GANDALF_API Gan_Bool gan_image_is_dpx(const unsigned char *magic_string, size_t length);
GANDALF_API Gan_Image *gan_read_dpx_image_stream ( FILE *infile, Gan_Image *image,
                                                   const struct Gan_ImageReadControlStruct *ictrlstr, struct Gan_ImageHeaderStruct *header );
GANDALF_API Gan_Image *gan_read_dpx_image ( const char *filename, Gan_Image *image,
                                            const struct Gan_ImageReadControlStruct *ictrlstr, struct Gan_ImageHeaderStruct *header );
GANDALF_API void       gan_initialise_dpx_header_struct(Gan_DPXHeaderStruct *octrlstr, Gan_ImageFormat image_format, Gan_Type type);
GANDALF_API Gan_Bool   gan_write_dpx_image_stream ( FILE *outfile, const Gan_Image *image, Gan_Bool new_file, const struct Gan_ImageWriteControlStruct *octrlstr );
GANDALF_API Gan_Bool   gan_write_dpx_image ( const char *filename, const Gan_Image *image, const struct Gan_ImageWriteControlStruct *octrlstr );

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_IMAGE_DPX_IO_H */
