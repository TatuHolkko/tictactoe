#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>
#include <string>

using namespace std;

class NeuralNetwork
{
public:
    NeuralNetwork();

    NeuralNetwork(int grid_diameter,
                  int kernel_radius,
                  int hidden_neurons,
                  int number_of_kernels);

    NeuralNetwork(const vector<vector<float>>& kernels,
                  const vector<vector<float>>& hidden_layer_weights,
                  const vector<vector<float>>& output_weights);
    //initialize weights and attributes from weight vectors
    void initialize_from(const vector<vector<float> >& kernels,
                         const vector<vector<float> >& hidden_layer_weights,
                         const vector<vector<float> >& output_weights);
    //randomize all weights between -1 and 1
    void randomize();
    /* feed game board state to the network and calculate the output
     * probability distribution where this network would place it's
     * next unit
     *
     * returns: a flattened distribution vector. if the board is n x m
     * matrix, the distribution vector will be a vector of length n*m
     */
    vector<float> make_move(const vector<vector<int>>& game_grid) const;
    //nudge all weights randomly
    void mutate(float scale);
    //copy all weights from <other>
    void make_equal_to(const NeuralNetwork& other);

    int get_grid_diameter() const;
    int get_number_of_kernels() const;
    int get_kernel_radius() const;
    int get_kernel_side() const;
    int get_hidden_layer_size() const;
    const vector<vector<float>>& get_kernel_weights() const;
    const vector<vector<float>>& get_hidden_weights() const;
    const vector<vector<float>>& get_output_weights() const;


private:
    //game grid side length
    int grid_diameter_ = 0;
    //number of kernels
    int number_of_kernels_ = 0;
    //radius of the kernel (excluding center)
    int kernel_radius_ = 0;
    //side length of the kernel
    int kernel_side_ = 0;
    //number of neurons in the hidden layer
    int hidden_layer_size_ = 0;
    //kernel weights for convolution
    vector<vector<float>> kernels_ = {};
    //hidden layer weights
    vector<vector<float>> hidden_layer_weights_ = {};
    //output weights
    vector<vector<float>> output_weights_ = {};
    //activation function
    static float activation_function(float x);
    //random weight function
    static float random_number();
    //return the result of a kernel applied to a point
    static float apply_kernel(const vector<vector<int> > &game_grid, const vector<float> kernel, const int kernel_radius, const int x0, const int y0);
};

#endif // NEURALNETWORK_H
