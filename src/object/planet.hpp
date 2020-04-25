#pragma once
#include <string>

#include "../types.hpp"
#include "../object/object.hpp"


class Planet : public SystemObject {

  public:

    Planet(System_ptr system, double position) : SystemObject(system, position) {};
    ~Planet() {};

    std::string get_object_name() override { return "planet"; }

    static SystemObject_ptr generate(System_ptr system, double position);

};


class EarthlikePlanet : public SystemObject {

  public:

    EarthlikePlanet(System_ptr system, double position) : SystemObject(system, position) {};
    ~EarthlikePlanet() {};

    std::string get_object_name() override { return "planet"; }

    static SystemObject_ptr generate(System_ptr system, double position);

};
