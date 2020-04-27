#include "stats.hpp"

ColonyStats::ColonyStats()
  :
    PopulationStats({
        .number    = Statistic(0),
        .medecine  = Statistic(0),
        .genetic_diversity = Statistic(0),
        .mood      = Statistic(0),
        .longevity = Statistic(75)
        }),
    TechnologyStats({
        .agriculture         = Statistic(0),
        .materials_gathering  = Statistic(0),
        .materials_processing = Statistic(0),
        .power_generation    = Statistic(0),
        .astrogation         = Statistic(0)
        }),
    CultureStats({
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
