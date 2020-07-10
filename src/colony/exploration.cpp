#include "colony.hpp"
#include "../system/system.hpp"
#include "../util/random.hpp"

bool Colony::ready_to_expand() const
{
  return this->resources.volume < 1e3;
}

void Colony::explore()
{
  std::vector<SystemObject_ptr> next_options;

  // any available objects?
  for (const auto& sys : this->inhabited_systems) {
    auto uninhabited_objects = this->get_uninhabited(sys);
    for (const auto& obj : uninhabited_objects) {
      next_options.push_back(obj);
    }
  }

  // nearby systems?
  // TODO

  if (next_options.size()) {
    auto obj = *select_randomly(next_options.begin(), next_options.end());
    this->inhabit(obj);
  }
  
}


std::list<SystemObject_ptr> Colony::get_uninhabited(System_ptr system) const
{
  std::list<SystemObject_ptr> uninhabited_objects;

  for (const auto& obj : system->get_objects()) {
    bool inhabited = false;
    for (const auto& inobj : this->inhabited_objects) {
      if (obj == inobj) {
        inhabited = true;
        break;
      }
    }

    if (not inhabited) {
      uninhabited_objects.push_back(obj);
    }
  }

  return uninhabited_objects;
}
