/**
 * File:          $RCSfile: convolve2D_test.h,v $
 * Module:        Vision package test program
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.1 $
 * Last edited:   $Date: 2004/03/25 09:22:34 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2004 <a href="http://frav.escet.urjc.es">FRAV (Face Recognition & Artificial Vision Group)</a>
 * Notes:         Tests the 2D convolution module.
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

#include <gandalf/TestFramework/cUnit.h>

#ifndef CUNIT_CONVOLVE2D_TEST_H
#define CUNIT_CONVOLVE2D_TEST_H

cUnit_test_suite *convolve2D_test_build_suite(void);

#endif
