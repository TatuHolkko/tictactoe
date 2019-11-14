#include "game.h"
#include "cell.h"
#include "gridhelper.cpp"
#include <vector>
#include <iostream>

using namespace std;


Game::Game(int size, int win): size_(size), win_(win)
{
    board_ = {};
    //initialize grid with no links
    for (int i = 0; i < size; i++){
        vector<Cell> row = {};
        for (int j = 0; j < size; j++){
            Cell c = Cell();
            row.push_back(c);
        }
        board_.push_back(row);
    }
    link_grid(board_, size);
}

Game::State Game::get_state(){
    return state_;
}

Game::State Game::update_state(const int placed_unit, const int x, const int y){
    Cell* placed_cell = get_cell(x, y);
    //check chain lenghts in all directions
    if (       count_chain(*placed_cell, Cell::right, placed_unit)       >= win_
            || count_chain(*placed_cell, Cell::down_right, placed_unit)  >= win_
            || count_chain(*placed_cell, Cell::down, placed_unit)        >= win_){

        if (placed_unit == 1){
            return player1_win;
        } else {
            return player2_win;
        }
    } else {
        if (length < size_*size_){
            return ongoing;
        } else {
            //no free space left
            return tied;
        }
    }
}



Cell* Game::get_cell(int x, int y){
    return &board_.at(y).at(x);
}

void Game::print(){
    for (vector<Cell> row : board_){
        for (Cell cell : row){
            cout << " " << cell.get_value();
        }
        cout << endl;
    }
}

bool Game::place(int unit, int x, int y){
    if (board_.at(y).at(x).get_value() != 0){
        return false;
    }
    board_.at(y).at(x).set_value(unit);
    return true;
}

