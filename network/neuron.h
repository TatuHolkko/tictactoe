#ifndef NEURON_H
#define NEURON_H

#include "node.h"
#include <vector>

using namespace std;

class Neuron: public INode
{
public:
    Neuron();

    void update();

    float value() const;

    virtual void connect(const INode& to, const float& weight);

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
    float bias_;

    //current activation value
    float value_;

protected:
    //return the activation of this neuron for given sum from
    //connections
    float activation_function(float sum);
};

#endif // NEURON_H
