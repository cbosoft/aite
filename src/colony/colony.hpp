#pragma once
#include <string>
#include <memory>
#include <map>
#include <list>
#include <mutex>

#include "../types.hpp"
#include "stats.hpp"


class Colony {

  private:

    // TODO overhaul stats; they're a bit of a mish-mash rn
    PopulationStats population_stats;
    TechnologyStats technology_stats;
    CultureStats culture_stats;

    Universe_ptr universe;

    // std::list<Abilities> abilites; // list of abilities the colony has acquired

    std::mutex messages_mutex;
    std::list<std::string> messages;

    double time_of_inception;
    std::string name;
    std::string strategy;

    std::map<int, std::string> planet_log;
    std::map<int, std::string> system_log;
    std::map<int, std::string> galaxy_log;
    std::string get_name(const Planet_ptr planet);
    std::string get_name(const System_ptr planet);
    std::string get_name(const Galaxy_ptr planet);
    std::list<Planet_ptr> inhabited_planets;
    std::list<System_ptr> inhabited_systems;
    std::list<Galaxy_ptr> inhabited_galaxies;


  public:

    Colony(std::string name, Planet_ptr starting_world, double time_of_inception);
    ~Colony();

    // TODO add moons, stars, nebula, asteroid fields
    void discover(const Planet_ptr planet);
    void discover(const System_ptr system);
    void discover(const Galaxy_ptr galaxy);

    std::string describe(const Planet_ptr planet);
    std::string describe(const System_ptr system);
    std::string describe(const Galaxy_ptr galaxy);

    bool have_discovered(const Planet_ptr planet) const;
    bool have_discovered(const System_ptr system) const;
    bool have_discovered(const Galaxy_ptr galaxy) const;

    void startoff(Planet_ptr planet);
    void update(double dt);

    void add_message(std::string message);
    std::list<std::string> get_messages();

    Event_ptr get_bootstrap_event();
    double get_number();
    double get_inception_time();

};
