#include <iostream>

#include "colony.hpp"
#include "../universe/universe.hpp"
#include "../object/object.hpp"
#include "../system/system.hpp"
#include "../project/project.hpp"


Colony::Colony(std::string name, SystemObject_ptr planet, double time_of_inception)
  : time_of_inception(time_of_inception), name(name)
{

  // set up stats
  this->stats.population = {
      .number    = Statistic(100),
      .medecine  = Statistic(0),
      .mood      = Statistic(0),
      .longevity = Statistic(75)
  };

  // research_effort(0.0),
  this->stats.technology = {
    .agriculture          = Statistic(0),
    .materials_gathering  = Statistic(0),
    .materials_processing = Statistic(0),
    .power_generation     = Statistic(0),
    .astrogation          = Statistic(0)
  };

  this->stats.culture = {
    .religion = Statistic(0),
    .art      = Statistic(0),
    .social   = Statistic(0),
    .politics = Statistic(50),
  };


  // set up derived stats
  this->stats.derived.growth_rate =
    std::make_shared<LinearDerivedStatistic>(&this->stats.population.number, 0.0, 0.2);
  this->stats.derived.required_habitable_volume =
    std::make_shared<LinearDerivedStatistic>(&this->stats.population.number, 80.0, 0.0); // roughly 80m3 per person

  this->stats.derived.travel_speed =
    std::make_shared<DerivedResource<PooledResource>>(&this->resources.nonmetallic_ore);

  // this->stats.derived.travel_speed =
  //   std::make_shared<PowerDerivedStatistic>(&this->stats.technology.astrogation, 3.0, 1.0, 1.0);
  this->stats.derived.max_habitable_temperature =
    std::make_shared<PowerDerivedStatistic>(&this->stats.technology.astrogation, 0.5, 100.0, 373.0);
  this->stats.derived.max_habitable_gravity =
    std::make_shared<PowerDerivedStatistic>(&this->stats.technology.astrogation, 0.33, 1.1, 5.0);


  // add reference to universe
  this->universe = Universe::get_universe();

  this->startoff(planet);

  double starting_vol = this->stats.population.number.get_value() * 10;
  this->resources.volume -= starting_vol;
  this->processed_resources.habitable_volume += starting_vol;
}


Colony::~Colony()
{
  // do nothing
}

double Colony::get_number()
{
  return this->stats.population.number;
}

double Colony::get_inception_time()
{
  return this->time_of_inception;
}

void Colony::add_message(std::string message)
{
  std::lock_guard<std::mutex> lock(this->messages_mutex);
  this->messages.push_back(message);
}

std::list<std::string> Colony::get_messages()
{
  std::lock_guard<std::mutex> lock(this->messages_mutex);
  std::list<std::string> rv(this->messages);
  this->messages.erase(this->messages.begin(), this->messages.end());
  return rv;
}

void Colony::startoff(SystemObject_ptr planet)
{
  this->discover(planet);
  if (not this->try_inhabit(planet, this->stats.population.number)) {
    throw AuthorError(Formatter() << "Starting planet not inhabitable!");
  }
  else {
    this->resources.add_source(planet->get_resources_rawptr());
  }
  this->inhabited_objects.push_back(planet);

  auto system = planet->get_system();
  this->inhabited_systems.push_back(system);
  auto galaxy = system->get_galaxy();
  this->inhabited_galaxies.push_back(galaxy);
}

bool Colony::can_inhabit(SystemObject_ptr object)
{
  double temperature = object->get_temperature();
  double gravity = object->get_gravity();
  bool temp_ok = temperature < this->stats.derived.max_habitable_temperature->get_value();
  bool gravity_ok = gravity < this->stats.derived.max_habitable_gravity->get_value();
  return temp_ok && gravity_ok;
}

bool Colony::try_inhabit(SystemObject_ptr object, double number)
{
  if (not this->can_inhabit(object))
    return false;

  // TODO: set population on planet
  (void) number;

  this->add_message(Formatter()
      << BOLD << "Inhabited " << object->get_object_name() << " "
      << this->get_name(object) << "." << RESET);
  return true;
}

void Colony::add_project(Project_ptr project)
{
  // TODO fix "unique" activity guarantee
  // assignment operator of activity?
  if (project != nullptr)
    this->projects[project->get_name()] = project;
}
