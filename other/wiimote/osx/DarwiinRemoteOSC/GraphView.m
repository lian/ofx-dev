#import "GraphView.h"
#import <OpenGL/OpenGL.h> 
#import <OpenGL/gl.h> 
#import <OpenGL/glu.h> 
#import "GraphPoint.h"
#import <sys/time.h>


@implementation GraphView

- (void)awakeFromNib{
	lock = [[NSLock alloc] init];
	datax = [[NSMutableArray array] retain];
	datay = [[NSMutableArray array] retain];
	dataz = [[NSMutableArray array] retain];
}

- (void) resizeView : (NSRect) rect { 
	glViewport( (GLint) rect.origin.x  , (GLint) rect.origin.y, 
				(GLint) rect.size.width, (GLint) rect.size.height ); 

} 

- (void)setIRPointX:(float)x Y:(float)y{
	_x = x;
	_y = y;
}

- (id) initWithFrame : (NSRect) frameRect{
	
	_x = _y = -2;
	
	NSOpenGLPixelFormatAttribute attr[] = { 
		NSOpenGLPFADoubleBuffer, 
		NSOpenGLPFAAccelerated , 
		NSOpenGLPFAStencilSize , 32,
		NSOpenGLPFAColorSize   , 32,
		NSOpenGLPFADepthSize   , 32,
		0
	};
	
	NSOpenGLPixelFormat* pFormat; 
	pFormat = [ [ [ NSOpenGLPixelFormat alloc ] initWithAttributes : attr ] autorelease ]; 
	self = [ super initWithFrame : frameRect pixelFormat : pFormat ];
	[ [ self openGLContext ] makeCurrentContext ];
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	[self display];
	return( self ); 
}

-(void)startTimer{
	animTimer = [NSTimer scheduledTimerWithTimeInterval:0.03 target:self selector:@selector(drawAnimation:) userInfo:nil repeats:YES];

}

- (void)stopTimer{
	[animTimer invalidate];
}

- (void) drawAnimation: (NSTimer*)timer{
	[self display];
}


- (void) drawRect : (NSRect) rect{
	[self resizeView: rect];
	struct timeval tval;
	struct timezone tzone;
	gettimeofday(&tval, &tzone);
	
	
	
	while( [datax count] && [datay count] && [dataz count] && ![self shouldDraw:[[datax objectAtIndex:0] timeValue] now:tval]){
		[datax removeObjectAtIndex: 0];
		[datay removeObjectAtIndex: 0];
		[dataz removeObjectAtIndex: 0];
	}
	
	if (![datax count] || ![datay count] || ![dataz count])
		return;

	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	struct timeval from = [[datax objectAtIndex:0] timeValue];
	
	glBegin (GL_LINE_STRIP);
	{
		int i;
		glColor4f(1.0, 0.0, 0.0, 1.0);
		for (i = 0; i < [datax count]; i++){
			GraphPoint* p = [datax objectAtIndex:i];
			float y = [p value] / (float)0xff * 2.0 - 1.0;
			float x = (float)[self timeDif:[p timeValue] subtract:from] / (float)[self timeDif:tval subtract:from] * 2.0 - 1.0;
			glVertex3f(x, y, 0.0f);
		}
		
		
	}
	glEnd();
	
	glBegin (GL_LINE_STRIP);
	{
		int i;
		glColor4f(0.0, 1.0, 0.0, 1.0);
		for (i = 0; i < [datay count]; i++){
			GraphPoint* p = [datay objectAtIndex:i];
			float y = [p value] / (float)0xff * 2.0 - 1.0;
			float x = [self timeDif:[p timeValue] subtract:from] / [self timeDif:tval subtract:from] * 2.0 - 1.0;
			glVertex3f(x, y, 0.0f);
		}
		
		
	}
	glEnd();
	
	glBegin (GL_LINE_STRIP);
	{
		int i;
		glColor4f(0.0, 0.0, 1.0, 1.0);
		for (i = 0; i < [dataz count]; i++){
			GraphPoint* p = [dataz objectAtIndex:i];
			float y = [p value] / (float)0xff * 2.0 - 1.0;
			float x = [self timeDif:[p timeValue] subtract:from] / [self timeDif:tval subtract:from] * 2.0 - 1.0;
			glVertex3f(x, y, 0.0f);
		}
		
		
	}
	glEnd();
	
	if (_x > -2){
		glColor4f(1.0, 1.0, 0.0, 1.0);
		glRectf( _x - 0.05* (rect.size.height / rect.size.width), _y - 0.05, _x + 0.05 * (rect.size.height / rect.size.width), _y + 0.05 );
	}

	
	glFinish();
	[[self openGLContext] flushBuffer];
	
}

- (float)timeDif:(struct timeval)timeVal1 subtract:(struct timeval)timeVal2{
	float dif = (float)(timeVal1.tv_sec - timeVal2.tv_sec) + (float)(timeVal1.tv_usec - timeVal2.tv_usec) / (float)1000000.0;
	
	return dif;
}

- (BOOL)shouldDraw:(struct timeval)tval now:(struct timeval)now {
	double dif = now.tv_sec - tval.tv_sec + (double)(now.tv_usec - tval.tv_usec) / 1000000.0;
	
	if (dif > SAMPLETIME){
		return NO;
	}else{
		return YES;
	}
	
}


-(void)setData:(unsigned char)x y:(unsigned char)y z:(unsigned char)z{
	struct timeval tval;
	struct timezone tzone;
	gettimeofday(&tval, &tzone);
	
	GraphPoint* pointX = [[GraphPoint alloc] initWithValue:(float)x time:tval];
	GraphPoint* pointY = [[GraphPoint alloc] initWithValue:(float)y time:tval];
	GraphPoint* pointZ = [[GraphPoint alloc] initWithValue:(float)z time:tval];
	
	[datax addObject:pointX];
	[datay addObject:pointY];
	[dataz addObject:pointZ];
	[pointX release];
	[pointY release];
	[pointZ release];

}



@end
