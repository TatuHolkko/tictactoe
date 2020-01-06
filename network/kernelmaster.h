/* this is a class for defining a kernel with weights.
 * kernel instances can then be created linking them
 * to the input nodes and their weights to this kernel master.
 * this way the changes in the kernel master's weights will
 * affect all instances.
 */
#ifndef KERNELMASTER_H
#define KERNELMASTER_H

#include "../game/cell.h"
#include "neuron.h"
#include <vector>

using namespace std;

class KernelMaster
{
public:
    KernelMaster(int radius);

    ~KernelMaster();

    //push all kernel instances for this board into <kernels> parameters
    void create_kernels(vector<Neuron*>& kernels, const vector<vector<Cell>>& board);

    //return a kernel instance as a Neuron at <x>, <y> in <board>.
    //this will link all connections in the kernelto the correct board cells
    Neuron& create_kernel(const vector<vector<Cell>>* board, int x, int y) const;

private:

    //how many pixels to each direnction does the kernel cover in addition to
    //the center
    int radius_;

    vector<float> weights_;

    //pointers to all instances of this kernel
    vector<Neuron*> instances_;
};

#endif // KERNELMASTER_H
