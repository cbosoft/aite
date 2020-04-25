#pragma once
#include <string>
#include <array>

#include "../colony/colony.hpp"
#include "../types.hpp"

#include "description.hpp"

enum SystemObjectType {SO_Planet, SO_EarthlikePlanet, SO_Star, SO_Nebula /*TODO: the rest...*/ };

class SystemObject {

  protected:
    const unsigned long id;
    System_ptr system;

    double position,
           // for collections of objects the size of the object will be much
           // smaller than the territory size
           territory_diameter,
           object_diameter;

    std::string inhabiting_colony_name;
    double population;

    double gravitational_constant;
    std::array<double, 3> temperature; // low, high, average
    std::array<double, 3> pressure;
    std::array<double, 4> density; // deep, shallow, near-surface, average
    std::array<std::list<std::pair<Element_ptr, double>>, 3> composition; // deep, shallow, near-surface

    ObjectDescriptionData description_data;

  public:

    SystemObject(System_ptr system, double position);

    static SystemObject_ptr generate(System_ptr system, double position, SystemObjectType type);

    double get_position() const;
    double get_temperature() const;
    double get_pressure() const;
    double get_gravity() const;
    unsigned long get_id() const;
    System_ptr get_system() const;

    virtual std::string get_object_name() =0;
    const ObjectDescriptionData &describe();

    bool try_inhabit(double population, Colony &colony);

};
