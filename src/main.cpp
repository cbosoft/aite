#include <iostream>
#include <ctime>

#include "colony/colony.hpp"
#include "planet/planet.hpp"
#include "universe/universe.hpp"
#include "util/random.hpp"
#include "event/new_colony_event.hpp"
#include "feature/feature.hpp"

int main(void)
{
  seed(time(NULL));

  for (int i = 0; i < 100; i++) {
    Feature_ptr feat = Feature::generate(FO_Planet);
    std::cerr << feat->describe() << "\n\n";
  }
}
