#include "game/game.h"
#include "filehandler/filehandler.h"
#include "network/neuralnetwork.h"
#include "trainer/trainer.h"
#include <iostream>
#include <vector>


using namespace std;

void place(Game& gm, int x, int y, int unit){
    Cell* c = gm.get_cell(x, y);
    c->set_value(unit);
    gm.place(unit, x, y);
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
    Game gm = Game(4, 3);
    //NeuralNetwork nn(4,1,10,5);
    NeuralNetwork nn;
    fh.load(nn, "../tictactoe/nnfiles/temp.nn");
    Trainer trainer(nn, 30, gm, 0.5, 50, 10, true);
    for (int i = 0; i < 300; i++){
        trainer.iterate(30);
        fh.save(trainer.get_winner(), "../tictactoe/nnfiles/temp" + to_string(i*30) + ".nn");
    }
    trainer.test_winner();
    return 0;
}
