#include "trainer.h"
#include <random>
#include <cmath>
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

Trainer::Trainer(NeuralNetwork &ancestor,
                 int pool_size,
                 Game& game,
                 float mutation_scale,
                 int matches_per_opponent,
                 int winner_pool_size,
                 bool randomize,
                 bool start_random):
    game_(&game),
    mutation_scale_(mutation_scale),
    matches_per_opponent_(matches_per_opponent),
    winner_pool_size_(winner_pool_size),
    start_random_(start_random)
{
    network_pool_ = {};
    network_pool_.reserve(pool_size);

    for (int i = 0; i < pool_size; i++){
        Competitor comp = {new NeuralNetwork(ancestor, *(game.get_board())), 0};
        if (randomize){
            comp.network->randomize();
        }
        network_pool_.push_back(comp);
    }
    winner_ = NeuralNetwork(ancestor, *(game.get_board()));

    if (randomize){
        score_all();
        pick_winner();
    }
}

Trainer::~Trainer()
{
    for(Competitor comp : network_pool_){
        delete comp.network;
    }
}

void Trainer::iterate(int n)
{
    for (int iteration = 0; iteration < n; iteration++){
        iteration_number_++;
        copy_and_mutate_all();
        score_all();
        pick_winner();
        info();

    }
}

const NeuralNetwork& Trainer::get_winner() const
{
    return winner_;
}

void Trainer::play_winner()
{
    game_->reset();
    cout << "--------" << endl;
    game_->print();
    int player = 1;
    while(game_->get_state() == Game::ongoing){
        pair<int, int> move;
        if (player == 1){
            move = get_move_cli();
        } else {
            vector<float> output = {};
            winner_.make_move(output);
            move = get_move(output);
        }

        game_->place(player, move.first, move.second);
        game_->next_turn();
        cout << "--------" << endl;
        game_->print();

        if (player == 1){
            player = 2;
        } else {
            player = 1;
        }
    }
    cout << "--------" << endl;
    cout << game_->get_result();
    cout << "--------" << endl;

}

void Trainer::showcase_winner()
{
    play_match(winner_, winner_, true);
}

void Trainer::set_generation(int generation)
{
    iteration_number_ = generation;
}

void Trainer::copy_and_mutate_all()
{
    for(vector<Competitor>::iterator comp = network_pool_.begin();
        comp < network_pool_.end();
        comp++){

        comp->score = 0;
        comp->network->make_equal_to(winner_);
        //leave first network unaltered so that there is at least one copy
        //of the winner in the pool
        if (comp != network_pool_.begin()){
            comp->network->mutate(mutation_scale_);
        }
    }
}

void Trainer::score_all()
{
    int total_matches = 0;
    int length_sum = 0;
    int score_sum = 0;
    for(vector<Competitor>::iterator player = network_pool_.begin();
        player < network_pool_.end();
        player++){
        for(vector<Competitor>::iterator opponent = network_pool_.begin();
            opponent < network_pool_.end();
            opponent++){
            //dont play against self
            if (opponent != player){
                for (int match = 0; match < matches_per_opponent_; match++){

                    play_match(*(player->network), *(opponent->network));
                    score_players(*player, *opponent);

                    total_matches++;
                    length_sum += game_->get_length();
                }
            }
        }
        score_sum += player->score;
    }
    avg_length_ = (float)length_sum/total_matches;
    avg_score_ = score_sum/total_matches;
}

void Trainer::play_match(NeuralNetwork& player1, NeuralNetwork& player2, bool print)
{
    game_->reset();
    NeuralNetwork* current_player = &player1;
    int unit = 1;
    if(start_random_){
        game_->place_random(1);
        game_->next_turn();
        unit  = 2;
        current_player = &player2;
    }
    while(game_->get_state() == Game::ongoing){
        vector<float> output = {};
        current_player->make_move(output);
        pair<int, int> unit_location = get_move(output);
        game_->place(unit, unit_location.first, unit_location.second);
        game_->next_turn();
        if (unit == 1){
            unit  = 2;
            current_player = &player2;
        } else {
            unit = 1;
            current_player = &player1;
        }
        if (print) {
            cout << "--------" << endl;
            game_->print();
        }
    }
    if (print){
        cout << "--------" << endl;
    }
}

void Trainer::score_players(Trainer::Competitor& player1, Trainer::Competitor& player2)
{
    Game::Result result = game_->get_result();
    int max_game_length = pow(game_->get_side_length(), 2);
    int length = game_->get_length();
    int winner_score = 100 - 75*((float)length/max_game_length);
    int loser_score = -100 + 50*((float)length/max_game_length);

    if (result == Game::player1_win){
        player1.score += winner_score;
        player2.score += loser_score;
    } else if (result == Game::player2_win){
        player2.score += winner_score;
        player1.score += loser_score;
    }
}

pair<int, int> Trainer::get_move(const vector<float>& dist) const
{
    /* copy the original distribution so we can remove coordinates
     * that are blocked from the distribution
     */
    vector<float> not_checked = vector<float>(dist.size(), 1);
    vector<float> masked_dist = dist;
    default_random_engine generator;
    discrete_distribution<int> distribution(masked_dist.begin(), masked_dist.end());

    int placed_on = distribution(generator);
    int x = placed_on % game_->get_side_length();
    int y = placed_on / game_->get_side_length();
    while(!game_->can_place(x, y)){
        //if x, y is blocked, remove it from the distribution
        //so it doesnt get picked again
        masked_dist.at(placed_on) = 0;
        //keep track of all tiles that are checked to not be empty
        not_checked.at(placed_on) = 0;

        if (std::accumulate(masked_dist.begin(), masked_dist.end(), 0) == 0){
            //the prob dist given only contains non-zero elements in blocked cells,
            //set the dist to be equally likely on all tiles that have not yet
            //been checked
            masked_dist = not_checked;
        }

        //redefine the distribution
        distribution = discrete_distribution<int>(masked_dist.begin(), masked_dist.end());
        //repick a coordinate
        placed_on = distribution(generator);
        x = placed_on % game_->get_side_length();
        y = placed_on / game_->get_side_length();
    }
    return make_pair(x, y);
}

void Trainer::pick_winner()
{
    std::sort(network_pool_.begin(), network_pool_.end());
    std::reverse(network_pool_.begin(), network_pool_.end());

    top_score_ = network_pool_.begin()->score;

    vector<Competitor>::iterator winners_begin = network_pool_.begin();
    vector<Competitor>::iterator winners_end = winners_begin + winner_pool_size_;

    vector<NeuralNetwork*> winners= {};
    for (vector<Competitor>::iterator competitor_iterator = winners_begin;
             competitor_iterator < winners_end;
             competitor_iterator++){
            winners.push_back(competitor_iterator->network);
    }

    winner_.make_average_from(winners);
}

pair<int, int> Trainer::get_move_cli()
{
    cout << "x y=";
    int x;
    int y;
    cin >> x;
    getchar();
    cin >> y;
    return make_pair(x, y);
}

void Trainer::info()
{
    int matches_per_player = 2 * (network_pool_.size() - 1) * matches_per_opponent_;
    cout << "generation " << iteration_number_ << ":"
         << " top: " << top_score_/matches_per_player
         << " avg: " << avg_score_
         << " len: " << avg_length_
         << endl;
}

