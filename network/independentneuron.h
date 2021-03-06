#ifndef INDEPENDENTNEURON_H
#define INDEPENDENTNEURON_H

#include "neuron.h"
#include "weighted.h"

using namespace std;

class IndependentNeuron: public Weighted, public Neuron
{
public:
    IndependentNeuron();

    void connect(const INode& to, const float& weight);

    void set_weights(const vector<float>& weights);
};

#endif // INDEPENDENTNEURON_H
