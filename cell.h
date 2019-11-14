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
    //neighbor directions
    enum Direction{
        up, up_right, right, down_right, down, down_left, left, up_left
    };
    //get a pointer to a cell next to this cell in the given direction
    Cell* next(Direction dir);
    //save a pointer to neighbor in a given direction
    void link(Direction dir, Cell& neighbor);
    //return value
    int get_value() const;
    //set value
    void set_value(int value);

private:
    //value representing an empty space with zero and a unit with any other value
    int value_;
    //array of pointers to the neighboring cells
    Cell* neighbors_[8] = {nullptr};
};

#endif // CELL_H
