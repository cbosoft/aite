#include "resource.hpp"

Resource::Resource()
  : Resource(0.0)
{
  // do nothing
}

Resource::Resource(double fraction)
  : fraction_visible(fraction)
{
  // do nothing
}

Resource::~Resource()
{
  // do nothing
}

double Resource::get_amount_available() const
{
  return this->total*this->fraction_visible - this->amount_used;
}

void Resource::set_fraction_visible(double value)
{
  this->fraction_visible = value;
}

void Resource::use(double amount)
{
  this->amount_used += amount;
}

void Resource::increase(double amount)
{
  this->total += amount;
}
