#include "../util/format.hpp"

#include "construct_habitat.hpp"

ConstructHabitat::ConstructHabitat(Colony &colony, const ProjectData &data)
  : Project(colony, data, "construct habitat")
{
}

ConstructHabitat::~ConstructHabitat()
{
}

bool ConstructHabitat::check()
{
  double volume_left = colony.resources.volume.get_amount_available();
  if (volume_left <= 0.0) {
    this->colony.add_message(Formatter() << FG_RED << BOLD << "Construction cancelled" << RESET << ": no more space.");
    return false;
  }

  static double previous_time = this->get_start_time();
  double time = Universe::get_time();
  double dt = time - previous_time;
  double volume_constructed = dt*100.0; // TODO get construction rate from derived stats
  
  if (volume_left < volume_constructed) {
    volume_constructed = volume_left;
  }

  this->colony.resources.volume -= volume_constructed;
  this->colony.processed_resources.habitable_volume += volume_constructed;

  return true;
}
