#include "cell.h"

Cell::Cell(): value_(0)
{
}

Cell* Cell::next(Direction dir) {
    return neighbors_[dir];
}

void Cell::link(Direction dir, Cell& neighbor) {
    neighbors_[dir] = &neighbor;
}

int Cell::get_value() const {
    return value_;
}

void Cell::set_value(int value) {
    value_ = value;
}

float Cell::value()
{
    return value_;
}

void Cell::update()
{

}
