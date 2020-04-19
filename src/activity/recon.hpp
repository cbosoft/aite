#pragma once

#include "activity.hpp"

class Recon : public virtual Activity {

  public:

    Recon(Colony &colony) : Activity(colony) {}
    ~Recon(){}

    static Activity_ptr create(Colony &colony)
    {
      return std::make_shared<Recon>(colony);
    }

    void update();
};
