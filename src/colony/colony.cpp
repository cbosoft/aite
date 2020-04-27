#include <iostream>

#include "colony.hpp"
#include "../universe/universe.hpp"
#include "../object/object.hpp"
#include "../system/system.hpp"


Colony::Colony(std::string name, SystemObject_ptr planet, double time_of_inception)
  : time_of_inception(time_of_inception), name(name)
{
  this->startoff(planet);
  this->universe = Universe::get_universe();
}


Colony::~Colony()
{
  // do nothing
}

double Colony::get_number()
{
  return this->stats.population_stats.number;
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
  if (not planet->try_inhabit(this->stats.population_stats.number, *this)) {
    throw AuthorError(Formatter() << "Starting planet not inhabitable!");
  }
  this->inhabited_objects.push_back(planet);

  auto system = planet->get_system();
  this->inhabited_systems.push_back(system);
  auto galaxy = system->get_galaxy();
  this->inhabited_galaxies.push_back(galaxy);
}

bool Colony::can_inhabit(const SystemObject &obj)
{
  const double p = obj.get_pressure();
  const double t = obj.get_temperature();
  const double g = obj.get_gravity();

  bool pressure_ok = this->stats.check_pressure_is_habitable(obj.get_pressure());
  bool temp_ok = this->stats.check_temperature_is_habitable(obj.get_temperature());
  bool gravity_ok = this->stats.check_gravity_is_habitable(obj.get_gravity());

  if (!pressure_ok) {
    std::cerr << "pressure " << p << std::endl;
  }
  if (!temp_ok) {
    std::cerr << "temperature " << t << std::endl;
  }
  if (!gravity_ok) {
    std::cerr << "gravity " << g << std::endl;
  }

  return pressure_ok and temp_ok and gravity_ok;
}
