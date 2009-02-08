/******************************************************************************
* FOBS Header File
* Copyright (c) 2004 Omnividea Multimedia S.L
* Coded by Jos San Pedro Wandelmer
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

#ifndef __OMNIVIDEA_FOBS_ENCODER_H
#define __OMNIVIDEA_FOBS_ENCODER_H

#include "Decoder.h"

//Forward declarations
struct AVStream;
struct AVCodec;
struct AVFormatContext;
struct AVOutputFormat;
struct SwsContext;


namespace omnividea
{
namespace fobs
{

	
typedef enum encoding_mode_t{
	ENCODE_COPY = -1,
	ENCODE_NONE = 0,
	ENCODE_FULL = 1
};

class Encoder
{
    friend class Transcoder;
   //AVInputFile fileInfo;
   AVFormatContext *outputFile;
   AVOutputFormat *outputFileFormat;
   AVCodec *vcodec;
   AVCodec *acodec;
   

   static const int videoBufferSize;
   uint8_t *videoBuffer;
    
   unsigned long currentFrame;
   bool opened;
   int width, height;
   double frameRate, bitRate;

   //TimeStamp currentRgb;
   
   //Reescaling temporal picture
   AVPicture *transitionPicture;
   uint8_t *transitionPictureBuf;
   int transitionPictureWidth;
   int transitionPictureHeight;
   //ImgReSampleContext *img_resample_ctx;
   struct SwsContext *img_resample_ctx; /* for image resampling */
   
   //Resampling audio
   uint8_t *audioResamplerBuf;
   int audioResamplerChannels;
   int audioResamplerSampleRate;
   ReSampleContext *audioResampler;
   
   //Audio Output
   uint8_t *audioOutputBuf;
   int audioOutputBufSize;

   uint8_t *samplesStorage;
   int samplesStorageSize;

   AVPicture *pictureToEncode;
   uint8_t *pictureToEncodeBuf;
   
   char *filename;
   
   encoding_mode_t encodeAudio, encodeVideo;

   //Encoding parameters: VIDEO
   //enum CodecType vcodecType;
   int vcodecType;
   int vcodecId;
   unsigned int vcodecTag;
	int vcodecFrameRate_num;
	int vcodecFrameRate_den;
   //enum PixelFormat vcodecPixelFormat;// = PIX_FMT_YUV420P
   int vcodecPixelFormat;
   int videoStream_time_base_num;
   int videoStream_time_base_den;
   AVCodecContext *iVideoCodec;


   //Encoding parameters: AUDIO
   //enum CodecType acodecType;
   int acodecType;
   //enum CodecID acodecId;
   int acodecId;
   unsigned int acodecTag;
   int acodecSampleRate;
   int acodecChannels;
   int acodecFrameSize;
   double acodecBitRate;
   int audioStream_time_base_num;
   int audioStream_time_base_den;
   AVCodecContext *iAudioCodec;
   
   //Incoming video first time_stamp
   int64_t start_time;
      
   //Encoding streams
   AVStream *videoStream;
   AVStream *audioStream;
   int videoStreamIndex;
   int audioStreamIndex;

   //Private Methods
   ReturnCode chooseCodec();
   ReturnCode chooseFormat();
   ReturnCode reallocTransitionPicture(int newWidth, int newHeight);
   ReturnCode reallocAudioResampler(int newChannels, int newSampleRate);
   
   ReturnCode testOpen();
   ReturnCode testClose();
   
   ReturnCode chooseCodec(char *name, int type);

   
   public:
   Encoder(const char *filename);
   ~Encoder();

   ReturnCode chooseVideoCodec(char *name);
   ReturnCode chooseAudioCodec(char *name);
   ReturnCode chooseFormat(char *name);
   ReturnCode setAudioParameters(Decoder *d);
   ReturnCode setAudioParameters(int sampleRate, int channels, double bitrate, char *acodec);
   ReturnCode setVideoParameters(Decoder *d);
   ReturnCode setVideoParameters(int width, int height, double bitRate, double frameRate, char *vcodec);

   //Get video encoding information
   int getWidth();
   int getHeight();
   double getBitRate();
   double getFrameRate();

   //Initialization & Finalization
   ReturnCode open();
   void close();
   
   //New frame encode
   ReturnCode addFrame(char *rgbFrame, int width, int height);
   ReturnCode addAudioFrame(uint8_t *samples, int samplesSize, int channels, int sampleRate);

   ReturnCode addRawFrame(AVPicture *pict, int width, int height, int pix_fmt);

   ReturnCode addSequence(Decoder* decoder, TimeStamp start, TimeStamp length);
   ReturnCode addSequence(Decoder* decoder, FrameIndex startFrame, FrameIndex length);

   ReturnCode addPacket(AVPacket *pkt);   
};

}
}
#endif
