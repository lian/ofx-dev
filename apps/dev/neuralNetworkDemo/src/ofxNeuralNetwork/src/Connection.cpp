#include "Connection.h"

float Connection::maxInitWeight = 0.1f;
float Connection::learningRate = 0.001f;

Connection::Connection(Neuron* a, Neuron* b) {
	weight = randomWeight();
	a->addOut(this);
	b->addIn(this);
}

void Connection::forwardPropagate() {
	target->activate(source->activation * weight);
}

void Connection::changeWeight() {
	weight += learningRate * target->delta * source->activation;
}

float Connection::randomWeight() {
	float one = (float) rand() / (1 << 15);
	one = one * 2 - 1;
	return one * maxInitWeight;
}
