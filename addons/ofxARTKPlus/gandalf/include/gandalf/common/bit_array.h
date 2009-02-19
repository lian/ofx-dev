/**
 * File:          $RCSfile: bit_array.h,v $
 * Module:        Binary array module
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.31 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
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

#ifndef _GAN_BIT_ARRAY_H
#define _GAN_BIT_ARRAY_H

#include <stdio.h>
#include <gandalf/common/misc_defs.h>
#include <gandalf/common/allocate.h>
#include <gandalf/common/memory_stack.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonArray
 * \{
 */

#ifdef GAN_UI64_MAX

/// 64-bit word
typedef gan_uint64 Gan_BitWord;
#define GAN_BITWORD_SIZE 64
#define GAN_BITWORD_FULL (gan_uint64) GAN_UINT64_MAX
#define GAN_MSB_SET (gan_uint64) 0x8000000000000000 /*(1<<63)*/
#define GAN_LSB_SET (gan_uint64) 1

#else

/// 32-bit word
typedef gan_uint32 Gan_BitWord;
#define GAN_BITWORD_SIZE 32
#define GAN_BITWORD_FULL (gan_uint32) GAN_UINT32_MAX
#define GAN_MSB_SET (gan_uint32) (1<<31)
#define GAN_LSB_SET (gan_uint32) 1

#endif

/**
 * \brief Alignment options when computing bounds of a bit array.
 */
typedef enum {GAN_WORD_ALIGNMENT, GAN_BYTE_ALIGNMENT, GAN_BIT_ALIGNMENT}
   Gan_Alignment;

/// 1-dimensional array of bits
typedef struct Gan_BitArray
{
   Gan_BitWord *data;
   unsigned int no_bits;
   unsigned int no_words;

   /* allocated number of words */
   unsigned int words_alloc;

   /* whether the data array was dynamically allocated */
   Gan_Bool data_alloc;

   /* memory stack pointer or NULL */
   Gan_MemoryStack *memory_stack;

   /* whether this structure was dynamically allocated */
   Gan_Bool alloc;
} Gan_BitArray;

GANDALF_API Gan_BitArray *gan_bit_array_form_data ( Gan_BitArray *ba,
                                        Gan_BitWord *data, unsigned data_words,
                                        unsigned int no_bits );
GANDALF_API Gan_BitArray *gan_bit_array_ms_form ( Gan_MemoryStack *ms, Gan_BitArray *ba,
                                      unsigned int no_bits );
GANDALF_API Gan_Bool gan_bit_array_set_size ( Gan_BitArray *ba, unsigned int no_bits );
GANDALF_API void     gan_bit_array_free    ( Gan_BitArray *ba );
GANDALF_API void     gan_bit_array_free_va ( Gan_BitArray *ba, ... );

/* Logic Functions */

GANDALF_API Gan_Bool      gan_bit_array_invert_i ( Gan_BitArray *ba );
GANDALF_API Gan_BitArray *gan_bit_array_invert_s ( const Gan_BitArray *ba );
GANDALF_API Gan_Bool gan_bit_array_and_i    ( Gan_BitArray *ba_dst, const Gan_BitArray *ba );
GANDALF_API Gan_Bool gan_bit_array_nand_i   ( Gan_BitArray *ba_dst, const Gan_BitArray *ba );
GANDALF_API Gan_Bool gan_bit_array_or_i     ( Gan_BitArray *ba_dst, const Gan_BitArray *ba );
GANDALF_API Gan_Bool gan_bit_array_eor_i    ( Gan_BitArray *ba_dst, const Gan_BitArray *ba );
GANDALF_API Gan_Bool gan_bit_array_andnot_i ( Gan_BitArray *ba_dst, const Gan_BitArray *ba );
GANDALF_API Gan_BitArray *gan_bit_array_and_s    ( const Gan_BitArray *ba1, const Gan_BitArray *ba2 );
GANDALF_API Gan_BitArray *gan_bit_array_nand_s   ( const Gan_BitArray *ba1, const Gan_BitArray *ba2 );
GANDALF_API Gan_BitArray *gan_bit_array_or_s     ( const Gan_BitArray *ba1, const Gan_BitArray *ba2 );
GANDALF_API Gan_BitArray *gan_bit_array_eor_s    ( const Gan_BitArray *ba1, const Gan_BitArray *ba2 );
GANDALF_API Gan_BitArray *gan_bit_array_andnot_s ( const Gan_BitArray *ba1, const Gan_BitArray *ba2 );

/* insert part of src bit array into dst bit array */
GANDALF_API Gan_Bool gan_bit_array_insert ( const Gan_BitArray *source, unsigned int offset_s,
                                      Gan_BitArray *dest,   unsigned int offset_d,
                                unsigned int no_bits );

/* set all bits in a bit array */
GANDALF_API Gan_Bool gan_bit_array_fill ( Gan_BitArray *ba, Gan_Bool val );

