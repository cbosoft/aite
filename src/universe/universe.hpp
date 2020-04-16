#pragma once
#include <memory>
#include <map>
#include <list>
#include <string>

#include "../util/vec.hpp"

class Event;
typedef std::shared_ptr<Event> Event_ptr;


class Colony;
typedef std::shared_ptr<Colony> Colony_ptr;


class Galaxy;
typedef std::shared_ptr<Galaxy> Galaxy_ptr;


class System;
typedef std::shared_ptr<System> System_ptr;


class Universe;
typedef std::shared_ptr<Universe> Universe_ptr;


class Universe {

  private:

    double size;

    std::map<std::string, Colony_ptr> colonies;

    std::list<Event_ptr> events;
    std::list<Galaxy_ptr> galaxies;

    double time;

  public:

    Universe();
    ~Universe();

    double get_time() const;

    static Universe_ptr get_universe();

    Colony_ptr add_colony(std::string name);
    Galaxy_ptr get_galaxy(Vec3 point);

};
