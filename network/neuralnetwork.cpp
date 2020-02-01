#include "neuralnetwork.h"
#include <cmath>
#include <chrono>
#include <random>

NeuralNetwork::NeuralNetwork():
    grid_diameter_(0),
    number_of_kernels_(0),
    kernel_radius_(0),
    kernel_side_(0),
    hidden_layer_size_(0),
    kernels_({}),
    hidden_layer_({}),
    output_layer_({})
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rand_eng_ = default_random_engine(seed);
}

NeuralNetwork::NeuralNetwork(const vector<vector<Cell>>& board,
                             int kernel_radius,
                             int number_of_kernels,
                             int hidden_neurons):
    grid_diameter_(board.size()),
    number_of_kernels_(number_of_kernels),
    kernel_radius_(kernel_radius),
    kernel_side_(2*kernel_radius + 1),
    hidden_layer_size_(hidden_neurons)
{
    for (int i = 0; i < number_of_kernels; i++){
        KernelMaster master = KernelMaster(kernel_radius);
        master.create_kernels(kernel_instances_, board);
        kernels_.push_back(master);
    }

    for (int i = 0; i < hidden_neurons; i++){
        IndependentNeuron neuron = IndependentNeuron();
        for (Neuron* kernel : kernel_instances_){
            neuron.connect(*kernel, 0);
        }
        hidden_layer_.push_back(neuron);
    }

    for (int i = 0; i < pow(grid_diameter_,2); i++){
        IndependentNeuron output = IndependentNeuron();
        for (vector<IndependentNeuron>::iterator hidden_neuron = hidden_layer_.begin();
             hidden_neuron < hidden_layer_.end();
             hidden_neuron++){
            output.connect(*hidden_neuron, 0);
        }
        output_layer_.push_back(output);
    }
}

NeuralNetwork::NeuralNetwork(const vector<vector<Cell>>& board,
                             const vector<vector<float>>& kernels,
                             const vector<vector<float>>& hidden_layer_weights,
                             const vector<vector<float>>& output_weights)
{
    int kernel_radius = floor(sqrt(kernels.at(0).size()) / 2);
    int number_of_kernels = kernels.size();
    int hidden_neurons = hidden_layer_weights.size();

    NeuralNetwork(board, kernel_radius, number_of_kernels, hidden_neurons);

    set_weights(kernels, hidden_layer_weights, output_weights);
}

void NeuralNetwork::set_weights(const vector<vector<float>>& kernels,
                                    const vector<vector<float>>& hidden_layer_weights,
                                    const vector<vector<float>>& output_weights)
{
    for(unsigned int i = 0; i < kernels_.size(); i++){
        KernelMaster& master = kernels_.at(i);
        master.set_weights(kernels.at(i));
    }

    for(unsigned int i = 0; i < hidden_layer_.size(); i++){
        IndependentNeuron& hidden_neuron = hidden_layer_.at(i);
        hidden_neuron.set_weights(hidden_layer_weights.at(i));
    }

    for(unsigned int i = 0; i < output_layer_.size(); i++){
        IndependentNeuron& output_neuron = output_layer_.at(i);
        output_neuron.set_weights(output_weights.at(i));
    }
}

void NeuralNetwork::randomize(){

    for(KernelMaster& kernel : kernels_){
        kernel.randomize(1);
    }
    for(IndependentNeuron& neuron : hidden_layer_){
        neuron.randomize(1);
    }
    for(IndependentNeuron& output : output_layer_){
        output.randomize(1);
    }
}

void NeuralNetwork::make_move(vector<float>& output)
{
    for(Neuron* kernel_instance : kernel_instances_){
        kernel_instance->update();
    }

    for(Neuron& hidden_node : hidden_layer_){
        hidden_node.update();
    }

    for(Neuron& output_node : output_layer_){
        output_node.update();
        output.push_back(output_node.value());
    }
}

void NeuralNetwork::mutate(float scale)
{
    for(KernelMaster& kernel : kernels_){
        kernel.mutate(scale);
    }
    for(IndependentNeuron& neuron : hidden_layer_){
        neuron.mutate(scale);
    }
    for(IndependentNeuron& output : output_layer_){
        output.mutate(scale);
    }
}

void NeuralNetwork::make_equal_to(const NeuralNetwork &other)
{
    vector<KernelMaster>::iterator own_kernel = kernels_.begin();
    vector<KernelMaster>::const_iterator other_kernel = other.get_kernels().begin();
    while(own_kernel != kernels_.end()){
        *own_kernel = *other_kernel;
        own_kernel++;
        other_kernel++;
    }
    vector<IndependentNeuron>::iterator own_neuron = hidden_layer_.begin();
    vector<IndependentNeuron>::const_iterator other_neuron = other.get_hidden_layer().begin();
    while(own_neuron != hidden_layer_.end()){
        *own_neuron = *other_neuron;
        own_neuron++;
        other_neuron++;
    }
    own_neuron = output_layer_.begin();
    other_neuron = other.get_output_layer().begin();
    while(own_neuron != output_layer_.end()){
        *own_neuron = *other_neuron;
        own_neuron++;
        other_neuron++;
    }
}

int NeuralNetwork::get_grid_diameter() const
{
    return grid_diameter_;
}

int NeuralNetwork::get_number_of_kernels() const
{
    return number_of_kernels_;
}

int NeuralNetwork::get_kernel_radius() const
{
    return kernel_radius_;
}

int NeuralNetwork::get_kernel_side() const
{
    return kernel_side_;
}

int NeuralNetwork::get_hidden_layer_size() const
{
    return hidden_layer_size_;
}

const vector<KernelMaster>& NeuralNetwork::get_kernels() const
{
    return kernels_;
}

const vector<IndependentNeuron>& NeuralNetwork::get_hidden_layer() const
{
    return hidden_layer_;
}

const vector<IndependentNeuron>& NeuralNetwork::get_output_layer() const
{
    return output_layer_;
}

float NeuralNetwork::weight_at(int layer, int node, int weight) const
{
    if (layer == 0){
        return kernels_.at(node).at(weight);
    } else if (layer == 1) {
        return hidden_layer_weights_.at(node).at(weight);
    } else {
        return output_weights_.at(node).at(weight);
    }
}

void NeuralNetwork::set_weight_at(int layer, int node, int weight, float value)
{
    if (layer == 0){
        kernels_.at(node).at(weight) = value;
    } else if (layer == 1) {
        hidden_layer_weights_.at(node).at(weight) = value;
    } else {
        output_weights_.at(node).at(weight) = value;
    }
}

float NeuralNetwork::activation_function(float x)
{
    if (x > 0){
        return x;
    }
    return 0;
}

float NeuralNetwork::random_number(){
    return rand() % 10000 / 5000.0 - 1;
}

float NeuralNetwork::random_normal()
{
    return (float)norm_dist_(rand_eng_);
}

float NeuralNetwork::apply_kernel(const vector<vector<int>> &game_grid,
                   const vector<float> kernel,
                   const int kernel_radius,
                   const int x0,
                   const int y0){
    float sum = 0;
    int kernel_side = 2*kernel_radius + 1;
    for (int y = 0; y < kernel_side; y++){
        for (int x = 0; x < kernel_side; x++){
            int xg = x0 - kernel_radius + x;
            int yg = y0 - kernel_radius + y;
            sum += kernel.at(y*kernel_side + x)*game_grid.at(yg).at(xg);
        }
    }
    return sum;
}
