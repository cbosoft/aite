#include "planet.hpp"

Planet::Planet(unsigned long id, double position, System_ptr system) 
  : SystemObject(position), id(id), system(system)
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

unsigned long Planet::get_id() const
{
  return this->id;
}

System_ptr Planet::get_system() const
{
  return this->system;
}
