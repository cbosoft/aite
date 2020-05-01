#pragma once

#include "activity.hpp"

/*
 * Reconnaissance is about looking far afield for new worlds/stars/systems and
 * so on
 *
 * */

class Recon : public virtual Activity {

  private:

  public:

    Recon(Colony &colony, const ActivityConstructorData &acd);
    ~Recon();

    bool check() override;
};
