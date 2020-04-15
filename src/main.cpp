#include <iostream>
#include <ctime>

#include "colony/colony.hpp"
#include "planet/planet.hpp"
#include "random/random.hpp"

int main(void)
{
  seed(time(NULL));

  auto planet = Planet::generate();
  auto colony = Colony();
  colony.discover_planet(planet);
  std::cerr << colony.describe_planet(planet) << std::endl;
}
