#pragma once

#include <string>

#include "../resources/resources.hpp"
#include "../resources/resource_pool.hpp"

/*
 * An item is something that is made by a colony, and is perhaps a requirement
 * for a project. For example, to travel to another world, a space ship is
 * required.
 * */

class ConstructedItem {

  private:

    std::string name;
    bool in_use;
    double time_started;
    double time_required;
    Resources requirements;
    Resources status;

  public:

    ConstructedItem(std::string name, Resources requirements);

    void use();
    void release();
    bool is_in_use() const;
    double get_progress() const;

    bool build(PooledResource &pool);


};
