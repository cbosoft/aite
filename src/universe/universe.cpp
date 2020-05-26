#include <limits>

#include "universe.hpp"

Universe::Universe()
  :
    size(std::numeric_limits<double>::max()),
    running(false),
    time(0)
{
  // in the beginning there was nothing, and then bam! there was something.
}

Universe::~Universe()
{
  // do nothing
}

void Universe::set_time(double new_time)
{
  this->time = new_time;
}

Colony_ptr Universe::get_colony(std::string name)
{
  return this->colonies[name];
}


static Universe_ptr the_universe = nullptr;

Universe_ptr Universe::get_universe()
{
  if (the_universe == nullptr)
    the_universe = std::make_shared<Universe>();

  return the_universe;
}

double Universe::get_time()
{
  return the_universe->time;
}
