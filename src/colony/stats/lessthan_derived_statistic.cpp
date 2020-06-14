#include "derived_statistic.hpp"

LessThanDerivedStatistic::LessThanDerivedStatistic(DerivedStatistic_ptr left, DerivedStatistic_ptr right, double value_true, double value_false, std::string name)
  : 
    Statistic(name),
    left(left),
    right(right),
    value_true(value_true),
    value_false(value_false)
{
  // do nothing
}

LessThanDerivedStatistic::~LessThanDerivedStatistic()
{
  // do nothing
}

double LessThanDerivedStatistic::get_base() const
{
  double left = this->left->get_value();
  double right = this->right->get_value();

  return (left < right) ? value_true : value_false;
}
