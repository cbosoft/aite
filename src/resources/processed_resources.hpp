#pragma once

#include "resource.hpp"

class ProcessedResources {

  public:

    Resource food;
    Resource metal;
    Resource heavy_metal;
    Resource ceramics;
    Resource nuclear_fuel;
    Resource habitable_volume;
    Resource power;
    Resource solar_collection_area;

    ProcessedResources();
    ProcessedResources(double food, double metal, double heavy_metal,
        double ceramics, double nuclear_fuel, double habitable_volume,
        double power, double solar_collection_area);

};
