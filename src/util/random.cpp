#include "random.hpp"
#include <random>

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
  std::uniform_int_distribution urd(min, max);
  return urd(e);
}
