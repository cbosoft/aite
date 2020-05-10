#include <iostream>
#include <ctime>

#include "util/random.hpp"
#include "universe/universe.hpp"
#include "galaxy/galaxy.hpp"
#include "colony/colony.hpp"
#include "system/system.hpp"

int main(void)
{

  seed(time(NULL));

  auto colony = std::make_shared<Colony>();
  auto universe = Universe::get_universe();
  auto galaxy = Galaxy::generate(Vec3({0.0, 0.0, 0.0}));
  auto system = System::generate(Vec3({0.0, 0.0, 0.0}), galaxy);
  auto objects = system->get_objects();

  for (auto &object : objects) {
    colony->discover(object);
    std::cerr << colony->describe(object) << std::endl;
  }

}
