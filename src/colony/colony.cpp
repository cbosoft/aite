#include <iostream>

#include "../universe/universe.hpp"
#include "../object/object.hpp"
#include "../system/system.hpp"
#include "../project/project.hpp"
#include "../item/item.hpp"

#include "colony.hpp"

Colony::Colony()
  : time_of_inception(0.0), name("a colony")
{
}

Colony::Colony(std::string name, SystemObject_ptr planet, double time_of_inception)
  : time_of_inception(time_of_inception), name(name)
{

  // set up stats
  this->stats.population = {
      .number    = Statistic(100),
      .medecine  = Statistic(0),
      .longevity = Statistic(75)
  };

  this->stats.technology = {
    .research_effort      = Statistic(0),
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
  this->stats.derived.required_habitable_volume->set_use_total();

  this->stats.derived.travel_speed =
    std::make_shared<PowerDerivedStatistic>(&this->stats.technology.astrogation, 3.0, 1.0, 1.0);
  this->stats.derived.max_habitable_temperature =
    std::make_shared<PowerDerivedStatistic>(&this->stats.technology.astrogation, 0.5, 100.0, 373.0);
  this->stats.derived.max_habitable_gravity =
    std::make_shared<PowerDerivedStatistic>(&this->stats.technology.astrogation, 0.33, 1.1, 5.0);

  DerivedStatistic_ptr cramped = std::make_shared<LessThanDerivedStatistic>(
        this->stats.derived.required_habitable_volume,
        std::make_shared<DerivedResource<Resource>>(&this->processed_resources.habitable_volume),
        0.0, -10.0
      );
  this->stats.derived.mood = std::make_shared<SumDerivedStatistic>(std::list<DerivedStatistic_ptr>({cramped}));


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
  std::string name = project->get_name();

  ProjectData orig = {0};
  bool updating = false;
  {
    auto it = this->projects.find(name);

    if (it != this->projects.end()) {
      orig = it->second->get_data();

      if (project->get_data() == orig) {
        this->add_message(Formatter() << BOLD << "Project \"" << name << "\" parameters unchanged." << RESET);
        return;
      }

      updating = true;
      this->projects.erase(it);
    }
  }


  if (project->check_can_start()) {

    this->projects[name] = project;
    project->start();

    if (updating) {
      this->add_message(Formatter() << BOLD << "Updated project \"" << name << "\" parameters." << RESET);
    }
    else {
      this->add_message(Formatter() << BOLD << "Started project \"" << name << "\"." << RESET);
    }

  }
  else {

    if (updating) {
      this->add_message(Formatter() << BOLD << "Cannot change project \"" << name << "\" parameters: " << RESET << project->get_error());
      this->projects[name] = project;
      this->projects[name]->set_data(orig);
    }
    else {
      this->add_message(Formatter() << BOLD << "Cannot start project \"" << name << "\": " << RESET << project->get_error());
    }

  }

}


void Colony::add_item(Item_ptr item)
{
  this->inventory.push_back(item);

  auto it = this->items_not_in_use.find(item->get_name());
  if (it == this->items_not_in_use.end()) {
    this->items_not_in_use[item->get_name()] = 1;
  }
  else {
    this->items_not_in_use[item->get_name()] ++;
  }

}

void Colony::use_item(std::string name)
{

  if (!this->items_not_in_use[name]) {
    throw ItemInUseError("Item not available!");
  }

  for (auto item : this->inventory) {
    if ((item->get_name().compare(name) == 0) and not item->is_in_use()) {
      item->use();
      this->items_not_in_use[name] --;
    }
  }

  // shouldnt get here
  throw AuthorError("item not available but notinuse check did not catch it");
}

void Colony::use_item(Item_ptr item)
{

  if (!this->items_not_in_use[item->get_name()]) {
    throw ItemInUseError("Item not available!");
  }
  
  item->use();

  this->items_not_in_use[item->get_name()] --;

}

bool Colony::has_free_item(std::string name) const
{
  auto it = this->items_not_in_use.find(name);
  return (it != this->items_not_in_use.end());
}
