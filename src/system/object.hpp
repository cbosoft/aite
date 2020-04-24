#pragma once
#include <string>
#include "../colony/colony.hpp"
#include "../types.hpp"

class SystemObject {

  protected:
    double position;

    std::string inhabiting_colony_name;
    double population;

    double gravitational_constant;
    double temp_average;
    double pressure_average;

  public:

    SystemObject(double position) 
      : 
        position(position), 
        population(0.0)
    {
    }

    double get_position() const { return this->position; }
    bool try_inhabit(double population, Colony &colony) {

      if (not colony.can_inhabit(*this)) {
        // cannot inhabit
        return false;
      }
      else {
        this->population = population;
        return true;
      }
    }

    double get_temp() const { return this->temp_average; }
    double get_pressure() const {return this->pressure_average; }
    double get_gravity() const {return this->gravitational_constant; }

};
