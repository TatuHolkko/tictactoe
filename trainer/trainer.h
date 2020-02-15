#ifndef TRAINER_H
#define TRAINER_H
#include "network/neuralnetwork.h"
#include "game/game.h"

#include <utility>

class Trainer
{
public:
    /* create a trainer for neural networks with <pool_size> copies
     * of <ancestor> fighting in each iteration
     *
     * <ancestor>:  if <randomize> is false, all networks are copies of this network
     *              it <randomize> is true, the network architecture is copied from
     *              this network and all weights are randomized
     *
     * <pool_size>: determines how many networks play against each other
     *              in every iteration
     *
     * <game>:      the game engine
     *
     * <mutation_scale>:    all networks are mutated by adding a random number between
     *                      <mutation_scale> and -<mutation_scale> to all weights
     *
     * <matches_per_opponent>:  each network will play this many matches against all
     *                          other networks. they will play as first player
     *                          and as second player so the total matches against a
     *                          single network is twice this amount
     *
     * <winner_pool_size>:      number of top scoring networks to average to create the
     *                          winner of each iteration
     *
     * <randomize>:     if true, all networks will start with random weights instead of
     *                  being copies of <ancestor>
     *
     * <start_random>:  if true, the first move of each game is forced random to increase
     *                  diversity in games
     *
     */
    Trainer(NeuralNetwork& ancestor,
            int pool_size,
            Game& game,
            float mutation_scale,
            int matches_per_opponent,
            int winner_pool_size,
            bool randomize=false,
            bool start_random=true);

   ~Trainer();

    /* iterate <n> generations of evolutionary progress
     *
     * In a single iteration the entire pool of neural networks
     * are made equal to the last iterations winner. All of
     * them (except the winner) are mutated and then they play against
     * each other. The network with the most score is chosen as the new
     * winner for the next iteration.
     */
    void iterate(int n);

    //return the current winner
    const NeuralNetwork& get_winner() const;

    //play against the winner ai through a cli
    void play_winner();

    //show an example game from the winner network
    void showcase_winner();

    //set the generation for information printing
    void set_generation(int generation);

private:
    /* a data type for tracking a network's score during
     * genetic iteration
     */
    struct Competitor
    {
        NeuralNetwork* network;
        int score;
        bool operator <(const Competitor& rhs){
            return this->score < rhs.score;
        }
    };
    //average network of the last iterations top scoring networks
    NeuralNetwork winner_;
    //pool of neural networks that compete against each other
    vector<Competitor> network_pool_;
    //pointer to the game to be used
    Game* game_;
    //maximum mutation of each weight on each iteration
    float mutation_scale_;

    //self descriptive info about last iteration
    int avg_score_ = 0;
    int top_score_ = 0;
    int avg_length_ = 0;
    int iteration_number_ = 0;

    //how many matches per opponent each competitor plays
    int matches_per_opponent_;

    //number of top scoring networks to average after each iteration
    int winner_pool_size_;

    //if true, force a random first unit on board
    bool start_random_;

    //make all competitiors mutated copies of the last winner
    void copy_and_mutate_all();
    //score all competitors against all others
    void score_all();
    //play a single game
    void play_match(NeuralNetwork& player1,
                    NeuralNetwork& player2,
                    bool print = false);
    /* change the scores of the last players according to the
     * state that the game was left after the last game finished
     */
    void score_players(Competitor& player1,
                       Competitor& player2);

    /* return an x, y pair from a neural network output probability
     * distribuiton
     */
    pair<int, int> get_move(const vector<float>& dist) const;

    //set winner_ to point to the competitor with the highest score
    void pick_winner();

    //get an x y pair from command line
    pair<int, int> get_move_cli();

    //print info about the last iteration
    void info();
};

#endif // TRAINER_H
