#include "project.hpp"

Project::Project(Colony &colony, double number, std::string name)
  :
    start_time(Universe::get_universe()->get_time()),
    name(name),
    number(number),
    colony(colony)
{
}

Project::~Project()
{
  if (this->started) {
    if (number > 0.0) {
      this->colony.stats.population.number
        .remove_additive_modifier(name);
    }
  }
}


bool Project::try_start()
{
  double available = this->colony.stats.population.number.get_value();
  this->started = available >= this->number;

  if (!this->started) {
    this->colony.add_message(Formatter()
        << BOLD << "Job cancelled. " << RESET
        << "Cannot start " << name << " with " << this->number
        << " people: not enough people available! ("
        << format_number(available) << ")");
  }
  else {
    this->colony.stats.population.number
      .set_additive_modifier(name, -this->number);
  }

  return this->started;
}
