#include "independentneuron.h"

IndependentNeuron::IndependentNeuron()
{

}

void IndependentNeuron::connect(const INode &to, const float &weight)
{
    const float& new_weight = add_weight(weight);
    Neuron::connect(to, new_weight);
}

void IndependentNeuron::set_weights(const vector<float>& weights)
{
    Weighted::set_weights(weights);
}
