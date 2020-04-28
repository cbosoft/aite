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
    Resource luminance;
    Resource volume;

    Resources();
    Resources(ElementalAbundance elements, double mass);

};
