#include <cmath>
#include <iostream>

#include "derived_statistic.hpp"

PowerDerivedStatistic::PowerDerivedStatistic(Statistic *base_stat, double p, double m, double c)
  : DerivedStatistic(base_stat), p(p), m(m), c(c)
{
  // do nothing
}

PowerDerivedStatistic::~PowerDerivedStatistic()
{
  // do nothing
}

double PowerDerivedStatistic::get_base() const
{
  double rv = std::pow(this->base_stats.front()->get_value(), this->p)*this->m + this->c;
  return rv;
}
