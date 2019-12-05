#include <fstream>
#include <iostream>
#include <cmath>
#include <memory>

#include "filehandler.h"

using namespace std;

const string LABEL_KERNEL = "kernel";
const string LABEL_NEURON = "neuron";
const string LABEL_OUTPUT = "output";

filehandler::filehandler()
{

}

bool filehandler::save(const NeuralNetwork &nn, const string& path)
{
    cout << "backing up into: " << path << endl;
    ofstream output(path);
    if (!output.is_open()){
        cout << "failed to back up" << endl;
        return false;
    }
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

bool filehandler::load(NeuralNetwork& nn, const string& path)
{
    cout << "reading .nn file: " << path << endl;
    ifstream input(path);
    if (!input.is_open()){
        cout << "failed to read .nn file" << endl;
        return false;
    }
    vector<vector<float>> kernels;
    vector<vector<float>> hidden_layer_weights;
    vector<vector<float>> output_weights;
    string line = "";
    while(getline(input, line)){
        vector<string> line_args = split(line, ';');
        if (line_args[0] == LABEL_KERNEL){

            vector<float> kernel = {};
            for (vector<string>::size_type i = 1; i < line_args.size(); i++){

                kernel.push_back(stod(line_args[i]));
            }
            kernels.push_back(kernel);

        } else if (line_args[0] == LABEL_NEURON){

            vector<float> hidden_neuron = {};
            for (vector<string>::size_type i = 1; i < line_args.size(); i++){
                hidden_neuron.push_back(stod(line_args[i]));
            }
            hidden_layer_weights.push_back(hidden_neuron);

        } else if (line_args[0] == LABEL_OUTPUT){

            vector<float> output = {};
            for (vector<string>::size_type i = 1; i < line_args.size(); i++){
                output.push_back(stod(line_args[i]));
            }
            output_weights.push_back(output);
        }
    }
    input.close();
    nn.initialize_from(kernels, hidden_layer_weights, output_weights);
    cout << "file reading done" << endl;
    return true;
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

















































