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
  double v =
    this->rawptr?
    this->base_stats_rawptr.front()->get_value() :
    this->base_stats_shrd.front()->get_value();
  return v*this->m + this->c;
}
