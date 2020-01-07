#ifndef WEIGHTED_H
#define WEIGHTED_H

#include <vector>
#include <random>

using namespace std;

class Weighted
{
public:
    Weighted(int n);

    //uniformly randomize all weights from -<scale> to <scale>
    void randomize(const float& scale);

    //use a normal distribution with stddev of <scale> to mutate all weights
    void mutate(const float& scale);

protected:
    vector<float> weights_;

private:
    //normal distribution used by the random_normal function
    normal_distribution<double> norm_dist_ = normal_distribution<double>(0.0,1.0);
    default_random_engine rand_eng_;

    //return a normally distributed float with stddev 1 and avg of 0
    float random_normal();

    //return a uniformally random number between -1 and 1
    static float random_number();
};

#endif // WEIGHTED_H
