/**
 * File:          $RCSfile: compare.h,v $
 * Module:        Numerical comparison
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.11 $
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

#ifndef _GAN_COMPARE_H
#define _GAN_COMPARE_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup Common
 * \{
 */

/**
 * \addtogroup CommonCompare
 * \{
 */

/* macro comparisons for any simple C types */

#ifdef GAN_GENERATE_DOCUMENTATION
#define GAN_COMP_TYPE int
#endif

/**
 * \brief Macro: Return maximum of two values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_max2 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b );
#else
#define gan_max2(a,b) ((a) > (b) ? (a) : (b))
#endif

/**
 * \brief Macro: Return minimum of two values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_min2 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b );
#else
#define gan_min2(a,b) ((a) < (b) ? (a) : (b))
#endif

/**
 * \brief Macro: Return maximum of three values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_max3 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c );
#else
#define gan_max3(a,b,c) (gan_max2(gan_max2(a,b),c))
#endif

/**
 * \brief Macro: Return minimum of three values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_min3 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c );
#else
#define gan_min3(a,b,c) (gan_min2(gan_min2(a,b),c))
#endif

/**
 * \brief Macro: Return maximum of four values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_max4 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d );
#else
#define gan_max4(a,b,c,d) (gan_max2(gan_max2(a,b),gan_max2(c,d)))
#endif

/**
 * \brief Macro: Return minimum of four values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_min4 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d );
#else
#define gan_min4(a,b,c,d) (gan_min2(gan_min2(a,b),gan_min2(c,d)))
#endif

/**
 * \brief Macro: Return maximum of five values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_max5 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e );
#else
#define gan_max5(a,b,c,d,e) (gan_max2(gan_max3(a,b,c),gan_max2(d,e)))
#endif

/**
 * \brief Macro: Return minimum of five values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_min5 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e );
#else
#define gan_min5(a,b,c,d,e) (gan_min2(gan_min3(a,b,c),gan_min2(d,e)))
#endif

/**
 * \brief Macro: Return maximum of six values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_max6 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e, GAN_COMP_TYPE f );
#else
#define gan_max6(a,b,c,d,e,f) (gan_max2(gan_max3(a,b,c),gan_max3(d,e,f)))
#endif

/**
 * \brief Macro: Return minimum of six values of any simple type.
 */
#ifdef GAN_GENERATE_DOCUMENTATION
GANDALF_API GAN_COMP_TYPE gan_min6 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e, GAN_COMP_TYPE f );
#else
#define gan_min6(a,b,c,d,e,f) (gan_min2(gan_min3(a,b,c),gan_min3(d,e,f)))
#endif

#ifdef GAN_GENERATE_DOCUMENTATION
#undef GAN_COMP_TYPE
#endif

/* declarations of comparison functions for unsigned character type */
#define GAN_COMP_TYPE unsigned char
#define GAN_MAX2 gan_max2_uc
#define GAN_MIN2 gan_min2_uc
#define GAN_MAX3 gan_max3_uc
#define GAN_MIN3 gan_min3_uc
#define GAN_MAX4 gan_max4_uc
#define GAN_MIN4 gan_min4_uc
#define GAN_MAX5 gan_max5_uc
#define GAN_MIN5 gan_min5_uc
#define GAN_MAX6 gan_max6_uc
#define GAN_MIN6 gan_min6_uc
#include <gandalf/common/comp_noc.h>

/* declarations of comparison functions for integer type */
#define GAN_COMP_TYPE int
#define GAN_MAX2 gan_max2_i
#define GAN_MIN2 gan_min2_i
#define GAN_MAX3 gan_max3_i
#define GAN_MIN3 gan_min3_i
#define GAN_MAX4 gan_max4_i
#define GAN_MIN4 gan_min4_i
#define GAN_MAX5 gan_max5_i
#define GAN_MIN5 gan_min5_i
#define GAN_MAX6 gan_max6_i
#define GAN_MIN6 gan_min6_i
#include <gandalf/common/comp_noc.h>

/* declarations of comparison functions for unsigned integer type */
#define GAN_COMP_TYPE unsigned int
#define GAN_MAX2 gan_max2_ui
#define GAN_MIN2 gan_min2_ui
#define GAN_MAX3 gan_max3_ui
#define GAN_MIN3 gan_min3_ui
#define GAN_MAX4 gan_max4_ui
#define GAN_MIN4 gan_min4_ui
#define GAN_MAX5 gan_max5_ui
#define GAN_MIN5 gan_min5_ui
#define GAN_MAX6 gan_max6_ui
#define GAN_MIN6 gan_min6_ui
#include <gandalf/common/comp_noc.h>

/* declarations of comparison functions for long integer type */
#define GAN_COMP_TYPE long
#define GAN_MAX2 gan_max2_l
#define GAN_MIN2 gan_min2_l
#define GAN_MAX3 gan_max3_l
#define GAN_MIN3 gan_min3_l
#define GAN_MAX4 gan_max4_l
#define GAN_MIN4 gan_min4_l
#define GAN_MAX5 gan_max5_l
#define GAN_MIN5 gan_min5_l
#define GAN_MAX6 gan_max6_l
#define GAN_MIN6 gan_min6_l
#include <gandalf/common/comp_noc.h>

/* declarations of comparison functions for unsigned long integer type */
#define GAN_COMP_TYPE unsigned long
#define GAN_MAX2 gan_max2_ul
#define GAN_MIN2 gan_min2_ul
#define GAN_MAX3 gan_max3_ul
#define GAN_MIN3 gan_min3_ul
#define GAN_MAX4 gan_max4_ul
#define GAN_MIN4 gan_min4_ul
#define GAN_MAX5 gan_max5_ul
#define GAN_MIN5 gan_min5_ul
#define GAN_MAX6 gan_max6_ul
#define GAN_MIN6 gan_min6_ul
#include <gandalf/common/comp_noc.h>

/* declarations of comparison functions for double type */
#define GAN_COMP_TYPE double
#define GAN_MAX2 gan_max2_d
#define GAN_MIN2 gan_min2_d
#define GAN_MAX3 gan_max3_d
#define GAN_MIN3 gan_min3_d
#define GAN_MAX4 gan_max4_d
#define GAN_MIN4 gan_min4_d
#define GAN_MAX5 gan_max5_d
#define GAN_MIN5 gan_min5_d
#define GAN_MAX6 gan_max6_d
#define GAN_MIN6 gan_min6_d
#include <gandalf/common/comp_noc.h>

/* declarations of comparison functions for float type */
#define GAN_COMP_TYPE float
#define GAN_MAX2 gan_max2_f
#define GAN_MIN2 gan_min2_f
#define GAN_MAX3 gan_max3_f
#define GAN_MIN3 gan_min3_f
#define GAN_MAX4 gan_max4_f
#define GAN_MIN4 gan_min4_f
#define GAN_MAX5 gan_max5_f
#define GAN_MIN5 gan_min5_f
#define GAN_MAX6 gan_max6_f
#define GAN_MIN6 gan_min6_f
#include <gandalf/common/comp_noc.h>

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_COMPARE_H */
