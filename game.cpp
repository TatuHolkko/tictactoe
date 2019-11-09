#include "game.h"
#include "cell.h"
#include <vector>
#include <iostream>

using namespace std;

vector<vector<Cell*>> link_grid(int size){
    //initialize grid with no links
    vector<vector<Cell*>> result = {};
    for (int i = 0; i < size; i++){
        vector<Cell*> row = {};
        for (int j = 0; j < size; j++){
            Cell c = Cell();
            row.push_back(&c);
        }
        result.push_back(row);
    }

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
                Cell neighbor = *(result.at(y2).at(x2));
                result.at(y).at(x)->link(static_cast<Cell::Direction>(dir), neighbor);
            }
        }
    }
    return result;
}

Game::Game(int size): size_(size)
{
    board_ = link_grid(size);
}

void Game::print(){
    for (vector<Cell*> row : board_){
        for (Cell* cell : row){
            cout << " " << cell->get_value();
        }
        cout << endl;
    }
}

bool Game::place(int unit, int x, int y){
    if (board_.at(y).at(x)->get_value() != 0){
        return false;
    }
    board_.at(y).at(x)->set_value(unit);
    return true;
}

