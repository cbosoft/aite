#pragma once
#include <string>
#include <array>

#include "../resources/resources.hpp"
#include "../types.hpp"

#include "description.hpp"

enum SystemObjectType {
  SO_Planet, SO_EarthlikePlanet, SO_Moon, SO_Planetoid,
  SO_Star, SO_MainSequenceStar, SO_MassiveStar, SO_SupergiantStar, SO_Supernova, SO_NeutronStar, SO_BlackHole,
  SO_Nebula, SO_StellarNebula, SO_PlanetaryNebula,
  SO_AsteroidField
};

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
    double temperature;
    double pressure;
    double density;
    std::list<std::pair<Element_ptr, double>> composition;
    Resources resources;
    std::string colour;

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
    std::string get_colour() const;
    Resources *get_resources_rawptr();


    virtual SystemObjectType get_object_type() const=0;
    virtual std::string get_object_name() const=0;

    const ObjectDescriptionData &describe();

    bool try_inhabit(double population, Colony &colony);

};
