#pragma once

#include "derived_statistic.hpp"
#include "statistic.hpp"

enum ResearchFocus {
  // split equally
  RF_Equal,

  // split between relevant stats
  RF_Food, RF_Resource, RF_Exploration,

  // specific stat
  RF_Agriculture, RF_MaterialsGathering, RF_MaterialsProcessing, RF_Power, RF_Astrogation
};

class ColonyStats {

  private:

    unsigned int number_adv_techniques;

  public:

    struct PopulationStats {
      Statistic number;
      Statistic medecine;
      Statistic mood;
      Statistic longevity;

      double get_growth() const;

    } population_stats;

    double research_effort;
    ResearchFocus research_focus;
    struct {
      Statistic agriculture;
      Statistic materials_gathering;
      Statistic materials_processing;
      Statistic power_generation;
      Statistic astrogation;
    } technology_stats;

    struct {
      Statistic religion;
      Statistic art;
      Statistic social;
      Statistic politics;
    } culture_stats;


    ColonyStats();
    ~ColonyStats();
    void update(double dt);

    double get_living_volume_requirement() const;
    void set_research_focus(ResearchFocus focus);
    ResearchFocus get_research_Focus() const;
    void set_research_effort(double value);

    // derived stats
    double get_food_production_power_efficiency() const;
    double get_food_production_efficiency() const;
    double get_material_harvesting_power_efficiency() const;
    double get_material_recovery_rate() const;
    double get_advance_material_technique_progress() const;
    double solar_generation_efficiency() const;
    double nuclear_power_minimum_activity() const;
    double get_detection_distance() const;
    double get_travel_speed() const;

    bool check_temperature_is_habitable(double temperature) const;
    bool check_gravity_is_habitable(double gravity) const;

    double get_max_habitable_temperature() const;
    double get_max_habitable_gravity() const;

};
