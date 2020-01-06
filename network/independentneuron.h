#ifndef INDEPENDENTNEURON_H
#define INDEPENDENTNEURON_H

#include "neuron.h"

using namespace std;

class IndependentNeuron: public Neuron
{
public:
    IndependentNeuron();

    void connect(const INode& to, const float& weight);

    void set_weights(const vector<float>& weights);

private:

    vector<float> weights_;
};

#endif // INDEPENDENTNEURON_H
