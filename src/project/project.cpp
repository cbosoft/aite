#include "project.hpp"

Project::Project(Colony &colony, ProjectData data, std::string name)
  :
    name(name),
    data(data),
    colony(colony)
{
}

Project::~Project()
{
  if (this->started) {
    if (data.get_number() > 0.0) {
      this->colony.stats.population.number
        .remove_additive_modifier(name);
    }
  }
}


bool Project::check_can_start()
{
  double available = this->colony.stats.population.number.get_value();
  bool enough_population = available >= this->data.get_number();

  // reason should start with a lower case letter as it will be used in a
  // sentence like:
  // "<b>Cannot start project: </b> $REASON"

  if (not enough_population) {
    this->reason = Formatter() << "not enough people unoccupied (" << available << "/" << this->data.get_number() << ").";
    return false;
  }


  // TODO other project requirements (space, energy, other resources, and so on)
  return true;
}

std::string Project::get_reason_cannot_start() const
{
  return this->reason;
}

void Project::start()
{
  this->colony.stats.population.number
    .set_additive_modifier(name, -this->data.get_number());

  // TODO initial resource costs

  this->started = true;
}
