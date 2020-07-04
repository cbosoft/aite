#include "../util/formatter.hpp"
#include "../util/colour.hpp"

#include "colony.hpp"

void Colony::update(double dt)
{
  this->number *= 1.0 + this->growth_rate*dt;

  // Explore?
  // if (this->ready_to_expand()) this->explore();
}
