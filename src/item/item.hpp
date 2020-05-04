#pragma once

#include <string>

#include "../resources/processed_resources.hpp"
#include "../resources/resources.hpp"
#include "../resources/resource_pool.hpp"
#include "../types.hpp"

/*
 * An item is something that is made by a colony, and is perhaps a requirement
 * for a project. For example, to travel to another world, a space ship is
 * required.
 * */

class Item {

  private:

    std::string name;
    bool in_use;
    double effort_required; // effort as in "number of people * time"
    Resources requirements, status;
    ProcessedResources processed_requirements, status_processed;
    double effort;


  public:

    Item(std::string name, double effort_required, Resources requirements, ProcessedResources processed_requirements);

    std::string get_name() const;

    void use();
    void release();
    bool is_in_use() const;
    //double get_progress() const;

    bool get_supplies(Colony&);
    bool construct(double effort);

    static Item_ptr generate(std::string name);


};
