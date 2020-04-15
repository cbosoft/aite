#include "planet.hpp"

Planet::Planet(unsigned long long id)
{
  this->id = id;
  this->description_data.set = false;
}

Planet::~Planet()
{
  // do nothing
}

double Planet::get_diameter() const
{
  return this->diameter;
}

unsigned long long Planet::get_id() const
{
  return this->id;
}
