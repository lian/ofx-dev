#ifndef OFXNEURALNETWORK_H_INCLUDED
#define OFXNEURALNETWORK_H_INCLUDED

#include "NeuralNetwork.h"
#include "ofxProcessing.h"
#include "ofxVectorMath.h"

/*
	A memoryState is used for storing an input-expected pair. Once a pair is
	created, it can be learned again in the future instead of being re-created
	each time.
*/

class MemoryState {
public:
	vector<float> *input, *expected;
	MemoryState(vector<float>* input, vector<float>* expected) {
		this->input = input;
		this->expected = expected;
	}
	~MemoryState() {
		delete input;
		delete expected;
	}
};

/*
	Another way to do this wrapper instead of using minInput, minOutput, etc,
	is to have all inputs inherit a class, like "bounded", that allows you to convert
	from arbitary ranges into other arbitrary ranges by storing a min and max for
	each dimension.
*/

template <class T>
class ofxNeuralNetwork {
public:
	ofxNeuralNetwork<T>(vector<T>& minInput, vector<T>& maxInput, vector<int>& topology,
		vector<T>& minOutput, vector<T>& maxOutput, int resolution) {
		this->minInput = &minInput;
		this->maxInput = &maxInput;
		this->minOutput = &minOutput;
		this->maxOutput = &maxOutput;

		this->pointLength = ofxPointLength(T());
		this->nodesPerPoint = resolution * pointLength;

		vector<int> dimensions;
		dimensions.push_back(minInput.size() * nodesPerPoint);
		for(int i = 0; i < topology.size(); i++)
			dimensions.push_back(topology[i]);
		dimensions.push_back(minOutput.size() * pointLength);
		this->nn = new NeuralNetwork(dimensions);

		this->resolution = resolution;
		this->markerSpacing = 1 / (float) resolution;
	}
	vector<T>* run(vector<T> &input) {
		vector<float>* floatInput = makeNodes(input, minInput, maxInput);
		vector<float>* floatOut = nn->run(*floatInput);
		delete floatInput;
		vector<T>* pointOut = new vector<T>();
		for(int i = 0; i < minOutput->size(); i++) {
			T curPoint;
			for(int j = 0; j < pointLength; j++)
				curPoint[j] = floatOut->at(i * pointLength + j);
			pointOut->push_back(curPoint);
		}
		delete floatOut;
		denorm(pointOut, minOutput, maxOutput);
		return pointOut;
	}
	void learn(vector<T> &input, vector<T> &expected) {
		vector<float>* inputState = makeNodes(input, minInput, maxInput);
		vector<float>* expectedState = makeExpected(expected, minOutput, maxOutput);
		nn->learn(*inputState, *expectedState);
		memory.push_back(new MemoryState(inputState, expectedState));
	}
	int memorySize() {
		return memory.size();
	}
	void relearn(int i) {
		MemoryState* curState = memory[i];
		nn->learn(*(curState->input), *(curState->expected));
	}
	~ofxNeuralNetwork() {
		for(int i = 0; i < memorySize(); i++)
			delete memory[i];
		delete nn;
	}
private:
	NeuralNetwork* nn;
	vector<ofxPoint2f> *minInput, *maxInput, *minOutput, *maxOutput;
	int resolution, pointLength, nodesPerPoint;
	float markerSpacing;
	vector<MemoryState*> memory;
	float norm(float x, float min, float max) {
		return ofConstrain(ofMap(x, min, max, -1, +1), -1, +1);
	}
	T* norm(T &x, T &min, T &max) {
		T* out = new T();
		for(int i = 0; i < pointLength; i++)
			(*out)[i] = norm(x[i], min[i], max[i]);
		return out;
	}
	void denorm(T& x, T& min, T& max) {
		for(int i = 0; i < pointLength; i++)
			x[i] = ofMap(x[i], -1, +1, min[i], max[i]);
	}
	void denorm(vector<T>* x, vector<T>* min, vector<T>* max) {
		for(int i = 0; i < x->size(); i++)
			denorm(x->at(i), min->at(i), max->at(i));
	}
	vector<float>* segment(float x) {
		x = ofMap(x, -1, +1, 0, 1);
		vector<float>* out = new vector<float>(resolution);
		for(int i = 0; i < resolution; i++) {
			float curMarker = i * markerSpacing;
			out->at(i) = ofConstrain(ofMap(fabs(curMarker - x) * resolution, 0, 1, -1, +1), -1, +1);
		}
		float wrap = ofConstrain(ofMap(fabs(1 - x) * resolution, 0, 1, -1, +1), -1, +1);
		if(wrap < out->at(0))
			out->at(0) = wrap;
		return out;
	}
	vector<float>* makeNodes(vector<T>& x, vector<T>* min, vector<T>* max) {
		vector<T*> points;
		for(int i = 0; i < x.size(); i++)
			points.push_back(norm(x.at(i), min->at(i), max->at(i)));
		int n = points.size();
		vector<float>* nodes = new vector<float>(n * nodesPerPoint);
		int nodePosition = 0;
		for(int i = 0; i < n; i++) {
			T curPoint = *(points[i]);
			for(int j = 0; j < pointLength; j++) {
				vector<float>* curSegment = segment(curPoint[j]);
				for(int k = 0; k < resolution; k++)
					nodes->at(nodePosition++) = curSegment->at(k);
				delete curSegment;
			}
		}
		for(int i = 0; i < points.size(); i++)
			delete points[i];
		return nodes;
	}
	vector<float>* makeExpected(vector<T>& x, vector<T>* min, vector<T>* max) {
		vector<float>* nodes = new vector<float>(min->size() * pointLength);
		for(int i = 0; i < x.size(); i++) {
			T cur = x[i];
			T curMin = min->at(i);
			T curMax = max->at(i);
			for(int j = 0; j < pointLength; j++)
				nodes->at(i * pointLength + j) = ofConstrain(ofMap(cur[j], curMin[j], curMax[j], -1, +1), -1, +1);
		}
		return nodes;
	}
};

int ofxPointLength(ofxPoint2f p) {
	return 2;
}
int ofxPointLength(ofxPoint3f p) {
	return 3;
}
int ofxPointLength(ofxPoint4f p) {
	return 4;
}

#endif // OFXNEURALNETWORK_H_INCLUDED
