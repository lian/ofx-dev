/**
 * File:          $RCSfile: matrixf_eigen_test.h,v $
 * Module:        Fixed size matrix eigensystem package test program
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.1 $
 * Last edited:   $Date: 2002/05/27 09:43:33 $
 * Author:        $Author: pm $
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

#include <gandalf/TestFramework/cUnit.h>

#ifndef CUNIT_MATRIXF_EIGEN_TEST_H
#define CUNIT_MATRIXF_EIGEN_TEST_H

cUnit_test_suite *matrixf_eigen_test_build_suite(void);

#endif
