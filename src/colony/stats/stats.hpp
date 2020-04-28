#pragma once

#include "statistic.hpp"
#include "derived_statistic.hpp"

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
    std::map<std::string, double> derived_additive_modifiers;
    std::map<std::string, double> derived_multiplicative_modifiers;

    double apply_modifiers(double value, std::string statname) const;

  public:

    struct PopulationStats {
      Statistic number;
      Statistic medecine;
      Statistic mood;
      Statistic longevity;
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

    struct {
      DerivedStatistic_ptr growth_rate;
      DerivedStatistic_ptr required_habitable_volume;
      DerivedStatistic_ptr food_production_power_efficiency;
      DerivedStatistic_ptr food_production_efficiency;
      DerivedStatistic_ptr material_haervesting_power_efficiency;
      DerivedStatistic_ptr advanced_material_technique_progress;
      DerivedStatistic_ptr solar_generation_efficiency;
      DerivedStatistic_ptr nulear_power_minimum_activity;
      DerivedStatistic_ptr detection_distance;
      DerivedStatistic_ptr travel_speed;
      DerivedStatistic_ptr max_habitable_temperature;
      DerivedStatistic_ptr max_habitable_gravity;
    } derived_stats;


    ColonyStats();
    ~ColonyStats();
    void update(double dt);

    void add_additive_modifier(double value, std::string name);
    void add_multiplicative_modifier(double value, std::string name);

    double get_living_volume_requirement() const;
    void set_research_focus(ResearchFocus focus);
    ResearchFocus get_research_focus() const;
    void set_research_effort(double value);
    double get_research_effort() const;

    bool check_temperature_is_habitable(double temperature) const;
    bool check_gravity_is_habitable(double gravity) const;
    bool check_habitable(double temperature, double gravity) const;

};
