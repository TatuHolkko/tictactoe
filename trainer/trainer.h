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
};

#endif // TRAINER_H
