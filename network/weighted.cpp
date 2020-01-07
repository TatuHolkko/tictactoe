#include "weighted.h"

Weighted::Weighted()
{

}

float Weighted::random_normal()
{
    return (float)norm_dist_(rand_eng_);
}

float Weighted::random_number()
{
    return rand() % 10000 / 5000.0 - 1;
}
