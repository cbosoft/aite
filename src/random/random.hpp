#pragma once
#include <random>

void seed(int s);
void seed(std::seed_seq s);
double normal_rand(double mean, double std);
double uniform_rand(double min, double max);
double weibull_rand(double a, double b);
