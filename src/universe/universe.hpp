#pragma once
#include <memory>
#include <map>
#include <list>
#include <string>

#include "../util/safeq.hpp"
#include "../util/vec.hpp"
#include "../event/event.hpp"
#include "../types.hpp"



class Universe {

  private:

    double size;
    bool running;

    std::map<std::string, Colony_ptr> colonies;

    SafeQueue<Event> events;

    std::list<Galaxy_ptr> galaxies;

    double time; // "indiction" -> 15 earth years
    void set_time(double new_time);

  public:

    Universe();
    ~Universe();

    double get_time() const;

    static Universe_ptr get_universe();

    Colony_ptr add_colony(std::string name);
    Galaxy_ptr get_galaxy(Vec3 point);

    void run();
    void stop();

    void add_event(Event_ptr event);

};
