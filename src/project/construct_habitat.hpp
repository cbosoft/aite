#pragma once

#include "project.hpp"

class ConstructHabitat : public virtual Project {

  private:

  public:
    ConstructHabitat(Colony &colony, const ProjectData &data);
    ~ConstructHabitat();

    ProjectStatus update() override;
};
