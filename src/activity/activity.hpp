#pragma once

#include "../types.hpp"
#include "../colony/colony.hpp"

class Activity {

  protected:

    Colony &colony;

  public:

    Activity(Colony &colony) : colony(colony) { }
    virtual ~Activity() { }

    virtual bool check() { return true; }

    static Activity_ptr from_string(std::string s, Colony &colony);
};
