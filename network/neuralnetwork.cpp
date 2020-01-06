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

NeuralNetwork::NeuralNetwork(int grid_diameter,
                             int kernel_radius,
                             int hidden_neurons,
                             int number_of_kernels):
    grid_diameter_(grid_diameter),
    number_of_kernels_(number_of_kernels),
    kernel_radius_(kernel_radius),
    kernel_side_(2*kernel_radius + 1),
    hidden_layer_size_(hidden_neurons)
{
    for (int i = 0; i < number_of_kernels; i++){
        KernelMaster kernel = KernelMaster(kernel_radius);
        kernels_.push_back(kernel);
    }

    for (int i = 0; i < hidden_neurons; i++){
        IndependentNeuron neuron = IndependentNeuron();
        hidden_layer_.push_back(neuron);
    }

    for (int i = 0; i < pow(grid_diameter,2); i++){
        IndependentNeuron neuron = IndependentNeuron();
        output_layer_.push_back(neuron);
    }
}

NeuralNetwork::NeuralNetwork(const vector<vector<float>>& kernels,
                             const vector<vector<float>>& hidden_layer_weights,
                             const vector<vector<float>>& output):
    NeuralNetwork()
{
    initialize_from(kernels, hidden_layer_weights, output);
}

void NeuralNetwork::initialize_from(const vector<vector<float>>& kernels,
                                    const vector<vector<float>>& hidden_layer_weights,
                                    const vector<vector<float>>& output_weights)
{
    grid_diameter_ = sqrt(output_weights.size());
    number_of_kernels_ = kernels.size();
    kernel_radius_ = floor(sqrt(kernels.at(0).size())/2);
    kernel_side_ = 2*kernel_radius_ + 1;
    hidden_layer_size_ = hidden_layer_weights.size();
    kernels_ = kernels;
    hidden_layer_weights_ = hidden_layer_weights;
    output_weights_ = output_weights;
}

void NeuralNetwork::randomize(){
    vector<vector<float>>::iterator it1;
    vector<float>::iterator it2;
    for (it1 = kernels_.begin(); it1 < kernels_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 = random_number();
        }
    }
    for (it1 = hidden_layer_weights_.begin(); it1 < hidden_layer_weights_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 = random_number();
        }
    }
    for (it1 = output_weights_.begin(); it1 < output_weights_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 = random_number();
        }
    }
}

vector<float> NeuralNetwork::make_move(const vector<vector<int>> &game_grid) const
{
    vector<float> convoluted_inputs;
    convoluted_inputs.reserve(number_of_kernels_ * pow(grid_diameter_ - 2*kernel_radius_, 2));

    for (int kernel_index = 0; kernel_index < number_of_kernels_; kernel_index++){
        for (int x = kernel_radius_; x < grid_diameter_ - kernel_radius_; x++){
            for (int y = kernel_radius_; y < grid_diameter_ - kernel_radius_; y++){
                float kernel_sum = apply_kernel(game_grid,
                                                kernels_.at(kernel_index),
                                                kernel_radius_,
                                                x,
                                                y);
                float bias = kernels_.at(kernel_index).back();
                convoluted_inputs.push_back(activation_function(kernel_sum + bias));
            }
        }
    }

    vector<float> hidden_activations;
    hidden_activations.reserve(hidden_layer_size_);
    for (int neuron = 0; neuron < hidden_layer_size_; neuron++){
        int sum = 0;
        for (vector<float>::size_type input = 0; input < convoluted_inputs.size(); input++){
            sum += convoluted_inputs.at(input) * hidden_layer_weights_.at(neuron).at(input);
        }
        float bias = hidden_layer_weights_.at(neuron).back();
        hidden_activations.push_back(activation_function(sum + bias));
    }

    vector<float> outputs;
    int amount_of_cells = pow(grid_diameter_, 2);
    outputs.reserve(amount_of_cells);
    for (int output = 0; output < amount_of_cells; output++){
        int sum = 0;
        for (int hidd_neur = 0; hidd_neur < hidden_layer_size_; hidd_neur++){
            sum += hidden_activations.at(hidd_neur) * output_weights_.at(output).at(hidd_neur);
        }
        if (REMOVE_OUTPUT_BIAS){
            outputs.push_back(activation_function(sum));
        } else {
            float bias = output_weights_.at(output).back();
            outputs.push_back(activation_function(sum + bias));
        }
    }
    return outputs;
}

void NeuralNetwork::mutate(float scale)
{
    vector<vector<float>>::iterator it1;
    vector<float>::iterator it2;
    for (it1 = kernels_.begin(); it1 < kernels_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 += random_normal() * scale;
        }
    }
    for (it1 = hidden_layer_weights_.begin(); it1 < hidden_layer_weights_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 += random_normal() * scale;
        }
    }
    for (it1 = output_weights_.begin(); it1 < output_weights_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 += random_normal() * scale;
        }
    }
}

void NeuralNetwork::make_equal_to(const NeuralNetwork &other)
{
    vector<vector<float>>::iterator own_weight = kernels_.begin();
    vector<vector<float>>::const_iterator other_weight = other.get_kernel_weights().begin();
    while(own_weight != kernels_.end()){
        *own_weight = *other_weight;
        own_weight++;
        other_weight++;
    }
    own_weight = hidden_layer_weights_.begin();
    other_weight = other.get_hidden_weights().begin();
    while(own_weight != hidden_layer_weights_.end()){
        *own_weight = *other_weight;
        own_weight++;
        other_weight++;
    }
    own_weight = output_weights_.begin();
    other_weight = other.get_output_weights().begin();
    while(own_weight != output_weights_.end()){
        *own_weight = *other_weight;
        own_weight++;
        other_weight++;
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

const vector<vector<float>>& NeuralNetwork::get_kernel_weights() const
{
    return kernels_;
}

const vector<vector<float>>& NeuralNetwork::get_hidden_weights() const
{
    return hidden_layer_weights_;
}

const vector<vector<float>>& NeuralNetwork::get_output_weights() const
{
    return output_weights_;
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
