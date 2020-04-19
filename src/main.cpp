#include <iostream>
#include <ctime>

#include "colony/colony.hpp"
#include "planet/planet.hpp"
#include "universe/universe.hpp"
#include "util/random.hpp"
#include "event/new_colony_event.hpp"

int main(void)
{
  seed(time(NULL));

  Universe_ptr universe = Universe::get_universe();

  // ask the universe to create new colony
  universe->add_event(NewColonyEvent::create("new1"));

  // run event processing loop
  universe->run_events();
}
