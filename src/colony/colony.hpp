#pragma once
#include <string>
#include <memory>
#include <map>

class Action;
class ActionResults;

class Planet;
typedef std::shared_ptr<Planet> Planet_ptr;

class Colony {

  private:
    std::string name;
    std::string strategy;

    std::map<int, std::string> planet_log;

    std::shared_ptr<ActionResults> results_of_last_action();

    std::string name_planet(const Planet_ptr planet) const;

  public:

    Colony(std::string name);
    ~Colony();

    std::shared_ptr<Action> get_next_action();

    void discover_planet(const Planet_ptr planet);
    std::string describe_planet(const Planet_ptr planet) const;
    void startoff(Planet_ptr planet);

};
