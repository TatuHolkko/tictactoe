#include "trainer.h"

trainer::trainer(neuralnetwork &ancestor, int pool_size, Game& game):
    winner_(nullptr),
    game_(&game)
{
    network_pool_ = {};
    network_pool_.reserve(pool_size);

    int grid_diameter = ancestor.get_grid_diameter();
    int number_of_kernels = ancestor.get_number_of_kernels();
    int kernel_radius = ancestor.get_kernel_radius();
    int hidden_layer_size = ancestor.get_hidden_layer_size();
    float mutation_rate = ancestor.get_mutation_rate();

    for (int i = 0; i < pool_size; i++){
        neuralnetwork nn(grid_diameter,
                         kernel_radius,
                         hidden_layer_size,
                         mutation_rate,
                         number_of_kernels);
        nn.make_equal_to(ancestor);
        network_pool_.push_back(nn);
    }
}

void trainer::iterate(int n){

}
