#include <limits>

#include "universe.hpp"

Universe::Universe()
{
  // in the beginning there was nothing, and then bam! there was something.
  this->size = std::numeric_limits<double>::max();
}

Universe::~Universe()
{
  // do nothing
}

double Universe::get_time() const
{
  return this->time;
}


static Universe_ptr the_universe = nullptr;

Universe_ptr Universe::get_universe()
{
  if (the_universe == nullptr)
    the_universe = std::make_shared<Universe>();

  return the_universe;
}
