#pragma once

#include "activity.hpp"

class ConstructHabitat : public virtual Activity {

  private:

  public:
    ConstructHabitat(Colony &colony);
    ~ConstructHabitat();

    bool can_start() override;
    bool check() override;
};
