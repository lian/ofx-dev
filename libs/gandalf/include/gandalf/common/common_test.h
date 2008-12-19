/**
 * File:          $RCSfile: common_test.h,v $
 * Module:        Common package test program
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.4 $
 * Last edited:   $Date: 2002/05/27 09:41:57 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 *
 * Notes:         Tests parts of the common package
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

#ifndef CUNIT_COMMON_TEST_H
#define CUNIT_COMMON_TEST_H

cUnit_test_suite * common_test_build_suite(void);

#endif
