#pragma once

#include "../types.hpp"
#include "resource.hpp"

class Resources {

  public:

    Resource OCHNPS;
    Resource metallic_ore;
    Resource nonmetallic_ore;
    Resource high_density_ore;
    Resource high_activity_ore;
    Resource luminosity;
    Resource volume;

    Resources();
    Resources(double OCHNPS, double metallic_ore, double nonmetallic_ore,
        double high_density_ore, double high_activity_ore, double luminosity,
        double volume);
    Resources(ElementalAbundance elements, double mass);

};
