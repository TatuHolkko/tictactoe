#include "trainer.h"

trainer::trainer(NeuralNetwork &ancestor, int pool_size, Game& game):
    winner_(nullptr),
    game_(&game)
{
    network_pool_ = {};
    network_pool_.reserve(pool_size);

    for (int i = 0; i < pool_size; i++){
        NeuralNetwork nn(ancestor.get_kernel_weights(),
                         ancestor.get_hidden_weights(),
                         ancestor.get_output_weights());
        nn.make_equal_to(ancestor);
        network_pool_.push_back(nn);
    }
}

void trainer::iterate(int n){

}
