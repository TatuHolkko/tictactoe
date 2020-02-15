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
        ongoing,
        ended
    };
    //game that has ended will be in one of these states
    enum Result{
        tie,
        player1_win,
        player2_win
    };

    enum Player{
        player1,
        player2
    };

    Game(int size, int win);
    //return game state
    State get_state() const;
    /* return game result. game state must be ended before
     * calling this
     */
    Result get_result() const;
    //return the length of the last game
    int get_length() const;
    //reset game state and clear board
    void reset();

    /* this will interchange ones and twos in the board so that
     * the board looks correct for the next player
     * should be called every time the player changes.
     */
    void turn(Player player);

    //switch the viewing player and update board to show their
    //friendly and opposing units
    void next_turn();

    //return a pointer to cell at (x, y)
    Cell* get_cell(int x, int y);
    /* return grid from perspective of a player
     *
     * <friendly_unit>: the viewing player's unit
     * returns a grid where ones represent friendly units and twos represent
     * opponent's units
     */
    vector<vector<int>> get_board(const int friendly_unit) const;

    //get a const pointer to the cell grid
    const vector<vector<Cell>>* get_board() const;
    //print the board
    void print() const;
    /* place a unit into the board
     * return true if the move was legal and executed
     */
    bool place(int unit, int x, int y);

    /* place a unit into the board at a random position
     * return true if the move was legal and executed
     */
    bool place_random(int unit);

    //return true if board is empty at x, y
    bool can_place(int x, int y) const;

    int get_side_length() const;
private:
    //side length of the game board
    int size_ = 0;
    //amount of units needed to chain in order to win
    int win_ = 0;
    //length of the game in turns
    int length_ = 0;
    //player currently viewing the board
    Player in_turn_ = player1;
    //game state that is updated every time a unit is placed
    State state_ = ongoing;
    /* game result that is updated once the game reaches
     * "ended" -state
     */
    Result result_ = tie;
    //grid where the units are represented as Cell objects
    vector<vector<Cell>> board_;
    //update and return game state based on last move
    State update_state(const int placed_unit, const int x, const int y);




};

#endif // GAME_H
