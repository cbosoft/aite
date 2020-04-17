#pragma once
#include <string>
#include <memory>
#include <map>

#include "../types.hpp"


typedef struct PopulationStats {
  // rate of population growth (births per indiction, per population)
  double birth_rate;

  // rate of population decline (deaths per indiction, per population)
  double death_rate;

  // ability of population to resist disease, hardship. Also affects longevity
  double resilience;

  // having a diverse population increases successful births; affecting birth
  // rate and death rate. A non-diverse population propagates negative genetics
  // resulting in poor-longevity.
  double diversity;

  // number of people in the colony
  double number;

  // covers the general genetic "stock". High genetic_xp gives chance of
  // the population developing abilities that could help (or hinder) their
  // ability to survive on a harsh exoplanet
  double genetics_xp;
} PopulationStats;


typedef struct TechnologyStats {

  // rate at which envoys travel between (planets, systems, galaxies)
  double travel_speed; 

  // time envoys can spend in transit between destinations before perishing
  double transit_time_limit; 

  // how well research is conducted; how quickly new technologies are mastered
  double research_effectiveness;
  
  // ability to assimilate alien technologies
  double assimilation_ability;

  // range at which planets can be discovered
  double scouting_range;

  // range at which a satellite is within communication; if outside, then
  // communication will be disrupted and the sattelite may perish!
  double communication_range;

  // number of envoys able to be sent out at once
  int number_envoys;

  // size of skeleton crew able to hold a planet as "occupied". At least double
  // this size of population is required before sending an envoy.
  double skeleton_crew;

  // limits for surviving on an exoplanet
  double min_g; double max_g;
  double min_temperature; double max_temperature;
  double min_pressure; double max_pressure;

  // number of alien technologies amassed
  int alien_technologies;

  // level of experience in technological matters; more experience occasionally
  // gives benefits like new abilities
  double technology_xp;
} TechnologyStats;


typedef struct CultureStats {
  double religious_belief;
  double artistic_outputs;
  double domestic_peace;

  int cultural_finds;
  int archaeological_finds;

  double culture_xp;
} CultureStats;


class Colony {

  private:

    PopulationStats population_stats;
    TechnologyStats technology_stats;
    CultureStats culture_stats;

    // std::list<Abilities> // list of abilities the colony has acquired

    std::string name;
    std::string strategy;

    std::map<int, std::string> planet_log;

    std::string name_planet(const Planet_ptr planet) const;

  public:

    Colony(std::string name);
    ~Colony();

    void discover_planet(const Planet_ptr planet);
    std::string describe_planet(const Planet_ptr planet) const;
    void startoff(Planet_ptr planet);
    void update(double dt);

};
