#include "weighted.h"

Weighted::Weighted(int n)
{
    weights_ = vector<float>(n, 0);
}

void Weighted::randomize(const float &scale)
{
    for (float& weight : weights_){
        weight = random_uniform() * scale;
    }
}

void Weighted::mutate(const float &scale)
{
    for (float& weight : weights_){
        weight += random_normal() * scale;
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
