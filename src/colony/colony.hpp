#pragma once
#include <string>
#include <memory>
#include <map>

class Action;
class ActionResults;
class Planet;
class Colony {

  private:
    std::string name;
    std::string strategy;

    std::map<int, std::string> planet_log;

    std::shared_ptr<ActionResults> results_of_last_action();

    std::string name_planet(const std::shared_ptr<Planet> planet) const;

  public:

    Colony();
    ~Colony();

    std::shared_ptr<Action> get_next_action();

    void discover_planet(std::shared_ptr<Planet> planet);
    std::string describe_planet(const std::shared_ptr<Planet> planet) const;

};
