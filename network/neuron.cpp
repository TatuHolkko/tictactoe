#include "neuron.h"
#include "node.h"

Neuron::Neuron()
{

}

float Neuron::value(){
    return value_;
}

void Neuron::connect(INode* to, float* weight)
{
    connections_.push_back({to, weight});
}

void Neuron::update()
{
    float sum = 0;
    //calculate weighted sum
    for (Connection conn : connections_){
        sum += conn.node->value() * *(conn.weight);
    }
    //add bias and pass the value through activation function
    value_ = activation_function(sum + bias_);
}

float Neuron::activation_function(float sum)
{
    if (sum < 0){
        return sum / 10;
    }
    return sum;
}
