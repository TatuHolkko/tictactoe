#include "kernelmaster.h"
#include <string>
#include <cmath>

KernelMaster::KernelMaster(int radius):
    radius_(radius)
{
    int side = 2 * radius + 1;
    weights_ = vector<float>(pow(side, 2), 0);
}

void KernelMaster::create_instance(Neuron* neuron, const vector<vector<Cell> > *board, int x, int y) const
{
    int board_side = board->size();
    if (x - radius_ < 0 || x + radius_ >= board_side || y - radius_ < 0 || y + radius_ >= board_side){
        throw "Cannot create kernel instance at " + std::to_string(x) + ", " + std::to_string(y);
    }
    int weight_index = 0;
    for(int dx = -radius_; dx <= radius_; dx++){
        for(int dy = -radius_; dy <= radius_; dy++){
            int cell_y = y + dy;
            int cell_x = x + dx;
            neuron->connect(board->at(cell_y).at(cell_x), weights_.at(weight_index));
            weight_index++;
        }
    }
}
