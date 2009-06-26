#ifndef _TEST_APP
#define _TEST_APP

#define width 256
#define height 256

#include "ofMain.h"
#include "ofxProcessing.h"
#include "ofxNeuralNetwork.h"

class testApp : public ofBaseApp{
public:
	NeuralNetwork* nn;
	ofTexture screen;

	void setup() {
		ofSetFrameRate(30);

		nn = NULL;
		Connection::learningRate = 0.01;
		Connection::maxInitWeight = 1;

		init();
	}

	void init(int _x=2, int _y=3, int _b=3) {
		vector<int> dimensions(3);
		dimensions[0] = _x;
		dimensions[1] = _y;
		dimensions[2] = _b;
		if(nn != NULL) delete nn;
		nn = new NeuralNetwork(dimensions);
		//if(nn == NULL) {
		//	nn = new NeuralNetwork(dimensions);
		//}

		unsigned char pixels[width * height * 3];
		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				vector<float> input(2);
				input[0] = ofMap(x, 0, width, -1, +1);
				input[1] = ofMap(y, 0, height, -1, +1);
				vector<float>* output = nn->run(input);
				int position = y * (width * 3) + (x * 3);
				for(int i = 0; i < 3; i++)
					pixels[position + i] = (unsigned char) ofMap(output->at(i), -1, +1, 0, 255);
				delete output;
			}
		}
		screen.allocate(width, height, GL_RGB);
		screen.loadData(pixels, width, height, GL_RGB);

		cout << "init x:" << _x << " y:" << _y; 
	}

	void draw() {
		screen.draw(0, 0);
	}

	void mousePressed(int x, int y, int button){
		init(x,y);
	}
};

#endif

