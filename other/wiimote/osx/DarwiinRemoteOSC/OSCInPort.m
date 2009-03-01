//
//  OSCInPort.m
//  PEAM
//
//  Created by Chandrasekhar Ramakrishnan on 07.10.04.
//  Copyright 2004 __MyCompanyName__. All rights reserved.
//

#import "OSCInPort.h"

#include "OSC-common.h"
#include "NetworkUDP.h"
#include "NetworkReturnAddress.h"
#include "OSC-receive.h"
#include "OSC-priority-queue.h"
#include "OSC-string-help.h"
#include "OSC-drop.h"
#include "OSC-dispatch.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>

@interface OSCInPort(OSCInPortPrivate)
- (BOOL)createSocket;
- (BOOL)createOSCAddressSpace;
- (BOOL)initializeOSC;
- (void)cleanup;
@end


void* InitTimeMallocForOSC(int numBytes) 
{
	return malloc(numBytes);
}

// Nothing I do is really that time critical -- just use malloc at realtime
void* RealTimeMallocForOSC(int numBytes) 
{
	return malloc(numBytes);
}

@implementation OSCInPort

- (void)dealloc
{
	// Need to free OSC memory. Perhaps I should keep track
	// of OSC's calls to the provided Malloc function?
	[self cleanup];
	[super dealloc];
}

- (id)initPort:(short)port {
	self = [super init];
	if (self) {
		_port = port;
		if (![self createSocket]) {
			[self release];
			return nil;
		}
		if (![self createOSCAddressSpace]) {
			[self release];
			return nil;
		}
		if (![self initializeOSC]) {
			[self release];
			return nil;
		}
	}
	
	return self;
}

- (BOOL)createSocket
{
	struct sockaddr_in serv_addr;

	// create a UDP socket
	_socket = socket(PF_INET, SOCK_DGRAM, 0);

	if (_socket < 0)
		return NO;
	_ownsSocket = YES; 

	// bind the socket
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(_port);	
	if( bind(_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	{
		NSLog(@"Could not bind UDP socket for OSC");
		return NO;
	}

	// set the socket to non-blocking
	fcntl(_socket, F_SETFL, FNDELAY);
	return YES;
}

- (BOOL)createOSCAddressSpace
{
	// Memory tuner parameters
	struct OSCAddressSpaceMemoryTuner tun;
	tun.initNumContainers = 8;
	tun.initNumMethods = 120;
	tun.InitTimeMemoryAllocator = InitTimeMallocForOSC;
	tun.RealTimeMemoryAllocator = RealTimeMallocForOSC;
	
	// create top level address space
	_topLevelContainer = OSCInitAddressSpace(&tun);	
	
	OSCInitContainerQueryResponseInfo(&_cqinfo);
	OSCInitMethodQueryResponseInfo(&_mqinfo);

	return YES;
}

- (BOOL)initializeOSC
{
	struct OSCReceiveMemoryTuner rt;

	rt.InitTimeMemoryAllocator = InitTimeMallocForOSC;
	rt.RealTimeMemoryAllocator = RealTimeMallocForOSC;
	rt.receiveBufferSize = 1000;
	rt.numReceiveBuffers = 50;
	rt.numQueuedObjects = 100;
	rt.numCallbackListNodes = 100;

	if (!OSCInitReceive(&rt))
	{
		NSLog(@"Couldn't start OSC");
		return NO;
	}	
	
	return YES;
}

- (void)receivePacket
{
    OSCPacketBuffer pb;
    struct NetworkReturnAddressStruct *ra;
    int maxclilen = sizeof(struct sockaddr_in);
	int n;
	int capacity = OSCGetReceiveBufferSize();
	BOOL morePackets = YES;
    char *buf;

	while (morePackets) 
	{
		pb = OSCAllocPacketBuffer();
		if (!pb) 
		{
			OSCWarning("Out of memory for packet buffers---had to drop a packet!");
			return;
		}
		buf = OSCPacketBufferGetBuffer(pb);
		ra = (struct NetworkReturnAddressStruct *) OSCPacketBufferGetClientAddr(pb);
		ra->clilen = maxclilen;
		ra->sockfd = _socket;
		n = recvfrom(_socket, buf, capacity, 0, (struct sockaddr*)&(ra->cl_addr), &(ra->clilen));
		if (n > 0) 
		{
			// accept the packet
			int * sizep = OSCPacketBufferGetSize(pb);
			*sizep = n;			
			OSCAcceptPacket(pb);
			
		} else {
			OSCFreePacket(pb);
			morePackets = NO;
		}
	}
}

- (void)runListeningLoop:(id)argument
{	
	fd_set read_fds;
	int numReadyDescriptors;
	struct timeval tv;
	struct timeval* timeout;

	// to keep Cocoa happy
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
	
	_keepRunning = YES;
	while(_keepRunning) {
		[self runListenerIteration: &timeout tv: &tv];
		
		// Set up the select file descriptor lists
		FD_ZERO(&read_fds);           // clear read_fds
		FD_SET(_socket, &read_fds);   // read from the OSC socket

		// Find out which socket has data available
		numReadyDescriptors = select(_socket + 1, &read_fds, (fd_set*)NULL, (fd_set*)NULL, timeout);
		if (numReadyDescriptors < 0) 
		{
			if (!_keepRunning)
			{
				// select failed because the socket got closed... which should happen
				break;
			}

			// if select reported an error
			NSLog(@"Select failed with error %i", errno);
			break;
		}

		if(FD_ISSET(_socket, &read_fds))   // if there's a message coming in
			[self receivePacket];          // accept the packet
	}

	[pool release];
}

- (void)runListenerIteration:(struct timeval**)timeout tv:(struct timeval*)tv
{	
	OSCTimeTag currentTime, timeOfNextEvent;

	currentTime = OSCTT_CurrentTime();
	OSCInvokeAllMessagesThatAreReady(currentTime);
	timeOfNextEvent = OSCTimeTagForNextMessage();
	if (0 > OSCTT_Compare(timeOfNextEvent, OSCTT_BiggestPossibleTimeTag()))
	{
		// There's an event in the queue. Timeout the select in time for it
		OSCTT_TimeTagIntervalToTimeval(currentTime, timeOfNextEvent, tv);
		*timeout = tv;
	} else {
		// no more events in the queue. Wait until something comes in
		*timeout = NULL;
	}		
}

- (void)start {
	[NSThread detachNewThreadSelector: @selector(runListeningLoop:) toTarget: self withObject: nil];	
}

- (void)stop
{
	_keepRunning = NO;
}

- (void)cleanup
{
	if (_ownsSocket)
		close(_socket);
	_socket = NULL;
}

- (OSCcontainer)topLevelContainer { return _topLevelContainer; }

- (OSCcontainer)newContainerNamed:(char*)name {
	return [self newContainerNamed: name under: _topLevelContainer];
}

- (OSCcontainer)newContainerNamed:(char*)name under:(OSCcontainer)container {
	return OSCNewContainer(name, container, &_cqinfo);
}

- (OSCMethod)newMethodNamed:(char*)name under:(OSCcontainer)container 
	callback:(methodCallback)callback context:(void*)context
{
	return OSCNewMethod(name, container, callback, context, &_mqinfo);
}

- (void)setOwnsSocket:(BOOL)ownsSocket { _ownsSocket = ownsSocket; }

@end
