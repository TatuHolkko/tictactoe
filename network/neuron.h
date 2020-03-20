#ifndef NEURON_H
#define NEURON_H

#include "node.h"
#include <vector>

using namespace std;

class Neuron: public INode
{
public:
    Neuron(const float& value);

    void update();

    float value() const;

    virtual void connect(const INode& to, const float& weight);

    void enable_bias();

    void disable_bias();

private:
    //connection to previous layer
    struct Connection
    {
        const INode* node;
        const float* weight;
    };

    //connections to the previous layer
    vector<Connection> connections_;

    //bias of the neuron
    const float* bias_;

    //if this is false, bias does not affect the activation
    bool bias_enabled_ = true;

    //current activation value
    float value_ = 0;

protected:
    //return the activation of this neuron for given sum from
    //connections
    float activation_function(float sum);
};

#endif // NEURON_H
