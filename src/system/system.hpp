#pragma once

#include <vector>

#include "../util/vec.hpp"
#include "../types.hpp"

class System {

  private:

    static const int max_number_stars = 5;

    unsigned long id;

    double size;
    Vec3 position; // position within galaxy, in units of light years

    std::vector<SystemObject_ptr> objects;

    Galaxy_ptr galaxy;

  public:

    System(Vec3 position, double size, unsigned long id, Galaxy_ptr galaxy);
    ~System();

    static System_ptr generate(Vec3 position, Galaxy_ptr galaxy);
    static System_ptr generate_inhabitable(Vec3 position, Galaxy_ptr galaxy, SystemObject_ptr &object);

    SystemObject_ptr get_random_object();

    const std::vector<SystemObject_ptr> &get_objects() const;
    Vec3 get_position() const;
    unsigned long get_id() const;
    unsigned int get_object_index(SystemObject_ptr object) const;
    Galaxy_ptr get_galaxy() const;


};
