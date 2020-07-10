#pragma once
#include <string>
#include <memory>
#include <map>
#include <list>
#include <mutex>

#include "../types.hpp"
#include "../resources/resource_pool.hpp"
#include "../resources/processed_resources.hpp"

#include <nlohmann/json.hpp>


// A Colony is a player controlled civilisation, controlled via commands issued
// by the client to the server. A colony grows over time, and has needs to be
// met. A colony has resources, and uses resources to engage in projects. Stats
// about the colony give indications of what can be done to improve the
// situation for the colony, increasing growth rate and opening up available
// living situations.
class Colony {

  private:

    // A ptr to the universe the colony exists within
    Universe_ptr universe;
    
    // list of abilities the colony has acquired
    // std::list<Ability> abilities;

    std::mutex messages_mutex;
    std::list<std::string> messages;

    double time_of_inception;
    std::string name;
    std::string strategy;

    std::list<Item_ptr> inventory;
    std::map<std::string, int> items_not_in_use;
    std::map<int, std::string> object_log;
    std::map<int, std::string> system_log;
    std::map<int, std::string> galaxy_log;
    std::string get_name(const SystemObject_ptr planet);
    std::string get_name(const System_ptr system);
    std::string get_name(const Galaxy_ptr galaxy);
    std::list<SystemObject_ptr> inhabited_objects;
    std::list<System_ptr> inhabited_systems;
    std::list<Galaxy_ptr> inhabited_galaxies;

    std::list<SystemObject_ptr> get_uninhabited(System_ptr system) const;

  public:

    double number;
    double inhabited_volume;
    double growth_rate;

    ResourcePool resources;
    ProcessedResources processed_resources;

    Colony();
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

    bool ready_to_expand() const;
    void explore();

    void update(double dt);

    bool has_free_item(std::string name) const;
    void use_item(std::string name);
    void use_item(Item_ptr item);
    void add_item(Item_ptr item);
    void add_project(Project_ptr project);
    void add_message(std::string message);
    std::list<std::string> get_messages();

    std::string get_status() const;
    std::string get_project_status() const;

    Event_ptr get_bootstrap_event();
    double get_number();
    double get_inception_time();

    bool inhabit(SystemObject_ptr object);

    static Colony_ptr from_serial(nlohmann::json json);
    static Colony_ptr from_serial(std::string s);
    nlohmann::json to_serial() const;

    friend class GameClient;

};
