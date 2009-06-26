#ifndef LAYER_H
#define LAYER_H

#include <vector>
using std::vector;

#include "Neuron.h"
class Neuron;

class Layer {
public:
	Layer(int units, bool hasBias) {
		bias = hasBias ? new Neuron() : NULL;
		for(int i = 0; i < units; i++)
			neurons.push_back(new Neuron());
	}
	void forwardPropagate(bool freeze) {
    if(bias != NULL)
			bias->forwardPropagate(true);
    for(int i = 0; i < size(); i++)
      neurons[i]->forwardPropagate(freeze);
	}
	void feed(vector<float>& data) {
    for(int i = 0; i < data.size(); i++)
      neurons[i]->setActivation(data[i]);
	}
	void backPropagate(vector<float>& expected) {
    for(int i = 0; i < expected.size(); i++)
      neurons[i]->backPropagate(expected[i]);
	}
	void backPropagate() {
    for(int i = 0; i < size(); i++)
      neurons[i]->backPropagate();
	}
	void resetActivations() {
    for(int i = 0; i < size(); i++)
      neurons[i]->resetActivation();
	}
	vector<float>* activations() {
		vector<float>* activations = new vector<float>(size());
    for(int i = 0; i < size(); i++)
			activations->at(i) = neurons[i]->activation;
    return activations;
	}
	void connect(Layer* layer) {
    for(int target = 0; target < layer->size(); target++) {
      if(bias != NULL)
				new Connection(bias, layer->neurons[target]);
      for(int source = 0; source < size(); source++)
        new Connection(neurons[source], layer->neurons[target]);
    }
	}
	~Layer() {
		delete bias;
		for(int i = 0; i < size(); i++)
			delete neurons[i];
	}
private:
	Neuron* bias;
	vector<Neuron*> neurons;
	int size() {
		return neurons.size();
	}
};

#endif // LAYER_H
