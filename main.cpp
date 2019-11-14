#include <iostream>
#include "game.h"
#include "cell.h"

using namespace std;

void place(Game& gm, int x, int y, int unit){
    Cell* c = gm.get_cell(x, y);
    c->set_value(unit);
    gm.update_state(unit, x, y);
    gm.print();
    cout << "---------" << gm.get_state() << endl;
}

int main()
{
    Game gm = Game(3, 2);
    gm.print();
    cout << "---------" << endl;
    place(gm, 0, 1, 1);
    place(gm, 1, 1, 1);
    place(gm, 2, 1, 1);
    return 0;
}