/* copy one bit array to another */
GANDALF_API Gan_Bool      gan_bit_array_copy_q ( const Gan_BitArray *ba_source,
                                     Gan_BitArray *ba_dest );
GANDALF_API Gan_BitArray *gan_bit_array_copy_s ( const Gan_BitArray *ba_source );

GANDALF_API Gan_BitArray *gan_bit_array_expand_q ( const Gan_BitArray *ba,
                                       const Gan_BitArray *ref_ba,
                                       Gan_BitArray *exp_ba );
GANDALF_API Gan_BitArray *gan_bit_array_expand_s ( const Gan_BitArray *ba,
                                       const Gan_BitArray *ref_ba );

/* dilate a bit array */
GANDALF_API Gan_Bool gan_bit_array_dilate_q ( Gan_BitArray *ba_source,
                                  unsigned int no_bits,
                                  Gan_BitArray *ba_dest );
GANDALF_API Gan_BitArray *gan_bit_array_dilate_s ( Gan_BitArray *ba,
                                       unsigned int no_bits );

/* shift a bit array left or right */
GANDALF_API Gan_Bool gan_bit_array_shift_q ( Gan_BitArray *ba_source,
                                 int no_bits,
                                 Gan_BitArray *ba_dest );
GANDALF_API Gan_BitArray *gan_bit_array_shift_s ( Gan_BitArray *ba,
                                      int no_bits );

/* get a set bit from a bit array */
GANDALF_API unsigned int gan_bit_array_get_first_set_bit(Gan_BitArray *ba);

/* fill part of a bit array */
GANDALF_API Gan_Bool gan_bit_array_fill_part ( Gan_BitArray *ba, unsigned int offset,
                                   unsigned int no_bits, Gan_Bool val );

/* invert part of a bit array */
GANDALF_API Gan_Bool gan_bit_array_invert_part ( Gan_BitArray *ba, unsigned int offset,
                                     unsigned int no_bits );

/* print bit array in ASCII to file */
GANDALF_API void gan_bit_array_fprint ( FILE *fp, const Gan_BitArray *ba, int indent );

/**
 * \brief Macro: Number of bit-words given number of bits.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
unsigned GAN_NO_BITWORDS ( unsigned no_bits );
#else
#define GAN_NO_BITWORDS(nb) ((nb+GAN_BITWORD_SIZE-1)/GAN_BITWORD_SIZE)
#endif

/**
 * \brief Macro: Form bit array.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_BitArray *
 gan_bit_array_form ( Gan_BitArray *ba, unsigned int no_bits );
#else
#define gan_bit_array_form(ba,nb) gan_bit_array_form_data(ba,NULL,0,nb)
#endif

/**
 * \brief Macro: Allocate new bit array.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_BitArray *gan_bit_array_alloc ( unsigned int no_bits );
#else
#define gan_bit_array_alloc(nb) gan_bit_array_form_data(NULL,NULL,0,nb)
#endif

/**
 * \brief Macro: Allocate new bit array using stack-style memory allocation.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_BitArray *gan_bit_array_ms_malloc ( unsigned int no_bits );
#else
#define gan_bit_array_ms_malloc(nb) gan_bit_array_ms_form(NULL,nb)
#endif

/**
 * \brief Macro: Print bit array in ASCII to standard output.
 *
 * Print bit array in ASCII to standard output. Implemented as a macro call
 * to gan_bit_array_fprint().
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_bit_array_print ( const Gan_BitArray *bit_array, int indent );
#else
#define gan_bit_array_print(ba,i) gan_bit_array_fprint(stdout,ba,i)
#endif

/**
 * \brief Macro: Set bit in bit list to 1 (true).
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_bit_array_set_bit ( Gan_BitArray *bit_array, int pos );
#else
#ifdef NDEBUG
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_set_bit(ba,p) \
            ((ba)->data[(p)/GAN_BITWORD_SIZE] |= ( GAN_MSB_SET >>( (p) % GAN_BITWORD_SIZE)),GAN_TRUE)
#else /* #ifndef WORDS_BIGENDIAN */
#define gan_bit_array_set_bit(ba,p) \
            ((ba)->data[(p)/GAN_BITWORD_SIZE] |= ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE)),GAN_TRUE)
#endif /* #ifdef WORDS_BIGENDIAN */
#else /* #ifndef NDEBUG */
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_set_bit(ba,p) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_set_bit",\
                          GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      ((ba)->data[(p)/GAN_BITWORD_SIZE] |= ( GAN_MSB_SET >>( (p) % GAN_BITWORD_SIZE)),GAN_TRUE))
#else /* #ifndef WORDS_BIGENDIAN */
#define gan_bit_array_set_bit(ba,p) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_set_bit",\
                          GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      ((ba)->data[(p)/GAN_BITWORD_SIZE] |= ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE)),GAN_TRUE))
