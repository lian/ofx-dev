#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
using std::vector;

#include "Layer.h"

class NeuralNetwork {
public:
	NeuralNetwork(vector<int>& dimensions) {
		for (int i = 0; i < dimensions.size(); i++) {
			Layer* curLayer = new Layer(dimensions[i], i != dimensions.size() - 1);
			layers.push_back(curLayer);
			if (i > 0)
				layers[i - 1]->connect(curLayer);
		}
	}
	void learn(vector<float>& input, vector<float>& expected) {
		forwardPropagate(input);
		backPropagate(expected);
	}
	vector<float>* run(vector<float>& input) {
		forwardPropagate(input);
		return outputLayer()->activations();
	}
	void forwardPropagate(vector<float>& input) {
		for (int i = 0; i < size(); i++)
			layers[i]->resetActivations();
		inputLayer()->feed(input);
		for (int i = 0; i < size(); i++)
			layers[i]->forwardPropagate(i == 0);
	}
	void backPropagate(vector<float> &expected) {
		outputLayer()->backPropagate(expected);
		for (int i = size() - 2; i > 0; i--)
			layers[i]->backPropagate();
	}
	~NeuralNetwork() {
		for(int i = 0; i < size(); i++)
			delete layers[i];
	}
private:
	vector<Layer*> layers;
	Layer* inputLayer() {
		return layers[0];
	}
	Layer* outputLayer() {
		return layers[size() - 1];
	}
	int size() {
		return layers.size();
	}
};

#endif // NEURALNETWORK_H
