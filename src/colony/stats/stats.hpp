#pragma once
#include "statistic.hpp"

class ColonyStats {

  private:

    struct {
      Statistic number;
      Statistic medecine;
      Statistic genetic_diversity; // unsure
      Statistic mood;
      Statistic longevity;
    } PopulationStats;

    struct {
      Statistic agriculture;
      Statistic materials_gathering;
      Statistic materials_processing;
      Statistic power_generation;
      Statistic astrogation;
    } TechnologyStats;

    struct {
      Statistic religion;
      Statistic art;
      Statistic social;
      Statistic politics;
      //Statistic insert_name_here;
    } CultureStats;

  public:
    ColonyStats();
    ~ColonyStats();
    void update(double dt); // TODO growth?
};
