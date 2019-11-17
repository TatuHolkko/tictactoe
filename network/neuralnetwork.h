#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>
#include <string>

using namespace std;

class neuralnetwork
{
public:
    neuralnetwork(int grid_diameter,
                  int kernel_radius,
                  int hidden_neurons,
                  int mutation_rate,
                  int number_of_kernels);
    //randomize all weights between -1 and 1
    void randomize();
    /* feed game board state to the network and calculate the output
     * probability distribution where this network would place it's
     * next unit
     */
    vector<float> make_move(const vector<vector<int>>& game_grid);
    //nudge all weights randomly
    void mutate();
    //copy all weights from <other>
    void make_equal_to(const neuralnetwork& other);

    int get_grid_diameter_();
    int get_number_of_kernels();
    int get_kernel_radius();
    int get_kernel_side();
    int get_hidden_layer_size();
    int get_mutatuon_rate();
    vector<vector<float>>& get_kernel_weights();
    vector<vector<float>>& get_hidden_weights();
    vector<vector<float>>& get_output_weights();
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
    //this scales the random nudges in weights
    float mutation_rate_ = 0;
    //kernel weights for convolution
    vector<vector<float>> kernels_ = {};
    //hidden layer weights
    vector<vector<float>> hidden_layer_ = {};
    //output weights
    vector<vector<float>> output_ = {};
    //activation function
    static float sigmoid(float x);
    //random weight function
    static float random_weight();
    //return the result of a kernel applied to a point
    static float apply_kernel(const vector<vector<int> > &game_grid, const vector<float> kernel, const int kernel_radius, const int x0, const int y0);
};

#endif // NEURALNETWORK_H
