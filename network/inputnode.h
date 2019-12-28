#ifndef INPUTNODE_H
#define INPUTNODE_H

#include "node.h"

class InputNode: public INode
{
public:
    InputNode(int* cell_value_ptr);

    void update();

    float value();

private:

    //the cell of the game board that this input
    //gets ist's value from
    int* cell_value_ptr_;

    //value of this input
    float value_;
};

#endif // INPUTNODE_H
