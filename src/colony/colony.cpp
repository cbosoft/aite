#include <iostream>

#include "../universe/universe.hpp"
#include "../object/object.hpp"
#include "../system/system.hpp"
#include "../item/item.hpp"

#include "colony.hpp"

Colony::Colony()
  : time_of_inception(0.0), name("a colony")
{
}

Colony::Colony(std::string name, SystemObject_ptr planet, double time_of_inception)
  :
   time_of_inception(time_of_inception),
   name(name),
   number(100),
   growth_rate(0.2)
{
  this->inhabit(planet);
}


Colony::~Colony()
{
  // do nothing
}


double Colony::get_inception_time()
{
  return this->time_of_inception;
}


void Colony::add_message(std::string message)
{
  std::lock_guard<std::mutex> lock(this->messages_mutex);
  this->messages.push_back(message);
}


std::list<std::string> Colony::get_messages()
{
  std::lock_guard<std::mutex> lock(this->messages_mutex);
  std::list<std::string> rv(this->messages);
  this->messages.erase(this->messages.begin(), this->messages.end());
  return rv;
}


bool Colony::inhabit(SystemObject_ptr object)
{
  // TODO check if object is already inhabited
  this->discover(object);
  this->inhabited_objects.push_back(object);

  auto system = object->get_system();
  this->inhabited_systems.push_back(system);
  auto galaxy = system->get_galaxy();
  this->inhabited_galaxies.push_back(galaxy);
  this->resources.add_source(object->get_resources_rawptr());
  return true;
}


void Colony::add_item(Item_ptr item)
{
  this->inventory.push_back(item);

  auto it = this->items_not_in_use.find(item->get_name());
  if (it == this->items_not_in_use.end()) {
    this->items_not_in_use[item->get_name()] = 1;
  }
  else {
    this->items_not_in_use[item->get_name()] ++;
  }

}

void Colony::use_item(std::string name)
{

  if (!this->items_not_in_use[name]) {
    throw ItemInUseError("Item not available!");
  }

  for (auto item : this->inventory) {
    if ((item->get_name().compare(name) == 0) and not item->is_in_use()) {
      item->use();
      this->items_not_in_use[name] --;
    }
  }

  // shouldnt get here
  throw AuthorError("item not available but notinuse check did not catch it");
}

void Colony::use_item(Item_ptr item)
{

  if (!this->items_not_in_use[item->get_name()]) {
    throw ItemInUseError("Item not available!");
  }
  
  item->use();

  this->items_not_in_use[item->get_name()] --;

}

bool Colony::has_free_item(std::string name) const
{
  auto it = this->items_not_in_use.find(name);
  return (it != this->items_not_in_use.end());
}

const std::string &Colony::get_name() const
{
  return this->name;
}

double Colony::get_number() const
{
  return this->number;
}


double Colony::get_required_volume() const
{
  return this->number*100;
}
