#include <iostream>
#include "game.h"
#include "cell.h"

using namespace std;

int main()
{
    Game gm = Game(2);
    gm.print();
    Cell* c = gm.get_cell(0,0);
    Cell* c2 = c->next(Cell::down);
    c2->set_value(1);
    gm.print();
    return 0;
}
