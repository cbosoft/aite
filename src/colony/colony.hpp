#pragma once
#include <string>
#include <memory>
#include <map>
#include <list>
#include <mutex>

#include "../types.hpp"
#include "stats/stats.hpp"


class Colony {

  private:

    ColonyStats stats;
    Universe_ptr universe;

    // std::list<Abilities> abilites; // list of abilities the colony has acquired

    std::mutex messages_mutex;
    std::list<std::string> messages;

    double time_of_inception;
    std::string name;
    std::string strategy;

    std::map<int, std::string> object_log;
    std::map<int, std::string> system_log;
    std::map<int, std::string> galaxy_log;
    std::string get_name(const SystemObject_ptr planet);
    std::string get_name(const System_ptr system);
    std::string get_name(const Galaxy_ptr galaxy);
    std::list<SystemObject_ptr> inhabited_objects;
    std::list<System_ptr> inhabited_systems;
    std::list<Galaxy_ptr> inhabited_galaxies;

    double get_inhabited_volume() const;

  public:

    Colony(std::string name, SystemObject_ptr starting_world, double time_of_inception);
    ~Colony();

    void discover(const SystemObject_ptr object);
    void discover(const System_ptr system);
    void discover(const Galaxy_ptr galaxy);

    std::string describe(const SystemObject_ptr object);
    std::string describe(const System_ptr system);
    std::string describe(const Galaxy_ptr galaxy);

    bool have_discovered(const SystemObject_ptr object) const;
    bool have_discovered(const System_ptr system) const;
    bool have_discovered(const Galaxy_ptr galaxy) const;

    void startoff(SystemObject_ptr planet);
    void update(double dt);

    void add_message(std::string message);
    std::list<std::string> get_messages();

    Event_ptr get_bootstrap_event();
    double get_number();
    double get_inception_time();

    bool can_inhabit(const SystemObject &object);

};
