#include "../util/format.hpp"
#include "../colony/colony.hpp"

#include "construct_habitat.hpp"


ConstructHabitat::ConstructHabitat(Colony &colony, const ProjectData &data)
  : Project(colony, data, "construct habitat")
{
}


ConstructHabitat::~ConstructHabitat()
{
}


ProjectStatus ConstructHabitat::get_status()
{
  double required_volume = colony.stats.derived.required_habitable_volume->get_value();
  double current_volume = colony.processed_resources.habitable_volume.get_amount_available();
  this->volume_left = colony.resources.volume.get_amount_available();

  // TODO: move to data
  double thresh = 0.1, thresh_big = 0.5;
  double thresh_mult = 1.0 + thresh, big_thresh_mult = 1.0 + thresh_big;

  if (this->volume_left <= 0.0) {
    this->pause("no more space.");
    return this->status;
  }

  switch (this->status) {

    case PS_Paused:
      if (current_volume < required_volume*thresh_mult) {
        this->unpause();
      }
      break;

    case PS_Active:
      if (current_volume >= required_volume*big_thresh_mult) {
        this->pause("space requirement fulfilled.");
      }
      break;

    default:
      break;

  }

  return this->status;
}


void ConstructHabitat::do_work()
{
  static double previous_time = this->get_start_time();
  double time = Universe::get_time();
  double dt = time - previous_time;
  double volume_constructed = dt*200.0; // TODO get construction rate from derived stats
  previous_time = time;

  if (this->volume_left < volume_constructed) {
    // can't build more than is available...
    volume_constructed = volume_left;
  }

  this->colony.resources.volume -= volume_constructed;
  this->colony.processed_resources.habitable_volume += volume_constructed;
}
