#ifndef OFXPROCESSING_H_INCLUDED
#define OFXPROCESSING_H_INCLUDED

/*
 ofxProcessing.h, r2
 Replicating some functions from Processing
 left out of Open Frameworks.

 Some functions from r1 were included in 006
 and had to be removed in r2 to be compatible.
*/

// Output: Text Area: print() and println()

void ofPrint(const char* str) {
	printf("%s", str);
}

void ofPrint(string &str) {
	printf("%s", str.c_str());
}

void ofPrint(int i) {
	printf("%i", i);
}

void ofPrint(float f) {
	printf("%f", f);
}

void ofPrint(bool b) {
	printf("%s", b ? "true" : "false");
}

void ofPrint(char c) {
	printf("%c", c);
}

template <class T>
void ofPrint(vector<T> &vec) {
	ofPrint("{ ");
	for(int i = 0; i < vec.size(); i++) {
		ofPrint(vec.at(i));
		ofPrint(", ");
	}
	ofPrint("}");
}

void ofPrintln() {
	ofPrint("\n");
}

template <typename T>
void ofPrintln(T &obj) {
	ofPrint(obj);
	ofPrintln();
}

template <typename T>
void ofPrintln(T* obj) {
	ofPrint(obj);
	ofPrintln();
}

// Output: Image: save(), saveFrame()

void ofSave(char* filename) {
	ofImage screen;
	screen.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	screen.saveImage(filename);
}

// Shapes: ellipse() with strokeWeight and CENTER/CORNER

#define OF_ELLIPSE_CENTER 0
#define OF_ELLIPSE_CORNER 1
float ofEllipse(float x, float y, float w, float h, int mode) {
	switch(mode) {
		case OF_ELLIPSE_CENTER:
			ofEllipse(x, y, w, h);
		break;
		case OF_ELLIPSE_CORNER:
			ofEllipse(x + w, y + h, w, h);
		break;
	}
}

float ofEllipse(float x, float y, float w, float h, int mode, int strokeWeight) {
	for(int i = 0; i < strokeWeight; i++) {
		ofEllipse(x, y, w - i, h - i, mode);
		if(i != 0)
			ofEllipse(x, y, w + i, h + i, mode);
	}
}

// Transform: radians(), degrees(), rotate()

float ofRadians(float d) {
	return d * DEG_TO_RAD;
}

float ofDegrees(float r) {
	return r * RAD_TO_DEG;
}

// Math: Calculation: map(), sq(), constrain(), dist(), mag()

float ofSq(float x) {
	return x * x;
}

float ofConstrain(float x, float low, float high) {
	return x < low ? low : x > high ? high : x;
}

float ofMag(float x, float y) {
	return ofDist(0, 0, x, y);
}

float ofRandom(float max) {
	return ofRandom(0, max);
}

#endif // OFXPROCESSING_H_INCLUDED
