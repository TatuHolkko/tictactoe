/* this is a class for defining a kernel with weights.
 * kernel instances can then be created linking them
 * to the input nodes and their weights to this kernel master.
 * this way the changes in the kernel master's weights will
 * affect all instances.
 */
#ifndef KERNELMASTER_H
#define KERNELMASTER_H

#include "kernelinstance.h"
#include <vector>

using namespace std;

class KernelMaster
{
public:
    KernelMaster(int radius);

    KernelInstance create_instance();

private:
    int radius_;

    vector<float> weights_;
};

#endif // KERNELMASTER_H
