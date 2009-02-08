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

#ifndef __OMNIVIDEA_FOBS_DECODER_H
#define __OMNIVIDEA_FOBS_DECODER_H

#include "common.h"

extern "C" {
#include <inttypes.h>
}

//Forward declaration of ffmpeg structs
struct AVPacket;
struct ReSampleContext;
struct AVPicture;
struct AVCodecContext;
struct AVFormatContext;
struct AVInputFormat;
struct AVRational;
struct SwsContext;

class PacketBuffer;

#ifndef AVCODEC_MAX_AUDIO_FRAME_SIZE
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000
#endif


namespace omnividea
{
namespace fobs
{


class Decoder
{
   friend class Transcoder;
   friend class Encoder;
   protected:
   
   //Streams
   int videoStreamIndex;
   int audioStreamIndex;
   bool audioEnabledFlag;
   
   bool eofReachedFlag;      /* true if eof reached */

   AVFormatContext *inputFile;
   AVInputFormat *inputFileFormat;


   bool frameFlag;
   bool opened;

   
   /*Decoded frame in different formats*/
   TimeStamp currentYuv;
   bool currentYuvFlag;
   char *yuvBytes;
   AVPicture *yuvPicture;
   uint8_t *yuvBuf;
   
   TimeStamp currentRgb;
   bool currentRgbFlag;
   AVPicture *rgbPicture;
   uint8_t *rgbBuf;

   TimeStamp currentRgba;
   bool currentRgbaFlag;
   AVPicture *rgbaPicture;
   uint8_t *rgbaBuf;

   AVPicture *decodedPicture; //Format from the video
   char filename[1024];
   

   bool incorrectPts;
   
   //Video timing data
   TimeStamp duration;
   TimeStamp position;
   TimeStamp firstVideoPosition;
   bool firstVideoPositionFlag;
   TimeStamp firstVideoFramePosition;

   //Audio frames
   uint8_t decodedAudioFrame[AVCODEC_MAX_AUDIO_FRAME_SIZE];
   int decodedAudioFrameSize;
   double audioTime; //in Seconds
   TimeStamp firstAudioFramePosition;
   TimeStamp positionAudio;
   TimeStamp firstAudioPosition;
   bool firstAudioPositionFlag;
   ReSampleContext *audioResampler;
   
   //Temporals to change size
   AVPicture *transitionPicture;
   uint8_t *transitionPictureBuf;
   AVPicture *transitionPictureRgb;
   uint8_t *transitionPictureBufRgb;

   int transitionPictureWidth;
   int transitionPictureHeight;
   //ImgReSampleContext *img_resample_ctx;
   struct SwsContext *img_resample_ctx; /* for image resampling */
   int resample_height;
   
   //Packet buffers
   PacketBuffer *videoBuffer;
   PacketBuffer *audioBuffer;


   //Private Methods
   void reset();
   inline uint _getWidth();
   inline uint _getHeight();
   ReturnCode reallocTransitionPicture(int newWidth, int newHeight);
   bool compareTimeStamps(TimeStamp t1, TimeStamp t2);
	
	bool audioResampleFlag;
	//uint8_t resampledAudioBuffer[AVCODEC_MAX_AUDIO_FRAME_SIZE];
   
   //unit conversion
   TimeStamp pts2TimeStamp(int64_t pts, AVRational *pts_timebase);
   int64_t timeStamp2pts(TimeStamp ts, AVRational *pts_timebase);

   //Packet reading
   virtual ReturnCode readNextFrame();
   virtual ReturnCode placeAtNextFrame(bool videoFrame);
   virtual ReturnCode decodeFrame();
   virtual ReturnCode decodeAudioFrame();

   ReturnCode setFrameFast(TimeStamp newPosition);
   ReturnCode setFrameClassic(TimeStamp newPosition);
   ReturnCode setAudioFast(TimeStamp newPosition);
   ReturnCode setAudioClassic(TimeStamp newPosition);
   FrameIndex frameIndexFromTimeStamp(TimeStamp t);
   TimeStamp timeStampFromFrameIndex(FrameIndex f);
   
   ReturnCode _open();
   ReturnCode _setFrame(TimeStamp newPosition);

         
   public:
   Decoder(const char *filename);
   ~Decoder();
   
   ReturnCode testOpen();
   ReturnCode testClose();
   void setAudioResampleFlag(bool flag); //cap number of channels to two - Compatibility with JMF
   ReturnCode open();
   ReturnCode close();

   //Video stream management
   bool isVideoPresent();
   virtual uint getWidth();
   virtual uint getHeight();
   virtual int getBitRate();
   virtual double getFrameRate();
   virtual TimeStamp getDurationMilliseconds();
   virtual double getDurationSeconds();
   
   //Audio stream management
   bool isAudioPresent();
   void enableAudio(bool flag);
   uint getAudioSampleRate(); //Samples per second
   uint getAudioBitRate(); //Kbits per second
	uint getAudioChannelNumber();

   TimeStamp getAVPosition();

   inline virtual char* getFileName();
   
   

   //End of stream query
   //inline virtual bool moreFrames();
   
   //Position query
   virtual FrameIndex getFrameIndex();
   inline virtual double getFrameTime();
   virtual double getNextFrameTime();
   double getAudioTime();
   
   
   //Next&Prev video frame decoding
   virtual ReturnCode nextFrame();
   virtual ReturnCode nextAudioFrame();
   virtual ReturnCode prevFrame();
   //Decoded video frame access
   virtual byte getCrFactor();
   virtual byte getCbFactor();
   virtual byte *getLuminance();
   virtual byte *getCr();
   virtual byte *getCb();
   virtual byte *getRGB();
   virtual byte *getRGBA();
   virtual byte *getRGBA(char *buf);
   byte *getRGB(int width, int height);
   ReturnCode getRawFrame(AVPicture** pict, int* pix_fmt);

   
   
   //Audio decoding
   uint8_t* getAudioSamples();
   int getAudioSamplesSize();


   //seeking functionality (video based)
   virtual ReturnCode setFrame(FrameIndex frameIndex);
   virtual ReturnCode setFrameByTime(double seconds);
   virtual ReturnCode setFrameByTime(TimeStamp milliseconds);
   virtual ReturnCode setPosition(TimeStamp milliseconds);

   //Other
   double getFirstFrameTime();
   double getFirstAudioSampleTime();
   
   AVCodecContext *getAudioCodec();
   AVCodecContext *getVideoCodec();
   
   double getTime();

};

} //namespace fobs
} //namespace omnividea
#endif
