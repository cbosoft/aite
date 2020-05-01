#include "resource.hpp"

Resource::Resource()
  : Resource(0.0)
{
  // do nothing
}

Resource::Resource(double amount)
  : total(amount), amount_used(0.0)
{
  // do nothing
}

Resource::~Resource()
{
  // do nothing
}

double Resource::get_amount_available() const
{
  return this->total - this->amount_used;
}

void Resource::use(double amount)
{
  this->amount_used += amount;
}

void Resource::increase(double amount)
{
  this->total += amount;
}
