#pragma once

#include "../types.hpp"
#include "../system/object.hpp"

class Star : public SystemObject {

  private:

    ElementalAbundance composition;
    double density, diameter, temperature;

  public:

    Star(double position);
    ~Star();

    static Star_ptr generate();
};
