#include "weighted.h"



Weighted::Weighted():
    weights_({}),
    bias_(0)
{

}

Weighted::Weighted(int n):
    weights_(vector<float>(n, 0)),
    bias_(0)
{

}

void Weighted::randomize(const float& scale)
{
    for (float& weight : weights_){
        weight = random_uniform() * scale;
    }

    bias_ = random_uniform() * scale;
}

void Weighted::mutate(const float& scale)
{
    for (float& weight : weights_){
        weight += random_normal() * scale;
    }

    bias_ += random_normal() * scale;
}

const float& Weighted::add_weight(const float& value)
{
    weights_.push_back(value);
    return *(weights_.end());
}

void Weighted::set_weights(const vector<float>& weights)
{
    if (weights.size() < weights_.size()){
        throw "Can not set weights, because argument vector is too small.";
    }
    vector<float>::iterator self_iterator = weights_.begin();
    vector<float>::const_iterator other_iterator = weights.begin();

    while(self_iterator != weights_.end()){
        *self_iterator = *other_iterator;
        self_iterator++;
        other_iterator++;
    }
}

void Weighted::set_bias(const float& value)
{
    bias_ = value;
}

const vector<float>& Weighted::get_weights() const {
    return weights_;
}

const float&Weighted::get_bias() const
{
    return bias_;
}

void Weighted::set_equal(const Weighted& target)
{
    const vector<float>& target_weights = target.get_weights();
    if (target_weights.size() != weights_.size()){
        throw "Can not copy weights, because target object has different number of weights";
    }
    set_weights(target_weights);
    set_bias(target.get_bias());
}

void Weighted::make_average_from(const vector<const Weighted*>& objects)
{
    vector<float> average_weights = {};
    float sum = 0;
    const Weighted* first = *(objects.begin());
    int number_of_weights = first->size();
    //for each weight
    for(int weight_index = 0; weight_index < number_of_weights; weight_index++){
        sum = 0;
        //average the same weight from all objects
        for(const Weighted* object : objects){
            sum += object->weight_at(weight_index);
        }
        average_weights.push_back(sum / objects.size());
    }

    set_weights(average_weights);

    //for bias
    sum = 0;
    for(const Weighted* object : objects){
        sum += object->get_bias();
    }
    set_bias(sum / objects.size());
}

const float& Weighted::weight_at(int i) const
{
    return weights_.at(i);
}

int Weighted::size() const
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
