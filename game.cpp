#include "game.h"
#include "cell.h"
#include <vector>
#include <iostream>

using namespace std;

void link_grid(vector<vector<Cell>>& board, int size){
    //link neigbors one direction at a time
    for (int dir = Cell::up; dir <= Cell::up_left; dir++){
        //loop through all cells
        for (int y = 0; y < size; y++){
            for (int x = 0; x < size; x++){
                //coordinates of the neighbor cell
                int x2 = x;
                int y2 = y;
                switch (dir){
                    case Cell::up:
                        y2 = y - 1;
                        break;
                    case Cell::up_right:
                        y2 = y - 1;
                        x2 = x + 1;
                        break;
                    case Cell::right:
                        x2 = x + 1;
                        break;
                    case Cell::down_right:
                        y2 = y + 1;
                        x2 = x + 1;
                        break;
                    case Cell::down:
                        y2 = y + 1;
                        break;
                    case Cell::down_left:
                        y2 = y + 1;
                        x2 = x - 1;
                        break;
                    case Cell::left:
                        x2 = x - 1;
                        break;
                    case Cell::up_left:
                        y2 = y - 1;
                        x2 = x - 1;
                        break;
                    default:
                        break;
                }
                //ignore coordinates not in the grid
                if (y2 < 0 || y2 >= size || x2 < 0 || x2 >= size){
                    continue;
                }
                board.at(y).at(x).link(static_cast<Cell::Direction>(dir), board.at(y2).at(x2));
            }
        }
    }
}

//return how many units of <value> lie next to each other
//in a straight line parallel to <direction> strarting from <start>
int count_chain(const Cell& start, Cell::Direction direction, int value){
    Cell::Direction opposite = (direction + 4) % 8;
    int chain = 1;
    Cell* current = start.next(direction);

    while(current != nullptr){
        if (current->get_value() == value){
            chain++;
        }
        current = current->next(direction);
    }
    //check in the opposite direction
    current = start.next(opposite);
    while(current != nullptr){
        if (current->get_value() == value){
            chain++;
        }
        current = current->next(opposite);
    }
    return chain;
}

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

void Game::update_state(const int placed_unit, const int x, const int y){
    Cell* placed_cell = get_cell(x, y);
    //check chain lenghts in all directions
    if (       count_chain(placed_cell, Cell::right, placed_unit)       >= win_
            || count_chain(placed_cell, Cell::down_right, placed_unit)  >= win_
            || count_chain(placed_cell, Cell::down, placed_unit)        >= win_){

        if (placed_unit == 1){
            return player1_win;
        } else {
            return player2_win;
        }
    } else {
        if (length < size*size){
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

