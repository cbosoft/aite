#pragma once

#include <iostream>

#include "../universe/universe.hpp"
#include "../colony/colony.hpp"
#include "project.hpp"

class BabyBoom : public virtual Project {

  private:

    double end_time;

  public:

    BabyBoom(Colony &colony, const ProjectData &data)
      : Project(colony, data, "baby boom")
    {
      this->colony.stats.derived.growth_rate->set_additive_modifier("baby boom", 2.0);
    }

    ~BabyBoom()
    {
      this->colony.stats.derived.growth_rate->remove_additive_modifier("baby boom");
    }

    ProjectStatus update() override
    {
      return PS_Active;
    }

};
