#include "derived_statistic.hpp"

LinearDerivedStatistic::LinearDerivedStatistic(Statistic *base_stat, double m, double c)
  : DerivedStatistic(base_stat), m(m), c(c)
{
  // do nothing
}

LinearDerivedStatistic::~LinearDerivedStatistic()
{
  // do nothing
}

double LinearDerivedStatistic::get_base() const
{
  return this->base_stat->get_value()*this->m + this->c;
}
