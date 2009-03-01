#import "AppController.h"

 
@implementation AppController



- (IBAction)setForceFeedbackEnabled:(id)sender
{
	[wii setForceFeedbackEnabled:[sender state]];
}


- (IBAction)setIRSensorEnabled:(id)sender
{
	[wii setIRSensorEnabled:[sender state]];
}


- (IBAction)setLEDEnabled:(id)sender
{

	[wii setLEDEnabled1:[led1 state] enabled2:[led2 state] enabled3:[led3 state] enabled4:[led4 state]];

}


- (IBAction)setMotionSensorsEnabled:(id)sender
{
	[wii setMotionSensorEnabled:[sender state]];
}


- (IBAction)doCalibration:(id)sender{
	
	//id config = [mappingController selection];
	
	
	if ([sender tag] == 0){
		x1 = tmpAccX;
		y1 = tmpAccY;
		z1 = tmpAccZ;
	}
	
	if ([sender tag] == 1){
		x2 = tmpAccX;
		y2 = tmpAccY;
		z2 = tmpAccZ;
	}
	if ([sender tag] == 2){
		x3 = tmpAccX;
		y3 = tmpAccY;
		z3 = tmpAccZ;
	}
	x0 = (x1 + x2) / 2.0;
	y0 = (y1 + y3) / 2.0;
	z0 = (z2 + z3) / 2.0;
	
	[textView setString:[NSString stringWithFormat:@"%@\n===== x: %d  y: %d  z: %d =====", [textView string], tmpAccX, tmpAccY, tmpAccZ]];

}


void PrintOSCArgs(int arglen, const void* args)
{
	const char* myArgTypes = (const char*) args;
	const char* myArgs = myArgTypes + OSCPaddedStrlen(myArgTypes);
	
	while (*myArgTypes != '\0') {

		switch (*myArgTypes) {
			case 'i':
				NSLog(@"\t\tread int %u", *((const int*)myArgs));
				myArgs += sizeof(int);
				break;
			case 'f':
				NSLog(@"\t\tread float %u", *((const float*)myArgs));
				myArgs += sizeof(float);			
				break;
			case 's':
				NSLog(@"\t\tread string %s", myArgs);
				myArgs += OSCPaddedStrlen(myArgs);						
				break;
		}
		myArgTypes++;
	}
}



#pragma mark _____ OSC Callbacks
BOOL ReadOSCInts(int arglen, const void* args, int numInts, int* outInts, NSString* errorMessage)
{
	unsigned i;
	char* errorMsg;
	const char* typeString;
	const char* remainingArgs;
	char desiredTypeString[numInts + 1];

	typeString = args;
	
	// create the desired type string
	desiredTypeString[0] = ',';
	for (i = 0; i < numInts; i++)
		desiredTypeString[i + 1] = 'i';

	// make sure the arguments are correct -- strncmp returns 0 on a match
	if (strncmp(typeString, desiredTypeString, numInts + 1))
	{
		return NO;
	}
	
	// get the arguments after the type tag
	remainingArgs = OSCDataAfterAlignedString(args, args + arglen, &errorMsg);
	if (!remainingArgs)
	{
		NSLog(@"Problem with OSC reading note off arguments");
		return NO;
	}
	
	// read out the parameters
	for(i = 0 ; i < numInts; i++)
	{
		outInts[i] = ((const int*)remainingArgs)[0];
		remainingArgs += 4;
	}
	
	return YES;
}

void GetBatteryLevel(void *context, int arglen, const void *args, 
	OSCTimeTag when, NetworkReturnAddressPtr returnAddr)
{
	[context sendBatteryLevel];
}


SetForceFeedback(void *context, int arglen, const void *args, 
	OSCTimeTag when, NetworkReturnAddressPtr returnAddr)
{
	int receivedArgs[1];
	NSString* errorMessage = @"Incorrect arguments to noteOn. Arguments should be int channel, int note, int velocity";
	if (ReadOSCInts(arglen, args, 1, receivedArgs, errorMessage))
	if(receivedArgs[0]==0) {	
		[context setForceFeedback:NO];
	} else {
		[context setForceFeedback:YES];
	}
}


