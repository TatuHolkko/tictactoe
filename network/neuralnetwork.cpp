#include "neuralnetwork.h"
#include <cmath>
#include <random>

neuralnetwork::neuralnetwork(int grid_diameter,
                             int kernel_radius,
                             int hidden_neurons,
                             int mutation_rate,
                             int number_of_kernels):
    grid_diameter_(grid_diameter),
    number_of_kernels_(number_of_kernels),
    kernel_radius_(kernel_radius),
    kernel_side_(2*kernel_radius + 1),
    hidden_layer_size_(hidden_neurons),
    mutation_rate_(mutation_rate)

{
    //initialize weights to zero
    for (int i = 0; i < number_of_kernels; i++){
        vector<float> kernel(pow(kernel_side_, 2) + 1, 0);
        kernels_.push_back(kernel);
    }
    for (int neuron = 0; neuron < hidden_neurons; neuron++){
        vector<float> convoluted_inputs(pow(grid_diameter - 2*kernel_radius, 2)*number_of_kernels + 1, 0);
        hidden_layer_.push_back(convoluted_inputs);
    }
    for (int output = 0; output < pow(grid_diameter,2); output++){
        vector<float> hidden_layer_output(hidden_neurons + 1, 0);
        output_.push_back(hidden_layer_output);
    }
}

void neuralnetwork::randomize(){
    vector<vector<float>>::iterator it1;
    vector<float>::iterator it2;
    for (it1 = kernels_.begin(); it1 < kernels_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 = random_weight();
        }
    }
    for (it1 = hidden_layer_.begin(); it1 < hidden_layer_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 = random_weight();
        }
    }
    for (it1 = output_.begin(); it1 < output_.end(); it1++){
        for (it2 = it1->begin(); it2 < it1->end(); it2++){
            *it2 = random_weight();
        }
    }
}

vector<float> neuralnetwork::make_move(const vector<vector<int>> &game_grid)
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
                convoluted_inputs.push_back(sigmoid(kernel_sum + bias));
            }
        }
    }

    vector<float> hidden_activations;
    hidden_activations.reserve(hidden_layer_size_);
    for (int neuron = 0; neuron < hidden_layer_size_; neuron++){
        int sum = 0;
        for (vector<float>::size_type input = 0; input < convoluted_inputs.size(); input++){
            sum += convoluted_inputs.at(input) * hidden_layer_.at(neuron).at(input);
        }
        float bias = hidden_layer_.at(neuron).back();
        hidden_activations.push_back(sigmoid(sum + bias));
    }

    vector<float> outputs;
    int amount_of_cells = pow(grid_diameter_, 2);
    outputs.reserve(amount_of_cells);
    for (int output = 0; output < amount_of_cells; output++){
        int sum = 0;
        for (int hidd_neur = 0; hidd_neur < hidden_layer_size_; hidd_neur++){
            sum += hidden_activations.at(hidd_neur) * output_.at(output).at(hidd_neur);
        }
        float bias = output_.at(output).back();
        outputs.push_back(sigmoid(sum + bias));
    }
    return outputs;
}

void neuralnetwork::make_equal_to(neuralnetwork &other)
{
    vector<vector<float>>::iterator own_weight = kernels_.begin();
    vector<vector<float>>::iterator other_weight = other.get_kernel_weights().begin();
    while(own_weight != kernels_.end()){
        *own_weight = *other_weight;
        own_weight++;
        other_weight++;
    }
    own_weight = hidden_layer_.begin();
    other_weight = other.get_hidden_weights().begin();
    while(own_weight != hidden_layer_.end()){
        *own_weight = *other_weight;
        own_weight++;
        other_weight++;
    }
    own_weight = output_.begin();
    other_weight = other.get_output_weights().begin();
    while(own_weight != output_.end()){
        *own_weight = *other_weight;
        own_weight++;
        other_weight++;
    }
}

int neuralnetwork::get_grid_diameter() const
{
    return grid_diameter_;
}

int neuralnetwork::get_number_of_kernels() const
{
    return number_of_kernels_;
}

int neuralnetwork::get_kernel_radius() const
{
    return kernel_radius_;
}

int neuralnetwork::get_kernel_side() const
{
    return kernel_side_;
}

int neuralnetwork::get_hidden_layer_size() const
{
    return hidden_layer_size_;
}

int neuralnetwork::get_mutation_rate() const
{
    return mutation_rate_;
}

vector<vector<float>>& neuralnetwork::get_kernel_weights()
{
    return kernels_;
}

vector<vector<float>>& neuralnetwork::get_hidden_weights()
{
    return hidden_layer_;
}

vector<vector<float>>& neuralnetwork::get_output_weights()
{
    return output_;
}

float neuralnetwork::sigmoid(float x)
{
    return x;
}

float neuralnetwork::random_weight(){
    return rand() % 10000 / 5000.0 - 1;
}

float neuralnetwork::apply_kernel(const vector<vector<int>> &game_grid,
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
