//
//  OSCInPort.h
//  PEAM
//
//  Created by Chandrasekhar Ramakrishnan on 07.10.04.
//  Copyright 2004 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "OSC-timetag.h"
#include "OSC-address-space.h"


@interface OSCInPort : NSObject {
	// internal state
	int   _socket;
	BOOL  _ownsSocket;	
	short _port;   // UDP port I listen and send on
	BOOL  _keepRunning;
	
	// OSC state
	OSCcontainer _topLevelContainer;
	struct OSCContainerQueryResponseInfoStruct _cqinfo;
	struct OSCMethodQueryResponseInfoStruct    _mqinfo;
}

- (id)initPort:(short)port;

- (void)setOwnsSocket:(BOOL)ownsSocket;

- (OSCcontainer)topLevelContainer;
// create a sub-container. Sender needs to hold a reference to "name" -- it
// doesn't get copied
- (OSCcontainer)newContainerNamed:(char*)name; // creates sub-container of top-level
- (OSCcontainer)newContainerNamed:(char*)name under:(OSCcontainer)container;
- (OSCMethod)newMethodNamed:(char*)name 
                under:(OSCcontainer)container 
                callback:(methodCallback)callback 
                context:(void*)context;

- (void)start;
- (void)stop;

- (void)runListenerIteration:(struct timeval**)timeout tv:(struct timeval*)tv;

@end
