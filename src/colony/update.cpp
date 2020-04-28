#include "colony.hpp"

void Colony::update(double dt)
{
  // Stats
  this->stats.update(dt);
  // Resources
  // for (auto activity : this->activities) {
  //   activity->update_resources(this->resources, this->processed_resources);
  // }

}
