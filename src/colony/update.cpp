#include "../util/formatter.hpp"
#include "../util/colour.hpp"

#include "colony.hpp"

void Colony::update(double dt)
{
  // Stats
  this->stats.update(dt);
  double dpop = this->stats.population_stats.number.get_delta();

  static bool notified_1 = false;
  if ((dpop >= 1.0) and not notified_1) {
    this->add_message(Formatter() 
        << BOLD << "First colonial birth." << RESET);
    notified_1 = true;
  }

  // Resources
  // for (auto activity : this->activities) {
  //   activity->update_resources(this->resources, this->processed_resources);
  // }

}
