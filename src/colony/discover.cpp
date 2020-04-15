#include <sstream>

#include "colony.hpp"
#include "../planet/planet.hpp"

std::string Colony::name_planet(const std::shared_ptr<Planet> planet) const
{
  // TODO different naming conventions?

  //auto d = planet->describe();

  std::stringstream ss;
  ss << "Planet #" << planet->get_id();
  return ss.str();
}

void Colony::discover_planet(const std::shared_ptr<Planet> planet)
{
  std::string name = this->name_planet(planet);
  this->planet_log[planet->get_id()] = name;
}
