#include <iostream>

#include "colony.hpp"


Colony::Colony(std::string name, Planet_ptr planet, double time_of_inception)
{
  this->name = name;
  this->discover_planet(planet);
  this->inhabited_planet.push_back(planet);
  this->time_of_inception = time_of_inception;

  this->population_stats = {
    .birth_rate = 0.5,
    .death_rate = 0.2,
    .resilience = 1.0,
    .diversity = 1.0,
   
    .number = 100.0,
   
    .genetics_xp = 0.0
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
   
    .technology_xp = 0.0
  };

  this->culture_stats = {
    .religious_belief = 0.0,
    .artistic_output = 0.0,
    .domestic_peace = 95.0,

    .cultural_finds = 0,
    .archaeological_finds = 0,
    
    .culture_xp = 0.0
  };

}


Colony::~Colony()
{
  // do nothing
}

double Colony::get_number()
{
  return this->population_stats.number;
}
