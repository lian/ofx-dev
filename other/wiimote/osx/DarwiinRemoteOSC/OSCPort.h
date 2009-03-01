//
//  OSCPort.h
//  ObjCOSC
//
//  Created by C. Ramakrishnan on Tue Oct 01 2002.
//  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OSC-client.h"

@interface OSCPort : NSObject {
    int	    _sock;
    char*   _types;
    OSCbuf* _oscBuffer;
	void*   _oscDataBuffer;
	BOOL    _ownsSocket;
}

#pragma mark _____ instance creation
// ipAddress is a character string representing a numeric address in the standard
// Internet . notation. *I don't do name lookup*
+ (id)oscPortToAddress:(const char*)ipAddress portNumber:(unsigned short)portNumber;

// socket needs to be a socket connected to the server
- (id)initWithSocket:(int)socket;

#pragma mark _____ accessing
- (int)socket;
- (BOOL)isSocketOwner;
- (void)setOwnsSocket:(BOOL)ownsSocket;

#pragma mark _____ actions
// If you use a single OSCPort in multiple threads, you need
// an NSLock/mutex around calls to these actions
- (BOOL)loadSynthDef:(char*)synthDefFilename;
- (BOOL)newSynthFromDef:(char*)synthDefName 
                synthID:(int)synthID 
            parentGroup:(int)parentGroup;
- (BOOL)freeSynth:(int)synthID;

- (BOOL)sendTo:(char*)address types:(char*)types, ...;

// build up a message progressively -- works when you
// know the signature beforehand, but don't know exactly
// what the values will be
- (void)beginSendTo:(char*)address types:(char*)types;
- (void)appendInt:(int)value;
- (void)appendFloat:(float)value;
- (void)appendString:(char*)value;
- (BOOL)completeSend;


@end
