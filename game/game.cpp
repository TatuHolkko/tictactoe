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

Game::State Game::get_state() const{
    return state_;
}

Game::State Game::update_state(const int placed_unit, const int x, const int y){
    Cell* placed_cell = get_cell(x, y);
    //check chain lenghts in all directions
    if (       count_chain(*placed_cell, Cell::right, placed_unit)       >= win_
            || count_chain(*placed_cell, Cell::down_right, placed_unit)  >= win_
            || count_chain(*placed_cell, Cell::down, placed_unit)        >= win_){
        state_ = ended;
        if (placed_unit == 1){
            result_ = player1_win;

        } else {
            result_ = player2_win;
        }
        return ended;
    } else {
        if (length < size_*size_){
            state_ = ongoing;
            return ongoing;
        } else {
            //no free space left
            state_ = ended;
            result_ = tie;
            return ended;
        }
    }
}



Cell* Game::get_cell(int x, int y){
    return &board_.at(y).at(x);
}

vector<vector<int>> Game::get_board() const
{
    vector<vector<int>> result;
    for (int i = 0; i < size_; i++){
        vector<int> row;
        for (int j = 0; j < size_; j++){
            row.push_back(board_.at(j).at(i).get_value());
        }
        result.push_back(row);
    }
    return result;
}

void Game::print() const {
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

