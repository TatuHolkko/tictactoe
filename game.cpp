#include "game.h"

Game::Game(int size)
{
    for (int i = 0; i < size; i++){
        board_.push_back(vector<int>(size));
    }
}

bool Game::place(int unit, int x, int y){
    if (board_.at(y).at(x) != 0){
        return false;
    }
    board_.at(y).at(x) = unit;
    return true;
}

