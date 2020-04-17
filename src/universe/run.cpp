#include <unistd.h>

#include "universe.hpp"
#include "../util/time.hpp"

void Universe::run_events()
{
  this->running = true;
  
  unsigned long start = get_system_time();

  int i = 0;
  while (this->running) {

    unsigned long now = get_system_time();
    unsigned long dt = now - start;
    double dt_hours = double(dt) / 3600.0;
    double new_time = dt_hours;
    this->set_time(new_time);

    if (i % 10 == 0) {
      std::cerr << this->time << std::endl;
    }

    if (this->events.size()) {
      Event_ptr event = this->events.pop();
      event->execute(this->get_universe());
    }

    usleep(100*1000); i++;

  }

}

void Universe::stop()
{
  this->running = false;
}
