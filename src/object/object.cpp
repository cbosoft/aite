#include "object.hpp"
#include <cmath>
#include "../constants.hpp"

static unsigned long id_counter = 0;

SystemObject::SystemObject(System_ptr system, double position)
  :
    id(++id_counter),
    system(system),
    position(position),
    population(0.0)
{
  this->description_data.set = false;
}


bool SystemObject::try_inhabit(double population, Colony &colony) {
  if (not colony.can_inhabit(*this)) {
    return false;
  }
  else {
    this->population = population;
    return true;
  }
}

double SystemObject::get_position() const
{
  return this->position;
}


double SystemObject::get_pressure() const
{
  return this->pressure[2];
}


double SystemObject::get_temperature() const
{
  return this->temperature[2];
}


double SystemObject::get_gravity() const
{
  return this->density[3] * this->object_diameter * M_PI * CONST_G * CONST_AUm * (1./6.);
}

unsigned long SystemObject::get_id() const
{
  return this->id;
}


System_ptr SystemObject::get_system() const
{
  return this->system;
}
