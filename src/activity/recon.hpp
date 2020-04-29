#pragma once

#include "activity.hpp"

/*
 * Reconnaissance is about looking far afield for new worlds/stars/systems and
 * so on
 *
 * */

class Recon : public virtual Activity {

  public:

    Recon(Colony &colony) : Activity(colony) {}
    ~Recon(){}

    static Activity_ptr create(Colony &colony)
    {
      return std::make_shared<Recon>(colony);
    }

    bool check() override;
};
