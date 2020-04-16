#pragma once

#include <memory>
#include <vector>

#include "../util/vec.hpp"

class Planet;
typedef std::shared_ptr<Planet> Planet_ptr;

class Star;
typedef std::shared_ptr<Star> Star_ptr;

class Colony;
typedef std::shared_ptr<Colony> Colony_ptr;

class System;
typedef std::shared_ptr<System> System_ptr;

class System {

  private:

    unsigned long id;

    double size;
    Vec3 position; // position within galaxy, in units of light years

    std::vector<Planet_ptr> planets;
    std::vector<Star_ptr> stars;

  public:

    System(Vec3 position, double size, unsigned long id);
    ~System();

    static System_ptr generate(Vec3 position);

    void introduce(Colony_ptr colony);

    Vec3 get_position() const;
    unsigned long get_id() const;

};
