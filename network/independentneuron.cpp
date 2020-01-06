#include "independentneuron.h"

IndependentNeuron::IndependentNeuron()
{

}

void IndependentNeuron::connect(const INode &to, const float &weight)
{
    weights_.push_back(weight);
    Neuron::connect(to, weight);
}
