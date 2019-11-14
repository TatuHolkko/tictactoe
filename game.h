#ifndef GAME_H
#define GAME_H
#include "cell.h"
#include <vector>

using namespace std;

class Game
{
public:
    //the game is always in one of these states
    enum State{
        player1_win,
        player2_win,
        tied,
        ongoing
    };

    Game(int size, int win);
    //return game state as an enumerator of type State
    State get_state();
    //return a pointer to cell at (x, y)
    Cell* get_cell(int x, int y);
    //print the board
    void print();
    //update and return game state based on last move
    State update_state(const int placed_unit, const int x, const int y);
private:
    //side length of the game board
    int size_ = 0;
    //amount of units needed to chain in order to win
    int win_ = 0;
    //length of the game in turns
    int length = 0;
    //game state that is updated every time a unit is placed
    State state_ = ongoing;
    //grid where the units are represented as Cell objects
    vector<vector<Cell>> board_;

    /* place a unit into the board
     * return true if the move was legal and executed
     */
    bool place(int unit, int x, int y);


};

#endif // GAME_H
