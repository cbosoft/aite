#include "derived_statistic.hpp"

DerivedStatistic::DerivedStatistic(Statistic *base_stat)
  : base_stat(base_stat)
{
  // do nothing
}

DerivedStatistic::~DerivedStatistic()
{
  // do nothing
}

double DerivedStatistic::get_base() const
{
  return this->base_stat->get_value();
}
