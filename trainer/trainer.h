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
     * if <randomize> is set, randomize each network after copying
     * and run one iteration to score the randomized networks and
     * set the winner
     */
    Trainer(NeuralNetwork& ancestor,
            int pool_size,
            Game& game,
            float mutation_scale,
            int matches_per_opponent,
            bool randomize=false,
            bool start_random=true);

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
    void test_winner();

private:
    /* a data type for tracking a network's score during
     * genetic iteration
     */
    struct Competitor
    {
        NeuralNetwork network;
        int score;
    };
    //iterator pointing to the last iteration's winner competitor
    vector<Competitor>::iterator winner_;
    //pool of neural networks that compete against each other
    vector<Competitor> network_pool_;
    //pointer to the game to be used
    Game* game_;
    //maximum mutation of each weight on each iteration
    float mutation_scale_;

    //if true, force a random first unit on board
    bool start_random_;

    //self descriptive info about last iteration
    int avg_score_ = 0;
    int top_score_ = 0;
    int avg_length_ = 0;
    int iteration_number_ = 0;

    //how many matches per opponent each competitor plays
    int matches_per_opponent_;
    //make all competitiors mutated copies of the last winner
    void copy_and_mutate_all();
    //score all competitors against all others
    void score_all();
    //play a single game
    void play_match(const NeuralNetwork& player1,
                    const NeuralNetwork& player2);
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
