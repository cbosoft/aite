#include <iostream>

#include "colony.hpp"
#include "../universe/universe.hpp"
#include "../planet/planet.hpp"
#include "../system/system.hpp"


Colony::Colony(std::string name, Planet_ptr planet, double time_of_inception)
{

  this->population_stats = {
    .growth_rate = 0.5,
    .resilience = 1.0,
    .diversity = 1.0,
    .mood = 0.0,
   
    .number = 100.0,
    .number_in_work = 0.0,
   
    .genetics_xp = 0.0,

    .inhabitable_volume = 0.0, // TODO check sensible defaults
    .food = 0.0
  };

  this->technology_stats = {
    .travel_speed = 0.1, // in light-year per indiction (fifteenths of light speed)
    .transit_time_limit = 3, // indictions (15 years)
    .research_effectiveness = 0.1,
    .assimilation_ability = 0.01,
    .scouting_range = 2e5,
    .communication_range = 2e5,
    .number_envoys = 0,
    .skeleton_crew = 100,
    .min_g = 0.1, .max_g = 5.0,
    .min_temperature = 250, .max_temperature = 360,
    .min_pressure = 0.5, .max_pressure = 1.5,
   
    .alien_technologies = 0,
   
    .technology_xp = 0.0,

    .energy = 0.0
  };

  this->culture_stats = {
    .religious_belief = 0.0,
    .artistic_output = 0.0,
    .domestic_peace = 95.0,

    .cultural_finds = 0,
    .archaeological_finds = 0,
    
    .culture_xp = 0.0
  };

  this->name = name;
  this->startoff(planet);
  this->time_of_inception = time_of_inception;
  this->universe = Universe::get_universe();
}


Colony::~Colony()
{
  // do nothing
}

double Colony::get_number()
{
  return this->population_stats.number;
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

void Colony::startoff(Planet_ptr planet)
{
  this->discover(planet);
  this->inhabited_planets.push_back(planet);
  if (not planet->try_inhabit(this->population_stats.number, *this)) {
    throw AuthorError(Formatter() << "Starting planet not inhabitable!");
  }

  auto system = planet->get_system();
  this->inhabited_systems.push_back(system);
  auto galaxy = system->get_galaxy();
  this->inhabited_galaxies.push_back(galaxy);
}

bool Colony::can_inhabit(const SystemObject &obj)
{
  const double p = obj.get_pressure();
  const double t = obj.get_temp();
  const double g = obj.get_gravity();

  bool pressure_ok = (p < this->technology_stats.max_pressure) && (p > this->technology_stats.min_pressure);
  bool temp_ok = (t < this->technology_stats.max_temperature) && (t > this->technology_stats.min_temperature);
  bool gravity_ok = (g < this->technology_stats.max_g) && (g > this->technology_stats.min_g);

  if (!pressure_ok) {
    std::cerr << "pressure " << p << std::endl;
  }
  if (!temp_ok) {
    std::cerr << "temperature " << t 
      << " " << this->technology_stats.min_temperature 
      << " " << this->technology_stats.max_temperature 
      << std::endl;
  }
  if (!gravity_ok) {
    std::cerr << "gravity " << g << std::endl;
  }

  return pressure_ok and temp_ok and gravity_ok;
}
