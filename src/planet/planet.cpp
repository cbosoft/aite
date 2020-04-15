#include "planet.hpp"

Planet::Planet()
{
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
