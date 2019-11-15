#include "filehandler.h"
#include <fstream>
#include <iostream>

using namespace std;

filehandler::filehandler()
{

}

bool filehandler::save(neuralnetwork &nn, string path)
{
    cout << "backing up: " << path << endl;
    ofstream output(path);
    output << "grid diameter;" << nn.get_grid_diameter_() << endl;

    output << "number of kernels;" << nn.get_number_of_kernels() << endl;

    output << "kernel radius;" << nn.get_kernel_radius() << endl;

    output << "kernel side;" << nn.get_kernel_side() << endl;

    output << "hidden layer size;" << nn.get_hidden_layer_size() << endl;

    output << "mutation rate;" << nn.get_mutatuon_rate() << endl;

    output << "kernels" << endl;

    vector<vector<float>>* kernels = &nn.get_kernel_weights();

    for (vector<float> kernel : *kernels){
        for (float value : kernel){
            output << value << ";";
        }
        output << endl;
    }

    cout << "backup done" << endl;
    return true;
}
