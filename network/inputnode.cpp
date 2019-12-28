#include "inputnode.h"

InputNode::InputNode(Cell* cell_ptr):
    cell_ptr_(cell_ptr)
{

}

void InputNode::update()
{
    value_ = cell_ptr_->get_value();
}

float InputNode::value()
{
    return value_;
}
