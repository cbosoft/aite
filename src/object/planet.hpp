#pragma once
#include <string>

#include "../types.hpp"
#include "object.hpp"


class Planet : public SystemObject {

  public:

    Planet(System_ptr system, double position) : SystemObject(system, position) {};
    ~Planet() {};

    SystemObjectType get_object_type() const override { return SO_Planet; }
    std::string get_object_name() const override { return "planet"; }

    static SystemObject_ptr generate(System_ptr system, double position);

};


class EarthlikePlanet : public SystemObject {

  public:

    EarthlikePlanet(System_ptr system, double position) : SystemObject(system, position) {};
    ~EarthlikePlanet() {};

    SystemObjectType get_object_type() const override { return SO_Planet; }
    std::string get_object_name() const override { return "planet"; }

    static SystemObject_ptr generate(System_ptr system, double position);

};
