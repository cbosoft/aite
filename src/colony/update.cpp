#include "colony.hpp"

void Colony::update(double dt)
{
  // POPULATION
  this->population_stats.number += (this->population_stats.birth_rate - this->population_stats.death_rate) * dt * this->population_stats.number;
  // reduce diversity over time for small populations, increase for large
  // slightly increase xp


  // TECHNOLOGY
  // slightly increase xp

  //  CULTURE
  // reduce or increase peace based on art and religion outputs
  // slightly increase xp
}
