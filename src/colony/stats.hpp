#pragma once


typedef struct PopulationStats {
  // rate of population growth (births per indiction, per person less deaths
  // per indiction per person)
  double growth_rate;

  // ability of population to resist disease, hardship. Also affects longevity
  double resilience;

  // having a diverse population increases successful births; affecting birth
  // rate and death rate. A non-diverse population propagates negative genetics
  // resulting in poor-longevity.
  double diversity;

  // mood: how happy are the people? This slightly affects growth rate
  double mood;

  // number of people in the colony
  double number;

  // covers the general genetic "stock". High genetic_xp gives chance of
  // the population developing abilities that could help (or hinder) their
  // ability to survive on a harsh exoplanet
  double genetics_xp;

  // The last few stats are not so much ability scores so much as "requirements"
  // of the colony. These are things that the colony needs in order to continue
  // to continue to develop and grow. If the required resources are in short
  // supply, then growth and mood will reduce, and xp will grow slower, perhaps
  // stop.

  // people need space! A lack of space and growth becomes difficult.
  double inhabitable_volume;

  // people need food! Most food is recycled, but there are losses that need to
  // be toppped up. A supply of carbon, phosphorous, nitrogen, and potassium are 
  // required to keep food in plenty supply.
  double food;

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

  // requirements

  // Energy is needed to do SCIENCE! This can be in the form of solar, nuclear,
  // or combustion power. Note: nuclear and solar provide the most bang for
  // buck (efficient... long lasting.. etc)
  double energy;
} TechnologyStats;


typedef struct CultureStats {
  double religious_belief;
  double artistic_output;
  double domestic_peace;

  int cultural_finds;
  int archaeological_finds;

  double culture_xp;
} CultureStats;
