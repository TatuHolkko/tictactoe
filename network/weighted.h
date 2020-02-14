/* this is a module for objects that hold an array of floats (weights)
 * that can be mutated and randomized
 */
#ifndef WEIGHTED_H
#define WEIGHTED_H

#include <vector>
#include <random>

using namespace std;

class Weighted
{
public:

    //initialize withn no weights
    Weighted();

    //intialize the weight vector with n zeros
    Weighted(int n);

    //uniformly randomize all weights from -<scale> to <scale>
    void randomize(const float& scale);

    //use a normal distribution with stddev of <scale> to mutate all weights
    void mutate(const float& scale);

    //add a weight with value: <value> and return a reference to the saved float
    const float& add_weight(const float& value);

    //set all weights to equal <weights>. <weights> must be a vector that has at least as many
    //elements as weights of this Weighted object.
    void set_weights(const vector<float>& weights);

    //copy all weight values from <target> to this object
    void set_equal(const Weighted& target);

    //get weights
    const vector<float>& get_weights() const;

    //set this object's weights equal to the average of the parameter objects' weights
    void make_average_from(const vector<const Weighted*>& objects);

    //return the weight at the given index
    const float& weight_at(int i);

    //return the number of weights
    int size();

protected:
    vector<float> weights_;

private:
    //normal distribution used by the random_normal function
    normal_distribution<double> norm_dist_ = normal_distribution<double>(0.0,1.0);
    default_random_engine rand_eng_;

    //return a normally distributed float with stddev 1 and avg of 0
    float random_normal();

    //return a uniformally random number between -1 and 1
    static float random_uniform();
};

#endif // WEIGHTED_H
