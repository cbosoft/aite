#include <iomanip>
#include <unistd.h>

#include "universe.hpp"
#include "../colony/colony.hpp"
#include "../util/time.hpp"

double get_hours_since_start(unsigned long start)
{
  unsigned long time_since_start_seconds = get_system_time() - start;
  double time_hours = double(time_since_start_seconds) / 3600.0;
  return time_hours;
}


// Called by the game server once, taking over the main thread. This thread
// manages the timestepping of the universe (incremental progress of the
// colonies) and manages events (not timestepped, but predetermined).
void Universe::run_events(int print_every)
{
  unsigned long start = get_system_time();
  double prev_time = 0.0;

  this->running = true;
  int seconds_ish = 0;
  while (this->running) {

    // Game time is calculated from real-world time: there is a 1:1 conversion
    // between hours in the real world, and centuries in Aite.
    double aite_new_time = get_hours_since_start(start);
    prev_time = this->_get_time();
    this->set_time(aite_new_time);
    double dt = this->_get_time() - prev_time;

    // output time to (server-side) user.
    if ( print_every and (seconds_ish / print_every)) {
      std::cerr << "t: " << this->_get_time() << "   dt: " << dt << std::endl;
      seconds_ish = 0;
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

    sleep(1);
    seconds_ish += 1;
  }

}

void Universe::stop()
{
  this->running = false;
}
