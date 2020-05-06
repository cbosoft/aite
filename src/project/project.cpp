#include "../colony/colony.hpp"
#include "project.hpp"

Project::Project(Colony &colony, ProjectData data, std::string name)
  :
    name(name),
    status(PS_Inactive),
    data(data),
    colony(colony)
{
}

Project::~Project()
{
  this->release_resources();
}


bool Project::check_can_start()
{
  double available = this->colony.stats.population.number.get_value();
  bool enough_population = available >= this->data.get_number();

  // reason should start with a lower case letter as it will be used in a
  // sentence like:
  // "<b>Cannot start project: </b> $REASON"

  if (not enough_population) {
    this->error = Formatter() << "not enough people unoccupied (" << available << "/" << this->data.get_number() << ").";
    return false;
  }


  // TODO other project requirements (space, energy, other resources, and so on)
  return true;
}

std::string Project::get_error() const
{
  return this->error;
}

std::string Project::get_name() const
{
  return this->name;
}

ProjectData Project::get_data() const
{
  return this->data;
}

void Project::set_data(ProjectData data)
{
  this->data = data;
}

double Project::get_start_time() const
{
  return this->data.get_start_time();
}

double Project::get_elapsed_time() const
{
  return Universe::get_universe()->get_time() - this->get_start_time();
}

ProjectStatus Project::update()
{
  this->status = this->get_status();

  if (this->status == PS_Active)
    this->do_work();

  return this->status;
}

ProjectStatus Project::get_status()
{
  return this->status;
}

void Project::do_work()
{
  // do nothing
}

void Project::start()
{
  this->take_resources();
  this->status = PS_Active;
}

void Project::take_resources()
{
  this->colony.stats.population.number
    .set_additive_modifier(name, -this->data.get_number());
}

void Project::release_resources()
{
  this->colony.stats.population.number
    .set_additive_modifier(name, 0.0);
}

void Project::pause(std::string err)
{
  if (err.size())
    this->error = err;

  this->release_resources();
  this->status = PS_Paused;
}

void Project::unpause()
{
  this->take_resources();
  this->status = PS_Active;
}

std::string Project::get_status_string() const
{
  std::stringstream ss;
  switch (this->status) {
    case PS_Active:
      ss << "active";
      break;
    case PS_Inactive:
      ss << "inactive";
      break;
    case PS_Paused:
      ss << "paused because " << this->error;
      break;
    case PS_Error:
      ss << "cancelled because " << this->error;
      break;
    case PS_Finished:
      ss << "finished";
      break;
  }
  return ss.str();
}
