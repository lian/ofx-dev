/**
 * File:          $RCSfile: linalg_test.h,v $
 * Module:        Linear algebra package test program
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.7 $
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

#ifndef CUNIT_LINALG_TEST_H
#define CUNIT_LINALG_TEST_H

cUnit_test_suite *linalg_test_build_suite(void);

#endif
