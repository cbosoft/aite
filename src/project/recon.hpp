#pragma once

#include "project.hpp"

/*
 * Reconnaissance is about looking far afield for new worlds/stars/systems and
 * so on
 *
 * */

class Recon : public virtual Project {

  private:

  public:

    Recon(Colony &colony, const ProjectData &data);
    ~Recon();

    bool check() override;
};
