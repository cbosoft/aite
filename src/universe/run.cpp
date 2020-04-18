#include <iomanip>
#include <unistd.h>

#include "universe.hpp"
#include "../colony/colony.hpp"
#include "../util/time.hpp"

void Universe::run_events()
{
  this->running = true;
  
  unsigned long start = get_system_time();

  int i = 0;
  while (this->running) {

    unsigned long now = get_system_time();
    unsigned long dt_seconds = now - start;
    double dt_hours = double(dt_seconds) / 3600.0;
    double new_time = dt_hours;
    double prev_time = this->time;
    this->set_time(new_time);
    double dt = this->time - prev_time;

    if (i % 30 == 0) {
      std::cerr << "t:" << std::scientific << this->time << " dt:" << dt << std::endl;
    }

    if (this->events.size()) {
      this->events.sort(EventCompareByTime());

      for (auto it = this->events.begin(); it != this->events.end(); it++) {
        Event_ptr event = (*it);
        if (event->get_time() < this->time) {
          event->execute(this->get_universe());
          this->events.erase(it++);
        }
        else {
          break;
        }
      }

    }
    
    for (auto kv : this->colonies) {
      auto colony = kv.second;
      colony->update(dt);
    }

    usleep(100*1000); i++;

  }

}

void Universe::stop()
{
  this->running = false;
}
