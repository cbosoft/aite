#pragma once

#include "../types.hpp"
#include "../colony/colony.hpp"
#include "../universe/universe.hpp"

class Activity {

  private:

    double start_time;

  protected:

    Colony &colony;

  public:

    Activity(Colony &colony) 
      : start_time(Universe::get_universe()->get_time()), colony(colony)
    {
    }
    virtual ~Activity()
    {
    }

    virtual bool can_start() { return true; }
    virtual bool check() { return true; }

    double get_start_time() const
    {
      return this->start_time;
    }

    double get_elapsed_time() const
    {
      return Universe::get_universe()->get_time() - this->start_time;
    }

    static Activity_ptr from_string(std::string s, Colony &colony);
};
