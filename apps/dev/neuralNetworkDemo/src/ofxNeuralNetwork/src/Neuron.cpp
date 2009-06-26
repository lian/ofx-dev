#include "Neuron.h"

Neuron::Neuron() {
	activation = 1;
}

void Neuron::addOut(Connection* c) {
	outs.push_back(c);
	c->source = this;
}

void Neuron::addIn(Connection* c) {
	ins.push_back(c);
	c->target = this;
}

void Neuron::resetActivation() {
	setActivation(0);
}

void Neuron::setActivation(float activation) {
	this->activation = activation;
}

void Neuron::activate(float activation) {
	this->activation += activation;
}

void Neuron::forwardPropagate(bool freeze) {
	if (!freeze)
		activation = tanh(activation);
	for (int i = 0; i < outs.size(); i++)
		outs[i]->forwardPropagate();
}

void Neuron::backPropagate(float expected) {
	modifyWeights(expected - activation);
}

void Neuron::backPropagate() {
	float diff = 0;
	for (int i = 0; i < outs.size(); i++)
		diff += outs[i]->target->delta * outs[i]->weight;
	modifyWeights(diff);
}

void Neuron::modifyWeights(float diff) {
	delta = (1 - activation * activation) * diff;
	for (int i = 0; i < ins.size(); i++)
		ins[i]->changeWeight();
}

Neuron::~Neuron() {
	for(int i = 0; i < outs.size(); i++)
		delete outs[i];
}
