/* this is a class for defining a kernel with weights.
 * kernel instances can then be created linking them
 * to the input nodes and their weights to this kernel master.
 * this way the changes in the kernel master's weights will
 * affect all instances.
 */
#ifndef KERNELMASTER_H
#define KERNELMASTER_H

#include "kernelinstance.h"
#include "../game/cell.h"
#include <vector>

using namespace std;

class KernelMaster
{
public:
    KernelMaster(int radius);

    //return a kernel instance as a Neuron at <x>, <y> in <board> as a
    //reference parameter. this will link all connections in the kernel
    //to the correct board cells
    void connect_kernel(Neuron* neuron, const vector<vector<Cell>>* board, int x, int y) const;

private:

    int radius_;

    vector<float> weights_;
};

#endif // KERNELMASTER_H
