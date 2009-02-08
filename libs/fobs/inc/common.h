/******************************************************************************
* FOBS C++ wrapper Header 
* Copyright (c) 2004 Omnividea Multimedia S.L
* Coded by José San Pedro Wandelmer
*
*    This file is part of FOBS.
*
*    FOBS is free software; you can redistribute it and/or modify
*    it under the terms of the GNU Lesser General Public License as
*    published by the Free Software Foundation; either version 2.1 
*    of the License, or (at your option) any later version.
*
*    FOBS is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Lesser General Public License for more details.
*
*    You should have received a copy of the GNU Lesser General Public
*    License along with FOBS; if not, write to the Free Software
*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#ifndef __OMNIVIDEA_FOBS_COMMON_H
#define __OMNIVIDEA_FOBS_COMMON_H

extern "C" {
#include <inttypes.h>
}

namespace omnividea
{
namespace fobs
{
typedef int64_t TimeStamp; 
//millisecond precission - Don't change this value
#define FOBS_TIMESTAMP_UNITS_D 1000.0
#define FOBS_TIMESTAMP_UNITS_I 1000

typedef unsigned long long FrameIndex;
typedef unsigned char byte;
typedef unsigned int uint;
}
}
#include "Error.h"

#endif