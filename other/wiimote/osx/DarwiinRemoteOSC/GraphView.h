/* GraphView */

#import <Cocoa/Cocoa.h>

#define SAMPLETIME 10.0

@interface GraphView : NSOpenGLView
{
	NSMutableArray* datax;
	NSMutableArray* datay;
	NSMutableArray* dataz;
	NSTimer* animTimer;
	
	NSLock* lock;
	float _x;
	float _y;
}
- (void)setIRPointX:(float)x Y:(float)y;
- (id) initWithFrame:(NSRect)frame;
-(void)setData:(unsigned char)x y:(unsigned char)y z:(unsigned char)z;
- (float)timeDif:(struct timeval)timeVal1 subtract:(struct timeval)timeVal2;
- (BOOL)shouldDraw:(struct timeval)tval now:(struct timeval)now;
- (void) drawAnimation: (NSTimer*)timer;
- (void) startTimer;
- (void) stopTimer;
@end
