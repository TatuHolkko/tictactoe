#include "game/game.h"
#include "filehandler.h"
#include "network/neuralnetwork.h"
#include <iostream>
#include <vector>


using namespace std;

void place(Game& gm, int x, int y, int unit){
    Cell* c = gm.get_cell(x, y);
    c->set_value(unit);
    gm.update_state(unit, x, y);
    gm.print();
    cout << "---------" << gm.get_state() << endl;
}

void print_output(const vector<float>& output){
    cout << "---------" << endl;
    for (int i = 0; i < 4; i++){
        cout << output.at(i*4 + 0) << " ";
        cout << output.at(i*4 + 1) << " ";
        cout << output.at(i*4 + 2) << " ";
        cout << output.at(i*4 + 3) << endl;;
    }
}

int main()
{

    filehandler fh;
    Game gm = Game(4, 2);
    bool ok = false;
    shared_ptr<neuralnetwork> nn = fh.load("../ticatactoe/test.nn", ok);
    vector<float> output = nn->make_move(gm.get_board());
    print_output(output);
    return 0;
}
