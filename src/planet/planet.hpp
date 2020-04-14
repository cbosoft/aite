#pragma once
#include <list>
#include <utility>
#include <memory>

class Element;
class Planet {

  private:

    double diameter;
    double density_core, density_mantle, density_deep, density_surface, density_average;
    double pressure_low, pressure_high, pressure_average;
    double temp_low, temp_high, temp_average;

    // double humidity_low, humidity_high, humidity_average;
    // double water_coverage;

    std::list<std::pair<std::shared_ptr<Element>, double>> surface_makeup;
    std::list<std::pair<std::shared_ptr<Element>, double>> deep_makeup;
    std::list<std::pair<std::shared_ptr<Element>, double>> mantle_makeup;
    std::list<std::pair<std::shared_ptr<Element>, double>> core_makeup;

  public:

    Planet();
    ~Planet();

    static std::shared_ptr<Planet> generate();

    std::string describe() const;

    double get_diameter() const;
};
