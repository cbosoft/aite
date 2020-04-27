#include <cmath>

#include "stats.hpp"

ColonyStats::ColonyStats()
  :
    population_stats({
        .number    = Statistic(0),
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
  // do nothing
}

ColonyStats::~ColonyStats()
{
  // do nothing
}

double ColonyStats::PopulationStats::get_growth() const
{

  // TODO

  return 0.2;
}

void ColonyStats::set_research_effort(double value)
{
  this->research_effort = value;
}

void ColonyStats::update(double dt)
{

  this->population_stats.number
    .multiply_base(1.0 + this->population_stats.get_growth()*dt);

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
  return temperature < this->get_max_habitable_temperature();
}


bool ColonyStats::check_gravity_is_habitable(double gravity) const
{
  return gravity < this->get_max_habitable_gravity();
}


double ColonyStats::get_max_habitable_gravity() const
{
  double base = this->technology_stats.astrogation;
  return std::pow(base, 0.33)*1.1 + 5.0;
}


double ColonyStats::get_max_habitable_temperature() const
{
  double base = this->technology_stats.astrogation;
  return (std::pow(base, 0.5) + 3.0)*100.0;
}
