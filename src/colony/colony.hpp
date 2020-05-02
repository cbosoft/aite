#pragma once
#include <string>
#include <memory>
#include <map>
#include <list>
#include <mutex>

#include "stats/statistic.hpp"
#include "stats/derived_statistic.hpp"
#include "../types.hpp"
#include "../resources/resource_pool.hpp"
#include "../resources/processed_resources.hpp"


class Colony {

  private:

    Universe_ptr universe;

    // std::list<Ability> abilities; // list of abilities the colony has acquired
    std::map<std::string, Activity_ptr> activities; // list of activities the colony is doing

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

  public:

    struct {
      struct {
        Statistic number;
        Statistic medecine;
        Statistic mood;
        Statistic longevity;
      } population;

      double research_effort;
      //ResearchFocus research_focus;
      struct {
        Statistic agriculture;
        Statistic materials_gathering;
        Statistic materials_processing;
        Statistic power_generation;
        Statistic astrogation;
      } technology;

      struct {
        Statistic religion;
        Statistic art;
        Statistic social;
        Statistic politics;
      } culture;

      struct {
        DerivedStatistic_ptr growth_rate;
        DerivedStatistic_ptr required_habitable_volume;
        DerivedStatistic_ptr food_production_power_efficiency;
        DerivedStatistic_ptr food_production_efficiency;
        DerivedStatistic_ptr material_harvesting_power_efficiency;
        DerivedStatistic_ptr advanced_material_technique_progress;
        DerivedStatistic_ptr solar_generation_efficiency;
        DerivedStatistic_ptr nulear_power_minimum_activity;
        DerivedStatistic_ptr detection_distance;
        DerivedStatistic_ptr travel_speed;
        DerivedStatistic_ptr max_habitable_temperature;
        DerivedStatistic_ptr max_habitable_gravity;
      } derived;
    } stats;

    ResourcePool resources;
    ProcessedResources processed_resources;

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

    void add_activity(Activity_ptr activity);
    void add_message(std::string message);
    std::list<std::string> get_messages();
    std::string get_status() const;

    Event_ptr get_bootstrap_event();
    double get_number();
    double get_inception_time();

    bool try_inhabit(SystemObject_ptr object, double number);
    bool can_inhabit(SystemObject_ptr object);


};
