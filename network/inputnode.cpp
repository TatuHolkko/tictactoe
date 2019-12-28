#include "inputnode.h"

InputNode::InputNode(int* cell_value_ptr):
    cell_value_ptr_(cell_value_ptr)
{

}

void InputNode::update()
{
    value_ = *cell_value_ptr_;
}

float InputNode::value()
{
    return value_;
}
