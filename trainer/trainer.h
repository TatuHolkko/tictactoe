#ifndef TRAINER_H
#define TRAINER_H
#include "network/neuralnetwork.h"

class trainer
{
public:
    //create a trainer for <ancestor> with <pool_size> copies of it fighting in each generation
    trainer(neuralnetwork& ancestor, int pool_size);
    //iterate <n> generations of evolutionary progress
    void iterate(int n);
private:
    //pointer pointing to the last
    neuralnetwork* winner_;
    //pool of neural networks that compete against each other
    vector<neuralnetwork> network_pool_;
};

#endif // TRAINER_H
