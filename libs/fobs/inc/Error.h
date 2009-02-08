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

#ifndef __OMNIVIDEA_FOBS_ERROR_H
#define __OMNIVIDEA_FOBS_ERROR_H

namespace omnividea
{
namespace fobs
{
typedef enum{
OkCode = 0,
CodecError = 1,
FormatUnsupportedError = 2,
VideoStreamMissingError = 3,
CodecUnsupportedError = 4,
VideoEndError = 5,
FrameActionError = 6,
DecoderError = 7,
EncoderError = 8,
VideoPacketBufferEmptyError = 9,
MemoryError = 10,
NotInitializedError = 11,
GenericError = 12,
FileOpenError = 13,
BadParamsError = 14,
AlreadyInitializedError = 15, 
FileWriteError = 16,
NoStreamsError = 17,
NoFrameError = 18
} ReturnCode;

bool isOk(ReturnCode error);
bool isError(ReturnCode error);
char *getErrorMessage(ReturnCode error);

typedef enum {
    NoLog = 0,
    Application = 0x1,
    Times = 2,
    Packets = 4,
    LowLevel = Times|Packets,
    All = 0xffffffff
} LogLevel;

void log(LogLevel level, char *pattern, ...);
void setLogLevel(LogLevel level);

}
}
#endif
