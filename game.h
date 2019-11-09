#ifndef GAME_H
#define GAME_H
#include "cell.h"
#include <vector>

using namespace std;

class Game
{
public:
    Game(int size);
    //side length of the game board
    int size_ = 0;
    //return game state as an enumerator of type State
    void get_state();
    //return a pointer to cell at (x, y)
    Cell* get_cell(int x, int y);
    //print the board
    void print();

private:

    //grid where the units are represented as Cell objects
    vector<vector<Cell>> board_;

    /* place a unit into the board
     * return true if the move was legal and executed
     */
    bool place(int unit, int x, int y);

    //the game is always in one of these states
    enum State{
        player1_win,
        player2_win,
        tied,
        ongoing
    };
};

#endif // GAME_H
