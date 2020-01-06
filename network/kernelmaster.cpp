#include "kernelmaster.h"
#include <string>
#include <cmath>

KernelMaster::KernelMaster(int radius):
    radius_(radius)
{
    int side = 2 * radius + 1;
    weights_ = vector<float>(pow(side, 2), 0);
}

KernelMaster::~KernelMaster()
{
    for (Neuron* n : instances_){
        delete n;
    }
}

void KernelMaster::create_kernels(vector<Neuron*>& kernels, const vector<vector<Cell>>& board)
{
    int side = board.size();
    for (y = radius_; y < side - radius_; y++){
        for (x = radius_; x < side - radius_; x++){
            kernels.push_back(create_kernel(board, x, y));
        }
    }
}

void KernelMaster::set_weights(const vector<float> &weights)
{
    weights_ = weights;
}

Neuron& KernelMaster::create_kernel(const vector<vector<Cell>>& board, int x, int y) const
{
    int board_side = board.size();
    if (x - radius_ < 0 || x + radius_ >= board_side || y - radius_ < 0 || y + radius_ >= board_side){
        throw "Cannot create kernel instance at " + std::to_string(x) + ", " + std::to_string(y);
    }
    Neuron* neuron = new Neuron();
    int weight_index = 0;
    for(int dy = -radius_; dy <= radius_; dy++){
        for(int dx = -radius_; dx <= radius_; dx++){
            int cell_y = y + dy;
            int cell_x = x + dx;
            neuron->connect(board.at(cell_y).at(cell_x), weights_.at(weight_index));
            weight_index++;
        }
    }
    instances_.push_back(&neuron);
    return *neuron;
}
