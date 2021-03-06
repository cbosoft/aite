#pragma once

#include <list>
#include <memory>

#include "../util/vec.hpp"
#include "../types.hpp"


class Galaxy {

  private:

    unsigned long id;

    double size; // light years

    Vec3 position; // position of this galaxy within the universe, units of light years

    std::list<System_ptr> systems;

    Universe_ptr universe;

  public:

    Galaxy(Vec3 position, double size, unsigned long id);
    ~Galaxy();

    static Galaxy_ptr generate(Vec3 position);

    System_ptr new_system();
    System_ptr new_inhabitable_system(SystemObject_ptr &object);

    Vec3 get_position() const;
    unsigned long get_id() const;

};
