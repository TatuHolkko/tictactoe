#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include "network/neuralnetwork.h"
#include "../game/cell.h"
#include <memory>

using namespace std;

class filehandler
{
public:
    filehandler();
    //save a neural network into a file, return true if successful
    bool save(const NeuralNetwork& nn, const string& path);
    // load a neural network from a file, return true if successful
    bool load(NeuralNetwork& nn, const string& path, const vector<vector<Cell>>& game);
private:
    static vector<string> split(const string &s, const char delimiter, bool ignore_empty = false);
};

#endif // FILEHANDLER_H
