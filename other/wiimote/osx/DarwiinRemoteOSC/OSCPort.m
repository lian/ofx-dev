//
//  OSCPort.m
//  ObjCOSC
//
//  Created by C. Ramakrishnan on Tue Oct 01 2002.
//  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
//

#import "OSCPort.h"
#import <sys/types.h>
#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <unistd.h>

#define DEFAULT_BUFFER_SIZE	4096
#define DEFAULT_TYPES_SIZE	255

//#define DEBUG

@implementation OSCPort

#pragma mark _____ superclass overrides
- (void)dealloc
{
    free(_oscBuffer);
	free(_oscDataBuffer);
    free(_types);
	if (_ownsSocket)
		close(_sock);
    
    [super dealloc];
}

#pragma mark _____ instance creation
+ (id)oscPortToAddress:(const char*)ipAddress portNumber:(unsigned short)portNumber
{
    struct	sockaddr_in serverAddress;
    int 	sock;

    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        NSLog(@"Couldn't create socket");
        return nil;
    }
    
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(ipAddress);
    serverAddress.sin_port        = htons(portNumber);
    
    if (connect(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        NSLog(@"Couldn't connect socket");
        return nil;
    }
    
    return [[[self alloc] initWithSocket:sock] autorelease];
}

- (id)initWithSocket:(int)socket
{
    if (!(self = [self init]))
        return nil;
    
    _sock	= socket;
    _oscBuffer	= (OSCbuf*) malloc(sizeof(OSCbuf));
	_oscDataBuffer = malloc(DEFAULT_BUFFER_SIZE);
    _types	= (char*) malloc(DEFAULT_TYPES_SIZE);
	_ownsSocket = YES;
    
    OSC_initBuffer(_oscBuffer, DEFAULT_BUFFER_SIZE, _oscDataBuffer);
    
    return self;
}

- (int)socket { return _sock; }

- (BOOL)isSocketOwner { return _ownsSocket; }

- (void)setOwnsSocket:(BOOL)ownsSocket { _ownsSocket = ownsSocket; }

#pragma mark _____ actions
- (BOOL)loadSynthDef:(char*)synthDefFilename
{
    return [self sendTo:"/d_load" types:"s", synthDefFilename];
}

- (BOOL)newSynthFromDef:(char*)synthDefName 
                synthID:(int)synthID 
            parentGroup:(int)parentGroup
{
    return [self sendTo:"/s_new" types:"sii", synthDefName, synthID, parentGroup];
}

- (BOOL)freeSynth:(int)synthID
{
    return [self sendTo:"/n_free" types:"i", synthID];
}
            
- (BOOL)sendTo:(char*)address types:(char*)types, ...
{
    // potential holders for variable arguments
    char* s;
    
    va_list args;
    va_start(args, types);
    
    [self beginSendTo:address types:types];

    // use the user supplied types for this
    while (*types) {
        switch (*types++) {
            case 'f':					// float
                [self appendFloat: (float) va_arg(args, double)];
                break;
            case 'i':					// int
                [self appendInt: va_arg(args, int)];
                break;
            case 'S':					// string
                s = va_arg(args, char*);
                OSC_writeSCStringArg(_oscBuffer, s);
                break;
            case 's':					// symbol
                [self appendString: va_arg(args, char*)];
                break;
        }
    }
    va_end(args);
    
#ifdef DEBUG
	NSLog(@"\tSending packet of size %i to %s", OSC_packetSize(_oscBuffer), OSC_getPacket(_oscBuffer));
#endif
    return [self completeSend];
}

- (void)beginSendTo:(char*)address types:(char*)types {
	// OSC-client wants types to begin with a ,
    memset(_types, 0, DEFAULT_TYPES_SIZE);
    sprintf(_types, ",%s", types);
    OSC_writeAddressAndTypes(_oscBuffer, address, _types);
}

- (void)appendInt:(int)value {
	OSC_writeIntArg(_oscBuffer, value);
}

- (void)appendFloat:(float)value {
	OSC_writeFloatArg(_oscBuffer, value);
}

- (void)appendString:(char*)value {
	OSC_writeStringArg(_oscBuffer, value);
}

- (BOOL)completeSend {
    send(_sock, OSC_getPacket(_oscBuffer), OSC_packetSize(_oscBuffer), 0);
	OSC_resetBuffer(_oscBuffer);
	
	return YES;
}

@end
