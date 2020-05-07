#include <random>

#include "random.hpp"
#include "exception.hpp"

static std::mt19937 e;




void seed(int i)
{
  seed(std::seed_seq{i});
}

void seed(std::seed_seq s)
{
  e = std::mt19937(s);
}







double exp_rand(double lambda)
{
  std::exponential_distribution nd(lambda);
  return nd(e);
}

double normal_rand(double mean, double std)
{
  std::normal_distribution nd(mean, std);
  return nd(e);
}

double uniform_rand(double min, double max)
{
  std::uniform_real_distribution urd(min, max);
  return urd(e);
}

double lognormal_rand(double mean, double std)
{
  std::lognormal_distribution<> d(mean, std);
  return d(e);
}

double binormal_rand(double mn1, double std1, double mn2, double std2, double p)
{
  double P = uniform_rand(0.0, 1.0);
  if (P > p) {
    return normal_rand(mn1, std1);
  }
  return normal_rand(mn2, std2);
}

double bilognormal_rand(double mn1, double std1, double mn2, double std2, double p)
{
  double P = uniform_rand(0.0, 1.0);
  if (P > p) {
    return lognormal_rand(mn1, std1);
  }
  return lognormal_rand(mn2, std2);
}


int uniform_rand_i(int min, int max)
{
  if (min > max)
    throw MathError("in uniform_rand_i: max is less than min!");

  std::uniform_int_distribution urd(min, max);
  return urd(e);
}



double likelihood_to_numerical_probability(RandomLikelihood likelihood)
{
  switch (likelihood) {

    case Likelihood_Impossible:
      return -1.0;

    case Likelihood_VeryRare:
      return 0.01;

    case Likelihood_Rare:
      return 0.05;

    case Likelihood_Uncommon:
      return 0.1;

    case Likelihood_Common:
      return 0.55;

    case Likelihood_Ubiquitous:
      return 0.85;

    case Likelihood_Certain:
      return 2.0;
  }

  // switch above means control will never reach here. throw exception *just in
  // case* I break something and control *does* reach here.
  throw AuthorError("control reaches end of likelihood_to_numerical_probability in src/util/random.cpp.");
}


bool check_likelihood(RandomLikelihood likelihood)
{
  return uniform_rand(0.0, 1.0) < likelihood_to_numerical_probability(likelihood);
}


RandomLikelihood str2likelihood(std::string s)
{
  if (s.compare("impossible") == 0) {
    return Likelihood_Impossible;
  }
  else if (s.compare("very rare") == 0) {
    return Likelihood_VeryRare;
  }
  else if (s.compare("rare") == 0) {
    return Likelihood_Rare;
  }
  else if (s.compare("uncommon") == 0) {
    return Likelihood_Uncommon;
  }
  else if (s.compare("common") == 0) {
    return Likelihood_Common;
  }
  else if (s.compare("ubiquitous") == 0) {
    return Likelihood_Ubiquitous;
  }
  else if (s.compare("certain") == 0) {
    return Likelihood_Certain;
  }
  else {
    throw AuthorError(Formatter() << "Uknown likelihood: " << s << ".");
  }
}
