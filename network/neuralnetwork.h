#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "kernelmaster.h"
#include "neuron.h"
#include "independentneuron.h"

#include <vector>
#include <string>
#include <random>

using namespace std;

class NeuralNetwork
{
public:
    NeuralNetwork();

    NeuralNetwork(const vector<vector<Cell>>& board,
                  int kernel_radius,
                  int number_of_kernels,
                  int hidden_neurons);

    NeuralNetwork(const vector<vector<Cell>>& board,
                  const vector<vector<float>>& kernels,
                  const vector<vector<float>>& hidden_layer_weights,
                  const vector<vector<float>>& output_weights);
    //initialize weights from weight vectors
    void set_weights(const vector<vector<float> >& kernels,
                     const vector<vector<float> >& hidden_layer_weights,
                     const vector<vector<float> >& output_weights);
    //randomize all weights between -1 and 1
    void randomize();
    /* calculate the output probability distribution where this network would place it's
     * next unit according to the current board state. the board needs to be from this
     * networks point of view (meaning that this network's units must be represented with
     * ones).
     *
     * <output> an empty vector of floats where the result distribution will be stored
     *
     * returns: a flattened distribution vector as a reference parameter. if the board is n x m
     * matrix, the distribution vector will be a vector of length n*m
     */
    void make_move(vector<float>& output);
    //nudge all weights randomly
    void mutate(float scale);
    //copy all weights from <other>
    void make_equal_to(const NeuralNetwork& other);

    int get_grid_diameter() const;
    int get_number_of_kernels() const;
    int get_kernel_radius() const;
    int get_kernel_side() const;
    int get_hidden_layer_size() const;
    const vector<KernelMaster>& get_kernels() const;
    const vector<IndependentNeuron>& get_hidden_layer() const;
    const vector<IndependentNeuron>& get_output_layer() const;

    bool REMOVE_OUTPUT_BIAS = true;

    /* get a weight with indexes
     *
     * <layer> 0: kernels, 1: hidden layer, 2: output layer
     * <node> index of the node or kernel
     * <weight> index of the weight
     */
    float weight_at(int layer, int node, int weight) const;
    /* set a weight with indexes
     *
     * <layer> 0: kernels, 1: hidden layer, 2: output layer
     * <node> index of the node or kernel
     * <weight> index of the weight
     */
    void set_weight_at(int layer, int node, int weight, float value);

    /* Set this network's weights to equal the averages of the weights in <pool>
     *
     * <pool> list of NeuralNetworks that are averaged
     */
    void make_average_from(const vector<NeuralNetwork*>& pool);

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
    //kernelmaster for each unique kernel
    vector<KernelMaster> kernels_ = {};

    //vector of all kernel instances for each postion and orientation
    //of a kernel master
    vector<Neuron*> kernel_instances_ = {};

    //hidden layer
    vector<IndependentNeuron> hidden_layer_ = {};
    //output layer
    vector<IndependentNeuron> output_layer_ = {};
    //normal distribution used by the random_normal function
    normal_distribution<double> norm_dist_ = normal_distribution<double>(0.0,1.0);
    default_random_engine rand_eng_;
    //activation function
    static float activation_function(float x);
    //random number between -1 and 1
    static float random_number();
    //random number with normal distribution around zero with stddev 1
    float random_normal();
    //return the result of a kernel applied to a point
    static float apply_kernel(const vector<vector<int> > &game_grid, const vector<float> kernel, const int kernel_radius, const int x0, const int y0);
};

#endif // NEURALNETWORK_H
