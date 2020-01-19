#include "weighted.h"

Weighted::Weighted(int n)
{
    weights_ = vector<float>(n, 0);
}

void Weighted::randomize(const float& scale)
{
    for (float& weight : weights_){
        weight = random_uniform() * scale;
    }
}

void Weighted::mutate(const float& scale)
{
    for (float& weight : weights_){
        weight += random_normal() * scale;
    }
}

const float& Weighted::add_weight(const float& value)
{
    weights_.push_back(value);
    return &(weights_.end());
}

void Weighted::set_weights(const vector<float>& weights)
{
    if (weights.size() < weights_.size()){
        throw "Can not set weights, because argument vector is too small.";
    }
    vector<float>::iterator self_iterator = weights_.begin();
    vector<float>::iterator other_iterator = weights.begin();

    while(self_iterator != weights_.end()){
        *self_iterator = *other_iterator;
        self_iterator++;
        other_iterator++;
    }
}

float Weighted::random_normal()
{
    return (float)norm_dist_(rand_eng_);
}

float Weighted::random_uniform()
{
    return rand() % 10000 / 5000.0 - 1;
}
