#pragma once

#include <iostream>

#include "../universe/universe.hpp"
#include "project.hpp"

class BabyBoom : public virtual Project {

  private:

    double end_time;

  public:

    BabyBoom(Colony &colony, const ProjectData &data)
      : Project(colony, data, "baby boom")
    {
      double time = Universe::get_universe()->get_time();
      this->end_time = time + 2;
      this->colony.stats.derived.growth_rate->set_additive_modifier("baby boom", 2.0);
    }

    ~BabyBoom()
    {
      this->colony.stats.derived.growth_rate->remove_additive_modifier("baby boom");
    }

    bool check() override
    {
      double time = Universe::get_universe()->get_time();
      return time < this->end_time;
    }

};
