/******************************************************************************
* FOBS Header File
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

#ifndef __OMNIVIDEA_FOBS_TRANSCODER_H
#define __OMNIVIDEA_FOBS_TRANSCODER_H

#include "Encoder.h"

namespace omnividea
{
namespace fobs
{

class Transcoder
{
      
   double completion;
   char *fIn;
   char *fOut;
   
   bool customVideoSettings;
   int vWidth, vHeight;
   double vBitRate, vFrameRate;
   
   bool customAudioSettings;
   int aSamplesPerSec, aChannels;
   double aBitRate;
   
   char *vCodec, *aCodec, *mFormat;
   
   bool abortSignal;
   
   Encoder *e;
   Decoder *d;
   
   public:
   Transcoder(char *fIn, char *fOut);
   ~Transcoder();
   
   ReturnCode chooseVideoCodec(int width, int height, double bitRate, double frameRate, char *fcc);
   ReturnCode chooseAudioCodec(int samplesPerSec, int channels, double bitRate, char *fcc);
   ReturnCode chooseFormat(char *fcc);

   ReturnCode transcode();
   double getCompletion();
   void abort();
};

}
}
#endif
