#include "../colony/colony.hpp"
#include "../item/item.hpp"
#include "produce_item.hpp"

ProduceItem::ProduceItem(Colony &colony, const ProjectData &data, Item_ptr item)
  :
    Project(colony, data, Formatter() << "production of " << item->get_name()),
    item(item)
{
  // do nothing
}

ProduceItem::~ProduceItem()
{
  // do nothing
}

ProjectStatus ProduceItem::update()
{

  if (this->status == PS_Active) {

    if (this->item->get_supplies(this->colony)) {
      static double previous_time = this->get_start_time();
      double time = Universe::get_time();
      double dt = time - previous_time;
      previous_time = time;

      if (this->item->construct(dt*this->data.get_number())) {
        this->colony.add_item(this->item);
        this->status = PS_Finished;
      }
    }

  }


  return this->status;
}
