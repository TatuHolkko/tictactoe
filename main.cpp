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
    NeuralNetwork nn(*(gm.get_board()),1,1,18);
    //NeuralNetwork nn;
    //fh.load(nn, "../tictactoe/nnfiles/train-hidden18-mut1-gen840.nn", *(gm.get_board()));
    Trainer trainer(nn, 2, gm, 0.1, 100, 3);
    trainer.set_generation(840);
    for (int i = 0; i < 10000; i++){
        trainer.iterate(1);
        if (i % 30 == 0){
            trainer.showcase_winner();
            fh.save(trainer.get_winner(), "../tictactoe/nnfiles/train-hidden18-mut1-gen" + to_string(i) + ".nn");
        }
    }
    trainer.play_winner();
    return 0;
}
