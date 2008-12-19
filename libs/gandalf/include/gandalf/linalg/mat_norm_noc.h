/*
 * File:          $RCSfile: mat_norm_noc.h,v $
 * Module:        Fixed size matrix projective normalisation
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.7 $
 * Last edited:   $Date: 2005/08/22 08:52:18 $
 * Author:        $Author: jps $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * Notes:         Not to be compiled separately
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

/* normalises an array of matrices B */
GANDALF_API Gan_Bool GAN_MAT_NORMALISE ( GAN_MATTYPE *B, int n, double term_threshold,
                             int max_iterations, GAN_SQUMATTYPE *Lp );
#ifdef GAN_MATT_NORMALISE
GANDALF_API Gan_Bool GAN_MATT_NORMALISE ( GAN_MATTYPE *B, int n, double term_threshold,
                              int max_iterations, GAN_SQUMATTYPE *Lp );
#endif /* #ifdef GAN_MATT_NORMALISE */
