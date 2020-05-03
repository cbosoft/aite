#include "derived_statistic.hpp"

SumDerivedStatistic::SumDerivedStatistic(std::list<DerivedStatistic_ptr> components)
  : DerivedStatistic(components)
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

  if (this->rawptr) {
    for (auto stat : this->base_stats_rawptr )
    {
      total += stat->get_value();
    }
  }
  else {
    for (auto stat : this->base_stats_shrd )
    {
      total += stat->get_value();
    }
  }

  return total;
}