void SetLED(void *context, int arglen, const void *args, 
	OSCTimeTag when, NetworkReturnAddressPtr returnAddr)
{
	int receivedArgs[4];
	NSString* errorMessage = @"Incorrect arguments to setLED.";
	if (ReadOSCInts(arglen, args, 4, receivedArgs, errorMessage)) {
		[context setLeds:(receivedArgs[0]==0) ? NO:YES theEnabled2:(receivedArgs[1]==0) ? NO:YES theEnabled3:(receivedArgs[2]==0) ? NO:YES theEnabled4:(receivedArgs[3]==0) ? NO:YES];
	}
}


-(void)setLeds:(BOOL)theEnabled1 theEnabled2:(BOOL)theEnabled2 theEnabled3:(BOOL)theEnabled3 theEnabled4:(BOOL)theEnabled4 {
	[wii setLEDEnabled1:theEnabled1 enabled2:theEnabled2 enabled3:theEnabled3 enabled4:theEnabled4];
}


-(void)setForceFeedback:(BOOL)mode {
	[wii setForceFeedbackEnabled:mode];
}



-(void)sendBatteryLevel {
	NSLog(@"sending batterylevel");
	[port sendTo:"/wii/batterylevel" types:"f", (float)[wii batteryLevel]];	
}


- (id)init{
	char address[16];
	
    unsigned short	portNumber = portno;

	// set the address
	memset(address, 0, sizeof(address));
    strcpy(address, "127.0.0.1");
	
    
	// sending OSC port 
	NSLog(@"Connecting to %s:%hu...", address, portNumber);
    port   = [OSCPort oscPortToAddress:address portNumber: portNumber];
	[port retain];
	[port sendTo:"/wii/connected" types:"i", 1];	

	
	// receive OSC messages.
	portIn = [[OSCInPort alloc] initPort: 5601];
	OSCcontainer wiiContainer = [portIn newContainerNamed: "wii"];
	[portIn newMethodNamed: "batterylevel" under: wiiContainer callback:GetBatteryLevel context: self];
	[portIn newMethodNamed: "forcefeedback" under: wiiContainer callback:SetForceFeedback context: self];
	[portIn newMethodNamed: "led" under: wiiContainer callback:SetLED context: self];
	[portIn start];
	
	
	
	
	modes = [[NSArray arrayWithObjects:@"Nothing", @"Key", @"\tReturn", @"\tTab", @"\tEsc", @"\tBackspace", @"\tUp", @"\tDown", @"\tLeft",@"\tRight", @"\tPage Up", @"\tPage Down", @"Left Click", @"Left Click2", @"Right Click", @"Right Click2", @"Toggle Mouse (Motion)", @"Toggle Mouse (IR)",nil] retain];

	
	id transformer = [[[WidgetsEnableTransformer alloc] init] autorelease];
	[NSValueTransformer setValueTransformer:transformer forName:@"WidgetsEnableTransformer"];

	id transformer3 = [[[WidgetsEnableTransformer2 alloc] init] autorelease];
	[NSValueTransformer setValueTransformer:transformer3 forName:@"WidgetsEnableTransformer2"];

	NSSortDescriptor* descriptor = [[[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES] autorelease];
	configSortDescriptors = [[NSArray arrayWithObjects:descriptor, nil] retain];
	return self;
}

-(void)awakeFromNib{
	
	mouseEventMode = 0;
	discovery = [[WiiRemoteDiscovery alloc] init];
	[discovery setDelegate:self];
	[discovery start];
	[drawer open];
	[textView setString:@"\nDarwiinRemote OSC 0.2.1 \ndefault osc remote address: 127.0.0.1:5600 (make changes in the preferences)\ndefault osc receiving port is 5601\n\nPlease press button 1 and button 2 simultaneously"];
	point.x = 0;
	point.y = 0;
	previousPoint.x = 0; 
	previousPoint.y = 0;
		
	[[NSNotificationCenter defaultCenter] addObserver:self
														selector:@selector(expansionPortChanged:)
														name:@"WiiRemoteExpansionPortChangedNotification"
														object:nil];
	
	


}

- (void)expansionPortChanged:(NSNotification *)nc{
	WiiRemote* tmpWii = (WiiRemote*)[nc object];
	if (![[tmpWii address] isEqualToString:[wii address]]){
		return;
	}
	
	if ([tmpWii isExpansionPortAttached]){
		[tmpWii setExpansionPortEnabled:YES];

	}else{
		[tmpWii setExpansionPortEnabled:NO];

	}
	
}




//delegats implementation

- (void) WiiRemoteDiscovered:(WiiRemote*)wiimote {
	wii = wiimote;
	[wiimote setDelegate:self];
	[textView setString:[NSString stringWithFormat:@"%@\n===== Connected to WiiRemote =====", [textView string]]];

	[wiimote setLEDEnabled1:NO enabled2:YES enabled3:NO enabled4:NO];
	[wiimote setMotionSensorEnabled:YES];
	//[wiimote setIRSensorEnabled:YES];
	[discovery stop];
	[graphView startTimer];
	[graphView2 startTimer];
	
	[port sendTo:"/wii/connected" types:"i", 1];	
		
	NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
}


- (void) WiiRemoteDiscoveryError:(int)code {
	[textView setString:[NSString stringWithFormat:@"%@\n===== WiiRemoteDiscovery error (%d) =====", [textView string], code]];
	[port sendTo:"/wii/connected" types:"i", 0];	
}



- (void) wiiRemoteDisconnected:(IOBluetoothDevice*)device {
	[textView setString:[NSString stringWithFormat:@"%@\n===== lost connection with WiiRemote =====", [textView string]]];
	[wii release];
	wii = nil;
	[discovery start];
	[textView setString:[NSString stringWithFormat:@"%@\nPlease press the synchronize button", [textView string]]];
	[port sendTo:"/wii/connected" types:"i", 0];	
}


- (void) rawIRData:(IRData[4])irData  wiiRemote:(WiiRemote*)wiiRemote{
		
		[irPoint1X setStringValue: [NSString stringWithFormat:@"%00X", irData[0].x]];		
		[irPoint1Y setStringValue: [NSString stringWithFormat:@"%00X", irData[0].y]];		
		[irPoint1Size setStringValue: [NSString stringWithFormat:@"%00X", irData[0].s]];		

		[irPoint2X setStringValue: [NSString stringWithFormat:@"%00X", irData[1].x]];		
		[irPoint2Y setStringValue: [NSString stringWithFormat:@"%00X", irData[1].y]];		
		[irPoint2Size setStringValue: [NSString stringWithFormat:@"%00X", irData[1].s]];		

		[irPoint3X setStringValue: [NSString stringWithFormat:@"%00X", irData[2].x]];		
		[irPoint3Y setStringValue: [NSString stringWithFormat:@"%00X", irData[2].y]];		
		[irPoint3Size setStringValue: [NSString stringWithFormat:@"%00X", irData[2].s]];		
	
		[irPoint4X setStringValue: [NSString stringWithFormat:@"%00X", irData[3].x]];		
		[irPoint4Y setStringValue: [NSString stringWithFormat:@"%00X", irData[3].y]];		
		[irPoint4Size setStringValue: [NSString stringWithFormat:@"%00X", irData[3].s]];
		
		
		[port sendTo:"/wii/irdata" types:"ffffffffffff", 
		(float)irData[0].x/1023,(float)irData[0].y/1023,(float)irData[0].s,
		(float)irData[1].x/1023,(float)irData[1].y/1023,(float)irData[1].s,
		(float)irData[2].x/1023,(float)irData[2].y/1023,(float)irData[2].s,
		(float)irData[3].x/1023,(float)irData[3].y/1023,(float)irData[3].s
		];
}


- (void) irPointMovedX:(float)px Y:(float)py  wiiRemote:(WiiRemote*)wiiRemote{
	if (mouseEventMode != 2)
		return;
	
	BOOL haveMouse = (px > -2)?YES:NO;
	
	if (!haveMouse) {
		[graphView setIRPointX:-2 Y:-2];
		[port sendTo:"/wii/irpoint" types:"ff", -2,-2];
		return;
	} else {
		[graphView setIRPointX:px Y:py];
		[port sendTo:"/wii/irpoint" types:"ff", px,py];

	}
	
	
	int dispWidth = CGDisplayPixelsWide(kCGDirectMainDisplay);
	int dispHeight = CGDisplayPixelsHigh(kCGDirectMainDisplay);
	
	float sens2 = 1.0;
	float newx = (px*1*sens2)*dispWidth + dispWidth/2;
	float newy = -(py*1*sens2)*dispWidth + dispHeight/2;
	
	if (newx < 0) newx = 0;
	if (newy < 0) newy = 0;
	if (newx >= dispWidth) newx = dispWidth-1;
	if (newy >= dispHeight) newy = dispHeight-1;
	
	float dx = newx - point.x;
	float dy = newy - point.y;
	
	float d = sqrt(dx*dx+dy*dy);

	
	
	// mouse filtering
	if (d < 20) {
		point.x = point.x * 0.9 + newx*0.1;
		point.y = point.y * 0.9 + newy*0.1;
	} else if (d < 50) {
		point.x = point.x * 0.7 + newx*0.3;
		point.y = point.y * 0.7 + newy*0.3;
	} else {
		point.x = newx;
		point.y = newy;
	}
	
	if (point.x > dispWidth)
		point.x = dispWidth - 1;
	
	if (point.y > dispHeight)
		point.y = dispHeight - 1;
	
	if (point.x < 0)
		point.x = 0;
	if (point.y < 0)
		point.y = 0;
	
	[port sendTo:"/wii/point" types:"ff", (float)point.x, (float)point.y];
	
}



- (void) buttonChanged:(WiiButtonType)type isPressed:(BOOL)isPressed wiiRemote:(WiiRemote*)wiiRemote {
		 
	id map = nil;
	int isPressedInt = (isPressed==true) ? 1:0;
	if (type == WiiRemoteAButton){
		[aButton setEnabled:isPressed];
		[port sendTo:"/wii/button/a" types:"i", isPressedInt];	
		
	}else if (type == WiiRemoteBButton){
		[bButton setEnabled:isPressed];
		[port sendTo:"/wii/button/b" types:"i", isPressedInt];

	}else if (type == WiiRemoteUpButton){
		[upButton setEnabled:isPressed];
		[port sendTo:"/wii/button/up" types:"i", isPressedInt];

	}else if (type == WiiRemoteDownButton){
		[downButton setEnabled:isPressed];
		[port sendTo:"/wii/button/down" types:"i", isPressedInt];

	}else if (type == WiiRemoteLeftButton){
		[leftButton setEnabled:isPressed];
		[port sendTo:"/wii/button/left" types:"i", isPressedInt];

	}else if (type == WiiRemoteRightButton){
		[rightButton setEnabled:isPressed];
		[port sendTo:"/wii/button/right" types:"i", isPressedInt];

	}else if (type == WiiRemoteMinusButton){
		[minusButton setEnabled:isPressed];
		[port sendTo:"/wii/button/minus" types:"i", isPressedInt];

	}else if (type == WiiRemotePlusButton){
		[plusButton setEnabled:isPressed];
		[port sendTo:"/wii/button/plus" types:"i", isPressedInt];

	}else if (type == WiiRemoteHomeButton){
		[homeButton setEnabled:isPressed];
		[port sendTo:"/wii/button/home" types:"i", isPressedInt];

	}else if (type == WiiRemoteOneButton){
		[oneButton setEnabled:isPressed];
		[port sendTo:"/wii/button/one" types:"i", isPressedInt];

	}else if (type == WiiRemoteTwoButton){
		[twoButton setEnabled:isPressed];
		[port sendTo:"/wii/button/two" types:"i", isPressedInt];

	}else if (type == WiiNunchukCButton){
		[port sendTo:"/nunchuk/button/c" types:"i", isPressedInt];
	}else if (type == WiiNunchukZButton){
		[port sendTo:"/nunchuk/button/z" types:"i", isPressedInt];
	}
}



- (void) joyStickChanged:(WiiJoyStickType)type tiltX:(unsigned char)tiltX tiltY:(unsigned char)tiltY wiiRemote:(WiiRemote*)wiiRemote {
	if (type == WiiNunchukJoyStick){
		unsigned short max = 0xE0;
		unsigned short center = 0x80;
		
		float shiftedX = (tiltX * 1.0) - (center * 1.0);
		float shiftedY = (tiltY * 1.0) - (center * 1.0);
		
		float scaledX = (shiftedX * 1.0) / ((max - center) * 1.0);
		float scaledY = (shiftedY * 1.0) / ((max - center) * 1.0);
		
		// NSLog(@"Joystick X = %f  Y= %f", scaledX, scaledY);
		//[joystickQCView setValue:[NSNumber numberWithFloat: scaledX] forInputKey:[NSString stringWithString:@"X_Position"]];
		//[joystickQCView setValue:[NSNumber numberWithFloat: scaledY] forInputKey:[NSString stringWithString:@"Y_Position"]];
		
		//[joystickX setStringValue: [NSString stringWithFormat:@"%00X", tiltX]];		
		//[joystickY setStringValue: [NSString stringWithFormat:@"%00X", tiltY]];	
		[port sendTo:"/nunchuk/joystick" types:"ff", (float)scaledX,(float)scaledY];
	}
}





- (void) accelerationChanged:(WiiAccelerationSensorType)type accX:(unsigned char)accX accY:(unsigned char)accY accZ:(unsigned char)accZ wiiRemote:(WiiRemote*)wiiRemote{
	if (type == WiiNunchukAccelerationSensor){
		[graphView2 setData:accX y:accY z:accZ];
		[port sendTo:"/nunchuk/acc" types:"fff", (float)accX,(float)accY,(float)accZ];
		tmpAccX = accX;
		tmpAccY = accY;
		tmpAccZ = accZ;
		// values from the preset
		x0 = 128; //data.accX_zero;
		x3 = 153; //data.accX_1g;
		y0 = 129; //data.accY_zero;
		y2 = 154; //data.accY_1g;
		
		double ax = (double)(accX - x0) / (x3 - x0);
		double ay = (double)(accY - y0) / (y2 - y0);
	
		double roll = atan(ax) * 180.0 / 3.14 * 2;
		double pitch = atan(ay) * 180.0 / 3.14 * 2;	
		
		// send orientation to a remote OSC address
		[port sendTo:"/nunchuk/orientation" types:"ff", (float)roll,(float)pitch];
		return;
	}
	
	[graphView setData:accX y:accY z:accZ];
	[batteryLevel setDoubleValue:(double)[wii batteryLevel]];
	
	
	tmpAccX = accX;
	tmpAccY = accY;
	tmpAccZ = accZ;
	
	// send acceleration to a remote OSC address
	[port sendTo:"/wii/acc" types:"fff", (float)accX,(float)accY,(float)accZ];
	
	// values from the preset
	x0 = 128; //data.accX_zero;
	x3 = 153; //data.accX_1g;
	y0 = 129; //data.accY_zero;
	y2 = 154; //data.accY_1g;
		
	double ax = (double)(accX - x0) / (x3 - x0);
	double ay = (double)(accY - y0) / (y2 - y0);
	
	double roll = atan(ax) * 180.0 / 3.14 * 2;
	double pitch = atan(ay) * 180.0 / 3.14 * 2;	
	
	// send orientation to a remote OSC address
	[port sendTo:"/wii/orientation" types:"ff", (float)roll,(float)pitch];

	
	int dispWidth = CGDisplayPixelsWide(kCGDirectMainDisplay);
	int dispHeight = CGDisplayPixelsHigh(kCGDirectMainDisplay);
	
		
	point.x = previousPoint.x;
	point.y = previousPoint.y;
	
	float sens1 = 1.0;

	if (roll < -15)
		point.x -= 2 * sens1;
	if (roll < -45)
		point.x -= 4 * sens1;
	if (roll < -75)
		point.x -= 6 * sens1;
	
	if (roll > 15)
		point.x += 2 * sens1;
	if (roll > 45)
		point.x += 4 * sens1;
	if (roll > 75)
		point.x += 6 * sens1;
	
	// pitch -	-90 = vertical, IR port up
	//			  0 = horizontal, A-button up.
	//			 90 = vertical, IR port down
	
	// The "natural" hand position for the wiimote is ~ -40 up. 
	
	if (pitch < -50)
		point.y -= 2 * sens1;
	if (pitch < -60)
		point.y -= 4 * sens1;
	if (pitch < -80)
		point.y -= 6 * sens1;
	
	if (pitch > -15)
		point.y += 2 * sens1;
	if (pitch > -5)
		point.y += 4 * sens1;
	if (pitch > 15)
		point.y += 6 * sens1; 
	
	
	if (point.x < 0)
		point.x = 0;
	if (point.y < 0)
		point.y = 0;
	
	if (point.x > dispWidth)
		point.x = dispWidth - 1;
	
	if (point.y > dispHeight)
		point.y = dispHeight - 1;
	
	
	// send point to a remote OSC address.
	// point is not absolute but the difference of the current position and
	// the previous position.
	[port sendTo:"/wii/point" types:"ff", (float)point.x, (float)point.y];	
	
	previousPoint.x = point.x;
	previousPoint.y = point.y;

}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender{
	
	NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
	
	[defaults setObject:[[NSNumber alloc] initWithDouble:x1] forKey:@"x1"];
	[defaults setObject:[[NSNumber alloc] initWithDouble:y1] forKey:@"y1"];
	[defaults setObject:[[NSNumber alloc] initWithDouble:z1] forKey:@"z1"];
	
	[defaults setObject:[[NSNumber alloc] initWithDouble:x2] forKey:@"x2"];
	[defaults setObject:[[NSNumber alloc] initWithDouble:y2] forKey:@"y2"];
	[defaults setObject:[[NSNumber alloc] initWithDouble:z2] forKey:@"z2"];
	
	[defaults setObject:[[NSNumber alloc] initWithDouble:x3] forKey:@"x3"];
	[defaults setObject:[[NSNumber alloc] initWithDouble:y3] forKey:@"y3"];
	[defaults setObject:[[NSNumber alloc] initWithDouble:z3] forKey:@"z3"];
	
	
	[graphView stopTimer];
	[graphView2 stopTimer];
	[wii closeConnection];
	
	[portIn stop];
	
	return NSTerminateNow;
}

- (IBAction)openKeyConfiguration:(id)sender{
	[NSApp beginSheet:preferenceWindow
	   modalForWindow:mainWindow
        modalDelegate:self
	   didEndSelector:@selector(sheetDidEnd:returnCode:contextInfo:)
		  contextInfo:nil];
	
}



- (void)sheetDidEnd:(NSWindow *)sheetWin returnCode:(int)returnCode contextInfo:(void *)contextInfo{
	// save configutation goes here.
	[sheetWin close];
}


- (NSManagedObject*)createNewConfigration:(NSString*)name{ } // create new configuration in the prefs

- (IBAction)enterSaveName:(id)sender{
    // OK button is pushed
	if ([[newNameField stringValue] length] == 0){
		return;
	}
    [NSApp stopModalWithCode:1];
}


- (IBAction)cancelEnterSaveName:(id)sender{
	// Cancel button is pushed
    [NSApp stopModalWithCode:0];

}


- (IBAction)deleteConfiguration:(id)sender{ }


- (IBAction)setMouseModeEnabled:(id)sender{
	mouseEventMode = [sender indexOfSelectedItem];
	// maybe we dont need that.
	switch(mouseEventMode){
		case 0:
			[textView setString:[NSString stringWithFormat:@"%@\n===== Mouse Mode Off =====", [textView string]]];
			[port sendTo:"/wii/mousemode" types:"i", 0];
			break;
		case 1:
			[textView setString:[NSString stringWithFormat:@"%@\n===== Mouse Mode On (Motion Sensors) =====", [textView string]]];
			[port sendTo:"/wii/mousemode" types:"i", 1];
			break;
		case 2:
			[textView setString:[NSString stringWithFormat:@"%@\n===== Mouse Mode On (IR Sensor) =====", [textView string]]];
			[port sendTo:"/wii/mousemode" types:"i", 2];
			
	}
}


- (IBAction)setRemoteAddress:(id)sender{
   
   if ([[theRemoteAddress stringValue] length] == 0){
		return;
	}
	
	NSString *addressInput = [theRemoteAddress stringValue];
	NSNumber *portInput = [NSNumber numberWithInt:[theRemotePort intValue]];
	int myRemotePort = [portInput intValue];
	
	
	const char *temp = [addressInput fileSystemRepresentation];
	int len = strlen(temp);
	char myAddress[len+1];
	strcpy(myAddress, temp);
	
	[textView setString:[NSString stringWithFormat:@"%@\n===== changing remote address to %s : %u =====", [textView string], myAddress, myRemotePort]];
	
	port   = [OSCPort oscPortToAddress:myAddress portNumber: myRemotePort];
	[port retain];
	[port sendTo:"/wii/connected" types:"i", 1];
}


@end
