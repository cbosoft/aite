#pragma once

#include "activity.hpp"

class ConstructHabitat : public virtual Activity {

  private:

  public:
    ConstructHabitat(Colony &colony, const ActivityConstructorData &acd);
    ~ConstructHabitat();

    bool check() override;
};
