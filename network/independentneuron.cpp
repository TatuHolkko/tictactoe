#include "independentneuron.h"

IndependentNeuron::IndependentNeuron()
{

}

void IndependentNeuron::connect(const INode &to, const float &weight)
{
    weights_.push_back(weight);
    Neuron::connect(to, weight);
}

void IndependentNeuron::set_weights(const vector<float>& weights)
{
    weights_ = weights;
}
