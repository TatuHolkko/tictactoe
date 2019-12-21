#ifndef NEURON_H
#define NEURON_H

#include "node.h"
#include <vector>

using namespace std;

class Neuron: public INode
{
public:
    Neuron();

private:
    //connection to previous layer
    struct Connection
    {
        INode* node;
        float weight;
    };

    //connections to the previous layer
    vector<Connection> connections_;

    //bias of the neuron
    float bias;
};

#endif // NEURON_H
