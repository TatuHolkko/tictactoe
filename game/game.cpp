#include "game.h"
#include "cell.h"
#include "gridhelper.cpp"
#include <vector>
#include <iostream>
#include <random>

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

Game::Result Game::get_result() const
{
    return result_;
}

int Game::get_length() const
{
    return length_;
}

void Game::reset()
{
    for (vector<vector<Cell>>::iterator row = board_.begin(); row < board_.end(); row++){
        for (vector<Cell>::iterator cell_it =  row->begin(); cell_it < row->end(); cell_it++){
            cell_it->set_value(0);
        }
    }
    state_ = ongoing;
    result_ = tie;
    length_ = 0;
}

void Game::turn(Game::Player player)
{
    if (player == in_turn_){
        //the board is from the right player's perspective
        return;
    }
    in_turn_ = player;

    int friendly_unit = player + 1;

    for (vector<vector<Cell>>::iterator row = board_.begin(); row < board_.end(); row++){
        for (vector<Cell>::iterator cell_it =  row->begin(); cell_it < row->end(); cell_it++){
            int value = cell_it->get_value();
            if (value != 0){
                if (value == friendly_unit){
                    cell_it->set_value(1);
                } else {
                    cell_it->set_value(2);
                }
            }
        }
    }
}

void Game::next_turn()
{
    if (in_turn_ == player1){
        turn(player2);
    } else {
        turn(player1);
    }
}

Game::State Game::update_state(const int placed_unit, const int x, const int y){
    Cell* placed_cell = get_cell(x, y);
    //check chain lenghts in all directions
    if (       count_chain(*placed_cell, Cell::right, placed_unit)       >= win_
            || count_chain(*placed_cell, Cell::down_right, placed_unit)  >= win_
            || count_chain(*placed_cell, Cell::down_left, placed_unit)   >= win_
            || count_chain(*placed_cell, Cell::down, placed_unit)        >= win_){
        if (placed_unit == 1){
            result_ = player1_win;

        } else {
            result_ = player2_win;
        }
        state_ = ended;
        return ended;
    } else {
        if (length_ < size_*size_){
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

vector<vector<int>> Game::get_board(const int friendly_unit) const
{
    vector<vector<int>> result;
    for (int y = 0; y < size_; y++){
        vector<int> row;
        for (int x = 0; x< size_; x++){
            int value = board_.at(y).at(x).get_value();
            if (value == 0){
                row.push_back(0);
            } else if (value == friendly_unit){
                //own unit
                row.push_back(1);
            } else {
                //opponent's unit
                row.push_back(2);
            }
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
    length_++;
    update_state(unit, x, y);
    return true;
}

bool Game::place_random(int unit)
{
    int x = rand() % size_;
    int y = rand() % size_;
    return place(unit, x, y);
}

bool Game::can_place(int x, int y) const
{
    return board_.at(y).at(x).get_value() == 0;
}

int Game::get_side_length() const
{
    return size_;
}

