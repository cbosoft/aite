#include <iostream>

#include "colony.hpp"


Colony::Colony(std::string name)
{
  this->name = name;
}

Colony::~Colony()
{
  // do nothing
}



void Colony::startoff(Planet_ptr planet)
{
  std::cerr << this->describe_planet(planet) << std::endl;
}
