#pragma once

#include "project.hpp"

/*
 * Produce an item: the colony requires a big Thing, and devotes resources and
 * time to it. The project is in two stages, first the resources are gathered
 * and second the project is constructed. When the project is completed, the
 * newly constructed Thing will be added to the colony's inventory.
 *
 * The Thing can be anything: a spaceship, a building, a church, some really big
 * shoes, a rain jacket, a helicopter, a space station...
 *
 * */


class ProduceItem : public virtual Project {

  private:

    Item_ptr item;

  public:

    ProduceItem(Colony &colony, const ProjectData &data, Item_ptr item);
    ~ProduceItem();

    ProjectStatus update();

};
