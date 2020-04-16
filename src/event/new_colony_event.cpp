#include "new_colony_event.hpp"
#include "../universe/universe.hpp"


NewColonyEvent::NewColonyEvent()
{
  // do nothing
}


NewColonyEvent::~NewColonyEvent()
{
  // do nothing
}


NewColonyEvent_ptr NewColonyEvent::create(std::string name)
{
  NewColonyEvent_ptr event = std::make_shared<NewColonyEvent>();

  event->name = name;

  return event;
}


void NewColonyEvent::execute(Universe_ptr universe)
{
  universe->add_colony(this->name);
}
