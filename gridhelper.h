#ifndef GRIDHELPER_H
#define GRIDHELPER_H
#include "cell.h"
#include <vector>

using namespace std;

//set every cell's neighbors' addresses
void link_grid(vector<vector<Cell>>& board, int size);

//return how many units of <value> lie next to each other
//in a straight line parallel to <direction> starting from <start>
int count_chain(const Cell& start, Cell::Direction direction, int value);

#endif // GRIDHELPER_H
