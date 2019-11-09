#include "cell.h"

Cell::Cell()
{
}

Cell* Cell::next(Direction dir){
    return neighbors_[dir];
}

void Cell::link(Direction dir, Cell &neighbor){
    neighbors_[dir] = &neighbor;
}

int Cell::get_value(){
    return value_;
}

void Cell::set_value(int value){
    value_ = value;
}
