#include "activity.hpp"

Activity::Activity(Colony &colony, double number, std::string name)
  :
    start_time(Universe::get_universe()->get_time()),
    name(name),
    number(number),
    colony(colony)
{
}

Activity::~Activity()
{
  if (this->started) {
    if (number > 0.0) {
      this->colony.stats.population_stats.number
        .remove_additive_modifier(name);
    }
  }
}


bool Activity::try_start()
{
  double available = this->colony.stats.population_stats.number.get_value();
  this->started = available >= this->number;

  if (!this->started) {
    this->colony.add_message(Formatter()
        << BOLD << "Job cancelled. " << RESET
        << "Cannot start " << name << " with " << this->number
        << " people: not enough people available! ("
        << format_number(available) << ")");
  }
  else {
    this->colony.stats.population_stats.number
      .set_additive_modifier(name, -this->number);
  }

  return this->started;
}
