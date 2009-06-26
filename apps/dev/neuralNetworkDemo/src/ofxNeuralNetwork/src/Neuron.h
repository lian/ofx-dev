#ifndef NEURON_H
#define NEURON_H

#include <cmath>

#include <vector>
using std::vector;

#include "Connection.h"
class Connection;

class Neuron {
public:
	float activation, delta;
	Neuron();
	void addOut(Connection*);
	void addIn(Connection*);
	void resetActivation();
	void setActivation(float);
	void activate(float);
	void forwardPropagate(bool);
	void backPropagate(float);
	void backPropagate();
	void modifyWeights(float);
	~Neuron();
private:
	vector<Connection*> outs, ins;
};

#endif // NEURON_H
