#pragma once

#include "project.hpp"

class ConstructHabitat : public virtual Project {

  private:
    double volume_left;

  public:
    ConstructHabitat(Colony &colony, const ProjectData &data);
    ~ConstructHabitat();

    ProjectStatus get_status() override;
    void do_work() override;
};
