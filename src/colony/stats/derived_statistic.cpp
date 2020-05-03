#include "derived_statistic.hpp"

DerivedStatistic::DerivedStatistic()
{
  // do nothing
}

DerivedStatistic::DerivedStatistic(Statistic * base_stat)
  : DerivedStatistic(std::list<Statistic *>({base_stat}))
{
  // do nothing
}

DerivedStatistic::DerivedStatistic(std::list<Statistic *> base_stats)
  :
    rawptr(true),
    base_stats_rawptr(base_stats)
{
}

DerivedStatistic::DerivedStatistic(DerivedStatistic_ptr base_stat)
  : DerivedStatistic(std::list<DerivedStatistic_ptr>({base_stat}))
{
  // do nothing
}

DerivedStatistic::DerivedStatistic(std::list<DerivedStatistic_ptr> base_stats)
  :
    rawptr(false),
    base_stats_shrd(base_stats)
{
}

DerivedStatistic::~DerivedStatistic()
{
  // do nothing
}

double DerivedStatistic::get_base() const
{
  if (this->rawptr) {
    return this->base_stats_rawptr.front()->get_value();
  }
  else {
    return this->base_stats_shrd.front()->get_value();
  }
}
