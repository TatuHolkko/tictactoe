/* This is a cell object that stores references to all its neighbor cells.
 * The references must be created after initialization by
 * calling the link mehtod on every neighbor. This makes traversing a grid
 * made from these cells much easier to implement.
 */
#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell();
    //array of pointers to the neighboring cells
    Cell* neighbors[8];
    //get a pointer to a cell next to this cell in the given direction
    Cell* next(Direction dir);
    //save a pointer to neighbor in a given direction
    void link(Direction dir, const Cell& neighbor);
    //neighbor directions
    enum Direction{
        up, up_right, right, down_rigth, down, down_left, left, up_left
    }
};

#endif // CELL_H
