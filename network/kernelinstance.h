/* An instance of a kernel. This class represents a single
 * kernel at a single location in the input space. The weights
 * are referenced to the kernel master that created this object.
 */
#ifndef KERNELINSTANCE_H
#define KERNELINSTANCE_H

#include "neuron.h"

class KernelInstance: public Neuron
{
public:
    KernelInstance();
};

#endif // KERNELINSTANCE_H
