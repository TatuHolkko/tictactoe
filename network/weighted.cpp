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

const vector<float>& get_weights() const {
    return weights_;
}

void Weighted::set_equal(const Weighted& target)
{
    vector<float>& target_weights = target.get_weights();
    if (target_weights.size() != weights_.size()){
        throw "Can not copy weights, because target object has different number of weights";
    }
    set_weights(target_weights);
}

void Weighted::get_average(const vector<Weighted>& objects, vector<float>& result)
{
    float sum = 0;
    int number_of_weights = objects.begin().size();
    //for each weight
    for(int weight_index = 0; weight_index < number_of_weights; weight_index++){
        sum = 0;
        //average the same weight from all objects
        for(const Weighted& object : objects){
            sum += object.weight_at(i);
        }
        result.push_back(sum / number_of_objects);
    }
}

const float& Weighted::weight_at(int i)
{
    return weights_.at(i);
}

int Weighted::size()
{
    return weights_.size();
}

float Weighted::random_normal()
{
    return (float)norm_dist_(rand_eng_);
}

float Weighted::random_uniform()
{
    return rand() % 10000 / 5000.0 - 1;
}
