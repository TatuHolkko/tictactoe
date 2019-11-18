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
    bool save(neuralnetwork& nn, const string& path);
    //load a neural network from a file, set true to <ok> if successful
    shared_ptr<neuralnetwork> load(const string& path, bool& ok);
private:
    static vector<string> split(const string &s, const char delimiter, bool ignore_empty = false);
};

#endif // FILEHANDLER_H
