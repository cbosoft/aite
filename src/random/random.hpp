#pragma once
#include <random>

void seed(int s);
void seed(std::seed_seq s);
double exp_rand(double lambda);
double normal_rand(double mean, double std);
double uniform_rand(double min, double max);
double lognormal_rand(double mean, double std);
double binormal_rand(double mn1, double std1, double mn2, double std2, double p);
double bilognormal_rand(double mn1, double std1, double mn2, double std2, double p);
