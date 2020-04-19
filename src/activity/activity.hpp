#pragma once

#include "../types.hpp"
#include "../colony/colony.hpp"

class Activity {

  private:

    Colony &colony;

  public:

    Activity(Colony &colony) : colony(colony) {}
    virtual ~Activity() {}

    virtual void update() =0;

    static Activity_ptr from_string(std::string s);
};
