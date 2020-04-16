#include "system.hpp"
#include "../colony/colony.hpp"
#include "../util/random.hpp"

void System::introduce(Colony_ptr colony)
{
  Planet_ptr planet = this->planets[uniform_rand_i(0, this->planets.size()-1)];

  colony->startoff(planet);
}
