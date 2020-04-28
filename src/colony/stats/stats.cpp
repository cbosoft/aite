#include <cmath>
#include <iostream>

#include "stats.hpp"

ColonyStats::ColonyStats()
  :
    population_stats({
        .number    = Statistic(100),
        .medecine  = Statistic(0),
        .mood      = Statistic(0),
        .longevity = Statistic(75)
        }),
    research_effort(0.0),
    technology_stats({
        .agriculture          = Statistic(0),
        .materials_gathering  = Statistic(0),
        .materials_processing = Statistic(0),
        .power_generation     = Statistic(0),
        .astrogation          = Statistic(0)
        }),
    culture_stats({
        .religion = Statistic(0),
        .art      = Statistic(0),
        .social   = Statistic(0),
        .politics = Statistic(50),
        })
{
  // set up derived stats
  this->derived_stats.growth_rate =
    std::make_shared<LinearDerivedStatistic>(&this->population_stats.number, 0.0, 0.2);
  this->derived_stats.required_habitable_volume =
    std::make_shared<LinearDerivedStatistic>(&this->population_stats.number, 80.0, 0.0); // roughly 80m3 per person

  this->derived_stats.travel_speed =
    std::make_shared<PowerDerivedStatistic>(&this->technology_stats.astrogation, 3.0, 1.0, 1.0);
  this->derived_stats.max_habitable_temperature =
    std::make_shared<PowerDerivedStatistic>(&this->technology_stats.astrogation, 0.5, 100.0, 373.0);
  this->derived_stats.max_habitable_gravity =
    std::make_shared<PowerDerivedStatistic>(&this->technology_stats.astrogation, 0.33, 1.1, 5.0);
}

ColonyStats::~ColonyStats()
{
  // do nothing
}

void ColonyStats::set_research_effort(double value)
{
  this->research_effort = value;
}

double ColonyStats::get_research_effort() const
{
  return this->research_effort;
}

void ColonyStats::update(double dt)
{

  this->population_stats.number
    .multiply_base(1.0 + this->derived_stats.growth_rate->get_value()*dt);

  if (this->research_effort == 0.0)
    return;

  double research_each = this->research_effort;
  switch (this->research_focus) {

    case RF_Equal:
      research_each /= 5.0;
      this->technology_stats.agriculture.increase_base(research_each);
      this->technology_stats.materials_gathering.increase_base(research_each);
      this->technology_stats.materials_processing.increase_base(research_each);
      this->technology_stats.power_generation.increase_base(research_each);
      this->technology_stats.astrogation.increase_base(research_each);
      break;

    case RF_Agriculture:
    case RF_Food:
      this->technology_stats.agriculture.increase_base(research_each);
      break;

    case RF_Resource:
      research_each /= 3.0;
      this->technology_stats.materials_gathering.increase_base(research_each);
      this->technology_stats.materials_processing.increase_base(research_each);
      this->technology_stats.power_generation.increase_base(research_each);
      break;

    case RF_Astrogation:
    case RF_Exploration:
      this->technology_stats.astrogation.increase_base(research_each);
      break;

    case RF_MaterialsGathering:
      this->technology_stats.materials_gathering.increase_base(research_each);
      break;

    case RF_MaterialsProcessing:
      this->technology_stats.materials_processing.increase_base(research_each);
      break;

    case RF_Power:
      this->technology_stats.power_generation.increase_base(research_each);
      break;
  }
}


bool ColonyStats::check_temperature_is_habitable(double temperature) const
{
  return temperature < this->derived_stats.max_habitable_temperature->get_value();
}


bool ColonyStats::check_gravity_is_habitable(double gravity) const
{
  return gravity < this->derived_stats.max_habitable_gravity->get_value();
}

bool ColonyStats::check_habitable(double temperature, double gravity) const
{
  return this->check_temperature_is_habitable(temperature) && this->check_gravity_is_habitable(gravity);
}

double ColonyStats::apply_modifiers(double value, std::string statname) const
{
  double rv = value;
  {
    auto it = this->derived_additive_modifiers.find(statname);
    if (it != this->derived_additive_modifiers.end()) {
      rv += it->second;
    }
  }

  {
    auto it = this->derived_multiplicative_modifiers.find(statname);
    if (it != this->derived_multiplicative_modifiers.end()) {
      rv *= it->second;
    }
  }

  return rv;
}

void ColonyStats::add_multiplicative_modifier(double value, std::string statname)
{
  if (this->derived_multiplicative_modifiers.find(statname) == this->derived_multiplicative_modifiers.end()) {
    this->derived_multiplicative_modifiers[statname] = value;
  }
  else {
    this->derived_multiplicative_modifiers[statname] = this->derived_multiplicative_modifiers[statname] + value;
  }
}

void ColonyStats::add_additive_modifier(double value, std::string statname)
{
  if (this->derived_additive_modifiers.find(statname) == this->derived_additive_modifiers.end()) {
    this->derived_additive_modifiers[statname] = value;
  }
  else {
    this->derived_additive_modifiers[statname] = this->derived_additive_modifiers[statname] + value;
  }
}
