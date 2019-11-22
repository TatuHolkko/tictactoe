#ifndef TRAINER_H
#define TRAINER_H
#include "network/neuralnetwork.h"
#include "game/game.h"

class trainer
{
public:
    //create a trainer for <ancestor> with <pool_size> copies of it fighting in each generation
    trainer(NeuralNetwork& ancestor, int pool_size, Game& game);
    //iterate <n> generations of evolutionary progress
    void iterate(int n);
private:
    //pointer pointing to the last
    NeuralNetwork* winner_;
    //pool of neural networks that compete against each other
    vector<NeuralNetwork> network_pool_;
    //pointer to the game to be used
    Game* game_;
    //play many matches and return winner by comparing scores
    Game::Result play_many_matches(const NeuralNetwork& player1,
                                   const NeuralNetwork& player2,
                                   int n);
    //play a single game
    Game::Result play_one_match(const NeuralNetwork& player1,
                                const NeuralNetwork& player2);
    //return scores from a single game as a reference parameter
    void scores(const Game& game, int& p1_score, int& p2_score);
};

#endif // TRAINER_H
