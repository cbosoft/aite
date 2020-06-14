#include <cmath>

#include "derived_statistic.hpp"

PowerDerivedStatistic::PowerDerivedStatistic(Statistic *base_stat, double p, double m, double c, std::string name)
  : DerivedStatistic(base_stat, name), p(p), m(m), c(c)
{
  // do nothing
}

PowerDerivedStatistic::~PowerDerivedStatistic()
{
  // do nothing
}

double PowerDerivedStatistic::get_base() const
{
  double v = DerivedStatistic::get_base();
  double rv = std::pow(v, this->p)*this->m + this->c;
  return rv;
}
