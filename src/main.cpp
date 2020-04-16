#include <iostream>
#include <ctime>

#include "colony/colony.hpp"
#include "planet/planet.hpp"
#include "universe/universe.hpp"
#include "util/random.hpp"

int main(void)
{
  seed(time(NULL));

  Universe_ptr universe = Universe::get_universe();
  universe->add_colony("new1");
}
