#include <fstream>
#include <iostream>
#include <cmath>
#include <memory>

#include "filehandler.h"

using namespace std;

const string LABEL_DIAM = "grid diameter";
const string LABEL_KERN_AMOUNT = "number of kernels";
const string LABEL_KERN_R = "kernel radius";
const string LABEL_HIDD_SIZE = "hidden layer size";
const string LABEL_MUT_RATE = "mutation rate";
const string LABEL_KERNEL = "kernel";
const string LABEL_NEURON = "neuron";
const string LABEL_OUTPUT = "output";

filehandler::filehandler()
{

}

bool filehandler::save(neuralnetwork &nn, const string& path)
{
    cout << "backing up into: " << path << endl;
    ofstream output(path);
    if (!output.is_open()){
        cout << "failed to back up" << endl;
        return false;
    }
    output << LABEL_DIAM << ";" << nn.get_grid_diameter() << endl;
    output << LABEL_KERN_AMOUNT << ";" << nn.get_number_of_kernels() << endl;
    output << LABEL_KERN_R << ";" << nn.get_kernel_radius() << endl;
    output << LABEL_HIDD_SIZE << ";" << nn.get_hidden_layer_size() << endl;
    output << LABEL_MUT_RATE << ";" << nn.get_mutation_rate() << endl;
    const vector<vector<float>>* vect = &nn.get_kernel_weights();

    for (vector<float> kernel : *vect){
        output << LABEL_KERNEL;
        for (float value : kernel){
            output << ";" << value;
        }
        output << endl;
    }
    vect = &nn.get_hidden_weights();
    for (vector<float> hidden_neuron : *vect){
        output << LABEL_NEURON;
        for (float value : hidden_neuron){
            output << ";" << value;
        }
        output << endl;
    }
    vect = &nn.get_output_weights();
    for (vector<float> output_neuron : *vect){
        output << LABEL_OUTPUT;
        for (float value : output_neuron){
            output << ";" << value;
        }
        output << endl;
    }
    output.close();
    cout << "backup done" << endl;
    return true;
}

neuralnetwork filehandler::load(const string& path)
{
    cout << "reading .nn file: " << path << endl;
    ifstream input(path);
    if (!input.is_open()){
        cout << "failed to read .nn file" << endl;
        throw std::invalid_argument("invalid .nn file");
    }
    int diameter;
    int n_of_kernels;
    int kernel_r;
    int hidden_layer_size;
    int mutation_rate;
    vector<vector<float>> kernels;
    vector<vector<float>> neurons;
    vector<vector<float>> outputs;
    string line = "";
    while(getline(input, line)){
        vector<string> line_args = split(line, ';');
        if (line_args.size() == 2){

            if (line_args[0] == LABEL_DIAM){
                diameter = stoi(line_args[1]);

            } else if (line_args[0] == LABEL_KERN_AMOUNT){
                n_of_kernels = stoi(line_args[1]);

            } else if (line_args[0] == LABEL_KERN_R){
                kernel_r = stoi(line_args[1]);

            } else if (line_args[0] == LABEL_HIDD_SIZE){
                hidden_layer_size = stoi(line_args[1]);

            } else if (line_args[0] == LABEL_MUT_RATE){
                mutation_rate = stod(line_args[1]);
            }
        } else {
            if (line_args[0] == LABEL_KERNEL){
                vector<float> kernel = {};
                for (int i = 0; i < pow(kernel_r*2+1, 2) + 1; i++){

                    kernel.push_back(stod(line_args[i + 1]));
                }
                kernels.push_back(kernel);
            } else if (line_args[0] == LABEL_NEURON){
                vector<float> hidden_neuron = {};
                for (int i = 0; i < pow(diameter - 2*kernel_r, 2)*n_of_kernels + 1; i++){
                    hidden_neuron.push_back(stod(line_args[i + 1]));
                }
                neurons.push_back(hidden_neuron);
            } else if (line_args[0] == LABEL_OUTPUT){
                vector<float> output = {};
                for (int i = 0; i < hidden_layer_size + 1; i++){
                    output.push_back(stod(line_args[i + 1]));
                }
                outputs.push_back(output);
            }
        }
    }
    input.close();
    return neuralnetwork(diameter,
                         kernel_r,
                         hidden_layer_size,
                         mutation_rate,
                         n_of_kernels,
                         kernels,
                         neurons,
                         outputs);
}

vector<string> filehandler::split(const string& s,
                                  const char delimiter,
                                  bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

















































