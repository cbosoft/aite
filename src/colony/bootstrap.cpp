#include <iostream>

#include "colony.hpp"
#include "bootstrap.hpp"


BootstrapColonyEvent::BootstrapColonyEvent(Colony &colony) : colony(colony)
{
  this->exec_time = this->colony.get_inception_time() + 0.1;
}


BootstrapColonyEvent::~BootstrapColonyEvent()
{
  // 
}


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

  std::cerr << "bootstrap!" << std::endl;
  this->colony.add_message("bootstrap!");
}


double BootstrapColonyEvent::get_time()
{
  return this->exec_time;
}
