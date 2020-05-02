#include "derived_statistic.hpp"

DerivedStatistic::DerivedStatistic()
  : DerivedStatistic(nullptr)
{
  // do nothing
}

DerivedStatistic::DerivedStatistic(Statistic * base_stat)
  : DerivedStatistic(std::list<Statistic *>({base_stat}))
{
  // do nothing
}

DerivedStatistic::DerivedStatistic(std::list<Statistic *> base_stats)
  : base_stats(base_stats)
{
  // do nothing
}

DerivedStatistic::~DerivedStatistic()
{
  // do nothing
}

double DerivedStatistic::get_base() const
{
  return this->base_stats.front()->get_value();
}
