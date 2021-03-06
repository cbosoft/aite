#include <cmath>

#include "../constants.hpp"
#include "../colony/colony.hpp"

#include "object.hpp"

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


// TODO: method to set population
// void SystemObject::set_population(double population, Colony &colony) {
//   if (not colony.can_inhabit(*this)) {
//     return false;
//   }
//   else {
//     this->population = population;
//     return true;
//   }
// }

double SystemObject::get_luminosity() const
{
  return this->resources.luminosity;
}

double SystemObject::get_position() const
{
  return this->position;
}


double SystemObject::get_pressure() const
{
  return this->pressure;
}


double SystemObject::get_temperature() const
{
  return this->temperature;
}


double SystemObject::get_gravity() const
{
  return this->density * this->object_diameter * M_PI * CONST_G * CONST_AUm * (1./6.);
}

unsigned long SystemObject::get_id() const
{
  return this->id;
}


System_ptr SystemObject::get_system() const
{
  return this->system;
}


std::string SystemObject::get_colour() const
{
  return this->colour;
}

Resources *SystemObject::get_resources_rawptr()
{
  return &this->resources;
}

void SystemObject::set_luminosity(double luminosity)
{
  this->resources.luminosity = luminosity;
}

double SystemObject::get_radius() const
{
  return this->object_diameter*0.5;
}

double SystemObject::get_diameter() const
{
  return this->object_diameter;
}
