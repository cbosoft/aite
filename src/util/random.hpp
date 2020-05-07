#pragma once
#include <random>
#include <list>
#include <iterator>

#include "exception.hpp"

enum RandomLikelihood {
  Likelihood_Impossible,   // nothing is truly impossible!
  Likelihood_VeryRare,     // unheard of, thought impossible, not even considered
  Likelihood_Rare,         // not seen much, maybe once-in-a-lifetime
  Likelihood_Uncommon,     // heard of, and seen from time to time
  Likelihood_Common,       // more often than not
  Likelihood_Ubiquitous,  // frequently seen
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

double likelihood_to_numerical_probability(RandomLikelihood likelihood);
bool check_likelihood(RandomLikelihood likelihood);
RandomLikelihood str2likelihood(std::string s);


// https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container
template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    std::advance(start, uniform_rand_i(0, std::distance(start, end)-1));
    return start;
}

template<typename T>
T probability_weighted_choice(std::list<RandomLikelihood> likelihoods, std::list<T> values)
{
  int rv_index = -1;
  double random_number = uniform_rand_i(0.0, 1.0);
  double rv_chance = 10.0;

  int i = 0;
  for (auto likelihood : likelihoods) {
    double numerical_chance = likelihood_to_numerical_probability(likelihood);
    if ((numerical_chance > random_number) and (rv_chance > random_number)) {
      rv_index = i;
      rv_chance = numerical_chance;
    }
    i ++;
  }

  if (rv_index < 0)
    throw NonOccurrenceError("No event occurred");

  auto it = values.begin();
  for (int i = 0; i < rv_index; i++, it++);
  return *it;

}
