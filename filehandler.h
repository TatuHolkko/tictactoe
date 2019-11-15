#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "network/neuralnetwork.h"

using namespace std;

class filehandler
{
public:
    filehandler();
    //save a neural network into a file, return true if successful
    bool save(neuralnetwork& nn, string path);
    //load a neural network from a file, return true if successful
    bool load(neuralnetwork& nn, string path);
};

#endif // FILEHANDLER_H
