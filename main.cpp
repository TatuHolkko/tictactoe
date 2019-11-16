#include <iostream>
#include "game/game.h"
#include "filehandler.h"
#include "network/neuralnetwork.h"

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
    filehandler fh;
    bool ok = false;
    shared_ptr<neuralnetwork> nn = fh.load("../tictactoe/bu.nn", ok);
    fh.save(*nn, "../tictactoe/bu2.nn");
    return 0;
}
