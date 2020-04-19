#pragma once
#include <list>
#include <utility>

#include "../types.hpp"
#include "description.hpp"
#include "../system/object.hpp"

class Planet : public SystemObject {

  private:

    unsigned long id;

    double diameter;
    double density_core, density_mantle, density_deep, density_surface, density_average;
    double pressure_low, pressure_high, pressure_average;
    double temp_low, temp_high, temp_average;

    // double humidity_low, humidity_high, humidity_average;
    // double water_coverage;

    std::list<std::pair<Element_ptr, double>> composition_surface;
    std::list<std::pair<Element_ptr, double>> composition_deep;
    std::list<std::pair<Element_ptr, double>> composition_mantle;
    std::list<std::pair<Element_ptr, double>> composition_core;

    PlanetDescriptionData description_data;

    System_ptr system;

  public:

    Planet(unsigned long id, double position, System_ptr system);
    ~Planet();

    static Planet_ptr generate(double position, System_ptr system);

    const PlanetDescriptionData &describe();

    double get_diameter() const;
    unsigned long get_id() const;
    System_ptr get_system() const;
};

