#pragma once
#include <random>
#include <iterator>

enum RandomLikelihood {
  Likelihood_Impossible,   // nothing is truly impossible!
  Likelihood_VeryRare,     // unheard of, thought impossible, not even considered
  Likelihood_Rare,         // not seen much, maybe once-in-a-lifetime
  Likelihood_Uncommon,     // heard of, and seen from time to time
  Likelihood_Common,       // more often than not
  Likelihood_Ubiquitious,  // frequently seen
  Likelihood_Certain       // nothing is truly certain!
};

void seed(int s);
void seed(std::seed_seq s);
double exp_rand(double lambda);
double normal_rand(double mean, double std);
double uniform_rand(double min, double max);
double lognormal_rand(double mean, double std);
double binormal_rand(double mn1, double std1, double mn2, double std2, double p);
double bilognormal_rand(double mn1, double std1, double mn2, double std2, double p);

int uniform_rand_i(int min, int max);

bool check_likelihood(RandomLikelihood likelihood);


// https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container
template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    std::advance(start, uniform_rand_i(0, std::distance(start, end)-1));
    return start;
}
