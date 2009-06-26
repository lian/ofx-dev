#ifndef CONNECTION_H
#define CONNECTION_H

#include <cstdlib>

#include "Neuron.h"
class Neuron;

class Connection {
public:
	static float learningRate, maxInitWeight;
	Neuron *source, *target;
	float weight;
	Connection(Neuron*, Neuron*);
	void forwardPropagate();
	void changeWeight();
private:
	float randomWeight();
};

#endif // CONNECTION_H
