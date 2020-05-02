#include "derived_statistic.hpp"

SumDerivedStatistic::SumDerivedStatistic(std::list<Statistic *> base_stats)
  : DerivedStatistic(base_stats)
{
  // do nothing
}

SumDerivedStatistic::~SumDerivedStatistic()
{
  // do nothing
}

double SumDerivedStatistic::get_base() const
{
  double total = 0.0;
  for (auto stat : this->base_stats )
  {
    total += stat->get_value();
  }

  return total;
}
