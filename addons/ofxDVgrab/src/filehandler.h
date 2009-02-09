/*
* filehandler.h
* Copyright (C) 2000 Arne Schirmacher <arne@schirmacher.de>
* Raw DV, JPEG, and Quicktime portions Copyright (C) 2003 Dan Dennedy <dan@dennedy.org>
* Portions of Quicktime code borrowed from Arthur Peters' dv_utils.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef _FILEHANDLER_H
#define _FILEHANDLER_H

enum { PAL_FORMAT, NTSC_FORMAT, AVI_DV1_FORMAT, AVI_DV2_FORMAT, QT_FORMAT, RAW_FORMAT, DIF_FORMAT, JPEG_FORMAT, MPEG2TS_FORMAT, OF_PIXEL_FORMAT, UNDEFINED };

#include <vector>
using std::vector;

#include <string>
using std::string;

#include "dvframe.h"

#include <sys/types.h>

/* this is a struct for each available pid */
typedef struct PayloadList {
	unsigned char	pid, state;
	struct PayloadList	*next;
} PayloadList;

enum FileCaptureMode {
	CAPTURE_IGNORE,
	CAPTURE_FRAME_APPEND,
	CAPTURE_FRAME_INSERT,
	CAPTURE_MOVIE_APPEND
};

class FileTracker
{
protected:
	FileTracker();
	~FileTracker();
public:
	static FileTracker &GetInstance( );
	void SetMode( FileCaptureMode );
	FileCaptureMode GetMode( );
	unsigned int Size();
	char *Get( int );
	void Add( const char * );
	void Clear( );
private:
	static FileTracker *instance;
	vector <char *> list;
	FileCaptureMode mode;
};

class FileHandler
{
public:

	FileHandler();
	virtual ~FileHandler();

	virtual bool GetAutoSplit();
	virtual int  GetTimeSplit();
	virtual bool GetTimeStamp();
	virtual bool GetTimeSys();
	virtual bool GetTimeCode();
	virtual string GetBaseName();
	virtual string GetExtension();
	virtual int GetMaxFrameCount();
	virtual off_t GetMaxFileSize();
	void CollectionCounterUpdate();
	virtual int GetSizeSplitMode();
	virtual off_t GetMinColSize();
	virtual off_t GetMaxColSize();
	virtual off_t GetFileSize() = 0;
	virtual int GetTotalFrames() = 0;

	virtual void SetAutoSplit( bool );
	virtual void SetTimeSplit(int secs);
	virtual void SetTimeStamp( bool );
	virtual void SetTimeSys( bool );
	virtual void SetTimeCode( bool );
	virtual void SetBaseName( const string& base );
	virtual void SetMaxFrameCount( int );
	virtual void SetEveryNthFrame( int );
	virtual void SetMaxFileSize( off_t );
	virtual void SetSizeSplitMode( int );
	virtual void SetMinColSize( off_t );
	virtual void SetMaxColSize( off_t );
	virtual void SetFilmRate( bool );
	virtual void SetRemove2332( bool );

	virtual bool WriteFrame( Frame *frame );
	virtual unsigned char * GetPixels(void) = 0;
	virtual bool FileIsOpen() = 0;
	virtual bool Create( const string& filename ) = 0;
	virtual int Write( Frame *frame ) = 0;
	virtual int Close() = 0;
	virtual bool Done( void );

	virtual bool Open( const char *s ) = 0;
	virtual int GetFrame( Frame *frame, int frameNum ) = 0;
	off_t GetLastCollectionFreeSpace()
	{
		return lastCollectionFreeSpace;
	}
	off_t GetCurrentCollectionSize()
	{
		return currentCollectionSize;
	}
	int GetFramesWritten()
	{
		return framesWritten;
	}
	virtual string GetFileName()
	{
		return filename;
	}
	virtual bool IsNewFile()
	{
		return isNewFile;
	}
	virtual bool IsFirstFile()
	{
		return isFirstFile == 0 ? false : true;
	}

protected:
	int isFirstFile;
	bool isNewFile;
	bool done;
	bool autoSplit;
	int  timeSplit;
	bool timeStamp;
	bool timeSys;
	bool timeCode;
	int maxFrameCount;
	int framesWritten;
	int everyNthFrame;
	int framesToSkip;
	off_t maxFileSize;
	off_t minColSize;
	off_t maxColSize;
	off_t currentCollectionSize;
	off_t lastCollectionFreeSpace;
	int sizeSplitMode;
	string base;
	string extension;
	string filename;
	TimeCode prevTimeCode;
	bool filmRate;
	bool remove2332;
	time_t prevTime;
};





class DVHandler: public FileHandler
{
private:

	bool isOpen;
	string filename;
	unsigned int count;
	unsigned int deinterlace;

	string file;

	int fixAspect( Frame *frame );
	bool scale( Frame *frame );
	unsigned char image_buffer_prev[720*576*3];
	unsigned char image_buffer_in[720*576*3];

public:

	unsigned char image_buffer[720*576*3];

	DVHandler( unsigned int deinterlace = 0);
	~DVHandler();

	unsigned char * GetPixels()
	{
		return &image_buffer[0];
	}

	bool FileIsOpen()
	{
		return isOpen;
	}
	bool Create( const string& filename );
	int Write( Frame *frame );
	int Close();
	off_t GetFileSize()
	{
		return 0;
	}
	int GetTotalFrames()
	{
		return 0;
	}
	bool Open( const char *s )
	{
		return false;
	}
	string GetFileName()
	{
		return file;
	}
	int GetFrame( Frame *frame, int frameNum )
	{
		return -1;
	}
};

#endif

