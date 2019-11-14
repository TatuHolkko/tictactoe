#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>

using namespace std;

class neuralnetwork
{
public:
    neuralnetwork();
    /* feed game board state to the network and calculate the output
     * probability distribution where this network would place it's
     * next unit
     */
    vector<float> make_move(const vector<int>& game_grid);
    //nudge all weights randomly
    void mutate();
    //copy all weights from <other>
    void make_equal_to(const neuralnetwork& other);
private:
    //game grid side length
    int grid_size_ = 0;
    //radius of the kernel
    int kernel_radius_ = 0;
    //side length of the kernel
    int kernel_side_ = 0;
    //number of neurons in the hidden layer
    int hidden_layer_size_ = 0;
    //this scales the random nudges in weights
    float mutation_rate = 0;
    //kernel weights for convolution
    vector<vector<float>> kernels_;
    //hidden layer weights
    vector<float> hidden_layer;
    //output weights
    vector<float> output;
    //activation function
    float sigmoid(float x);
};

#endif // NEURALNETWORK_H
