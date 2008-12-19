/*
 * File:          $RCSfile: comp_noc.h,v $
 * Module:        Numerical comparison (to be included)
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

/* declarations of functions */

GANDALF_API GAN_COMP_TYPE GAN_MAX2 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b );
GANDALF_API GAN_COMP_TYPE GAN_MIN2 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b );
GANDALF_API GAN_COMP_TYPE GAN_MAX3 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c );
GANDALF_API GAN_COMP_TYPE GAN_MIN3 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c );
GANDALF_API GAN_COMP_TYPE GAN_MAX4 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b,
                         GAN_COMP_TYPE c, GAN_COMP_TYPE d );
GANDALF_API GAN_COMP_TYPE GAN_MIN4 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b,
                         GAN_COMP_TYPE c, GAN_COMP_TYPE d );
GANDALF_API GAN_COMP_TYPE GAN_MAX5 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e );
GANDALF_API GAN_COMP_TYPE GAN_MIN5 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e );
GANDALF_API GAN_COMP_TYPE GAN_MAX6 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e, GAN_COMP_TYPE f );
GANDALF_API GAN_COMP_TYPE GAN_MIN6 ( GAN_COMP_TYPE a, GAN_COMP_TYPE b, GAN_COMP_TYPE c,
                         GAN_COMP_TYPE d, GAN_COMP_TYPE e, GAN_COMP_TYPE f );

#undef GAN_COMP_TYPE
#undef GAN_MAX2
#undef GAN_MIN2
#undef GAN_MAX3
#undef GAN_MIN3
#undef GAN_MAX4
#undef GAN_MIN4
#undef GAN_MAX5
#undef GAN_MIN5
#undef GAN_MAX6
#undef GAN_MIN6
