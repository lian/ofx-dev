#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	int i;
	int j;
	
	ofSetFrameRate( 60 );
	
	tex.allocate( BLOBS_WIDTH, BLOBS_HEIGHT, GL_RGB );
	texPixels	= new unsigned char[ BLOBS_WIDTH * BLOBS_HEIGHT * 3 ];
	
	blogPx = new int[ BLOBS_TOTAL ];
	blogPx[ 0 ] = 0;
	blogPx[ 1 ] = 90;
	blogPx[ 2 ] = 90;

	blogPy = new int[ BLOBS_TOTAL ];
	blogPy[ 0 ] = 0;
	blogPy[ 1 ] = 120;
	blogPy[ 2 ] = 45;
	
	blogDx = new int[ BLOBS_TOTAL ];
	blogDx[ 0 ] = 1;
	blogDx[ 1 ] = 1;
	blogDx[ 2 ] = 1;
	
	blogDy = new int[ BLOBS_TOTAL ];
	blogDy[ 0 ] = 1;
	blogDy[ 1 ] = 1;
	blogDy[ 2 ] = 1;

	vy = new int[ BLOBS_TOTAL * HEIGHT ];
	vx = new int[ BLOBS_TOTAL * WIDTH ];
}

//--------------------------------------------------------------
void testApp::update()
{
	int i;
	int x;
	int y;
	
	for( i=0; i<BLOBS_TOTAL; ++i )
	{
		blogPx[ i ] += blogDx[ i ];
		blogPy[ i ] += blogDy[ i ];
		
		if( blogPx[ i ] < 0 ) 
		{
			blogDx[ i ] = 1;
		}
		if( blogPx[ i ] > BLOBS_WIDTH )
		{
			blogDx[ i ] = -1;
		}
		if( blogPy[ i ] < 0 )
		{
			blogDy[ i ] = 1;
		}
		if( blogPy[ i ] > BLOBS_HEIGHT )
		{
			blogDy[ i ] = -1;
		}
		
		for( x = 0; x < BLOBS_WIDTH; x++ )
		{
			vx[ i * BLOBS_WIDTH + x ] = (int)( pow( ( blogPx[ i ] - x ), 2 ) );
		}
		
		for( y = 0; y < BLOBS_HEIGHT; y++ )
		{
			vy[ i * BLOBS_HEIGHT + y ] = (int)( pow( ( blogPy[ i ] - y ), 2 ) );
		}
	}
	
	for( y = 0; y < BLOBS_HEIGHT; y++)
	{
		for ( x = 0; x < BLOBS_WIDTH; x++)
		{
			int j = 0;
			int m = 1;
			
			j = ( x * 3 ) + ( y * BLOBS_WIDTH * 3 );
			
			for ( i = 0; i < BLOBS_TOTAL; i++ )
			{
				// Increase this number to make your blobs bigger
				m += 60000 / ( vy[ i * BLOBS_HEIGHT + y ] + vx[ i * BLOBS_WIDTH + x ] + 1 );
			}
			
			texPixels[ j + 0 ] = (unsigned char)( 0 );
			texPixels[ j + 1 ] = (unsigned char)( MIN( 255, m + x ) );
			texPixels[ j + 2 ] = (unsigned char)( MIN( 255, ( m + x + y ) / 2 ) );
		}
	}
}

//--------------------------------------------------------------
void testApp::draw()
{
	tex.loadData( texPixels, BLOBS_WIDTH, BLOBS_HEIGHT, GL_RGB );
	tex.draw( 0, 0, WIDTH, HEIGHT);
	
//	saveOutputImage();
}

void testApp :: saveOutputImage ()
{
	char fileName[ 255 ];
	
	screenGrab.grabScreen( 0, 0, WIDTH, HEIGHT );
	
	sprintf( fileName, "glitch_%0.3i.png", screenGrabCount );
	
	screenGrab.saveImage( fileName );
	
	++screenGrabCount;
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

