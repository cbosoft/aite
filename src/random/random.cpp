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

double weibull_rand(double a, double b)
{
  std::weibull_distribution<> d(a, b);
  return d(e);
}
