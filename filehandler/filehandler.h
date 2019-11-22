#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "network/neuralnetwork.h"
#include <memory>

using namespace std;

class filehandler
{
public:
    filehandler();
    //save a neural network into a file, return true if successful
    bool save(NeuralNetwork& nn, const string& path);
    // load and return a neural network from a file
    NeuralNetwork load(const string& path);
private:
    static vector<string> split(const string &s, const char delimiter, bool ignore_empty = false);
};

#endif // FILEHANDLER_H