#endif /* #ifdef WORDS_BIGENDIAN */
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: get bit of bit array.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_bit_array_get_bit ( const Gan_BitArray *bit_array, int pos );
#else
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_get_bit(ba,p) \
            ((ba)->data[(p)/GAN_BITWORD_SIZE] & ( GAN_MSB_SET >> ( (p) % GAN_BITWORD_SIZE)))
#else
#define gan_bit_array_get_bit(ba,p) \
            ((ba)->data[(p)/GAN_BITWORD_SIZE] & ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE)))
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: clear bit in bit list to 0 (false).
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool gan_bit_array_clear_bit ( Gan_BitArray *bit_array, int pos );
#else
#ifdef NDEBUG
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_clear_bit(ba,p) \
    ((ba)->data[(p)/GAN_BITWORD_SIZE] &= (GAN_BITWORD_FULL ^ ( GAN_MSB_SET >> ( (p) % GAN_BITWORD_SIZE))),GAN_TRUE)
#else /* #ifndef WORDS_BIGENDIAN */
#define gan_bit_array_clear_bit(ba,p) \
    ((ba)->data[(p)/GAN_BITWORD_SIZE] &= (GAN_BITWORD_FULL ^ ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE))),GAN_TRUE)
#endif /* #ifdef WORDS_BIGENDIAN */
#else /* #ifndef NDEBUG */
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_clear_bit(ba,p) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_clear_bit",GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      ((ba)->data[(p)/GAN_BITWORD_SIZE] &= (GAN_BITWORD_FULL ^ ( GAN_MSB_SET >> ( (p) % GAN_BITWORD_SIZE))),GAN_TRUE))
#else /* #ifndef WORDS_BIGENDIAN */
#define gan_bit_array_clear_bit(ba,p) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_clear_bit",GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      ((ba)->data[(p)/GAN_BITWORD_SIZE] &= (GAN_BITWORD_FULL ^ ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE))),GAN_TRUE))
#endif /* #ifdef WORDS_BIGENDIAN */
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: set/clear bit depending on Boolean argument.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_bit_array_twiddle_bit ( Gan_BitArray *bit_array, int pos, Gan_Bool val );
#else
#ifdef NDEBUG
#define gan_bit_array_twiddle_bit(ba,p,val) \
    (((val) ? gan_bit_array_set_bit(ba,p) : gan_bit_array_clear_bit(ba,p)),\
     GAN_TRUE)
#else
#define gan_bit_array_twiddle_bit(ba,p,val) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_twiddle_bit",\
                          GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      (((val) ? gan_bit_array_set_bit(ba,p) : gan_bit_array_clear_bit(ba,p)),\
       GAN_TRUE))
#endif
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */


/**
 * \brief Macro: Invert bit.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool
 gan_bit_array_invert_bit ( Gan_BitArray *bit_array, int pos );
#else
#ifdef NDEBUG
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_invert_bit(ba,p) \
            ((ba)->data[(p)/GAN_BITWORD_SIZE] ^= ( GAN_MSB_SET >>( (p) % GAN_BITWORD_SIZE)),GAN_TRUE)
#else /* #ifndef WORDS_BIGENDIAN */
#define gan_bit_array_invert_bit(ba,p) \
            ((ba)->data[(p)/GAN_BITWORD_SIZE] ^= ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE)),GAN_TRUE)
#endif /* #ifdef WORDS_BIGENDIAN */
#else /* #ifndef NDEBUG */
#ifdef WORDS_BIGENDIAN
#define gan_bit_array_invert_bit(ba,p) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_invert_bit",\
                          GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      ((ba)->data[(p)/GAN_BITWORD_SIZE] ^= ( GAN_MSB_SET >>( (p) % GAN_BITWORD_SIZE)),GAN_TRUE))
#else /* #ifndef WORDS_BIGENDIAN */
#define gan_bit_array_invert_bit(ba,p) \
     ((p)>=(ba)->no_bits \
      ? (gan_err_flush_trace(),\
         gan_err_register("gan_bit_array_invert_bit",\
                          GAN_ERROR_TOO_LARGE,""),\
         GAN_FALSE) :\
      ((ba)->data[(p)/GAN_BITWORD_SIZE] ^= ( GAN_LSB_SET << ( (p) % GAN_BITWORD_SIZE)),GAN_TRUE))
#endif /* #ifdef WORDS_BIGENDIAN */
#endif /* #ifdef NDEBUG */
#endif /* #ifdef GAN_GENERATE_DOCUMENTATION */

/**
 * \brief Macro: Dilate bit array
 * \param ba Bit array
 * \param no_pixels Number of pixels to dilate bit array
 * \return #GAN_TRUE on success, #GAN_FALSE on failure.
 *
 * Dilate input bit array \a ba by \a no_pixels, and write result in-place
 * into \a ba.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API Gan_Bool *gan_bit_array_dilate_i ( Gan_BitArray *ba, unsigned int no_pixels );
#else
#define gan_bit_array_dilate_i(ba,no_pixels) gan_bit_array_dilate_q(ba,no_pixels,ba)
#endif

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_BIT_ARRAY_H */
