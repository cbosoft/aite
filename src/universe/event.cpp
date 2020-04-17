#include "universe.hpp"

void Universe::add_event(Event_ptr event)
{
  this->events.push(event);
}
