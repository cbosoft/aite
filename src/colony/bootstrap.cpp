#include <iostream>

#include "colony.hpp"
#include "bootstrap.hpp"


BootstrapColonyEvent_ptr BootstrapColonyEvent::create(Colony &colony)
{
  return std::make_shared<BootstrapColonyEvent>(colony);
}


Event_ptr Colony::get_bootstrap_event()
{
  return BootstrapColonyEvent::create(*this);
}


void BootstrapColonyEvent::execute(Universe_ptr universe)
{
  (void) universe;
  // TODO
}
