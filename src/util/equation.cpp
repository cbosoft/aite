#include "equation.hpp"

LinearEqn::LinearEqn(double m, double c)
  : m(m), c(c)
{
  // do nothing
}


double LinearEqn::get_value(double x) const
{
  return (this->m*x) + this->c;
}
