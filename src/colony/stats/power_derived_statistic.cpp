#include <cmath>
#include <iostream>

#include "derived_statistic.hpp"

PowerDerivedStatistic::PowerDerivedStatistic(Statistic *base_stat, double p, double m, double c)
  : DerivedStatistic(base_stat), p(p), m(m), c(c)
{
  // do nothing
  std::cerr << "p " << p << ", m " << m << ", c " << c << std::endl;
}

PowerDerivedStatistic::~PowerDerivedStatistic()
{
  // do nothing
}

double PowerDerivedStatistic::get_base() const
{
  double rv = std::pow(this->base_stat->get_value(), this->p)*this->m + this->c;
  std::cerr << "rv: " << rv << std::endl;
  return rv;
}
