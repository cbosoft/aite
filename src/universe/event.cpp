#include "universe.hpp"

void Universe::add_event(Event_ptr event)
{
  std::lock_guard<std::mutex> lock(this->events_mutex);
  this->events.push_back(event);
}
