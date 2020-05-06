#pragma once

#include <string>
#include <map>

#include "../resources/resources.hpp"
#include "../resources/processed_resources.hpp"
#include "../universe/universe.hpp"

class ProjectData {

  private:

    double number;
    double start_time;
    Resources resources;
    ProcessedResources processed_resources;
    std::map<std::string, double> float_vars;
    std::map<std::string, std::string> str_vars;

  public:

    ProjectData(double number)
      : number(number), start_time(Universe::get_universe()->get_time())
    {
    }

    ~ProjectData()
    {
    }

    void set_number_population(double number)
    {
      this->number = number;
    }

    void set_float(std::string key, double value)
    {
      this->float_vars[key] = value;
    }

    void set_str(std::string key, std::string value)
    {
      this->str_vars[key] = value;
    }

    double get_number() const
    {
      return this->number;
    }

    double get_start_time() const
    {
      return this->start_time;
    }

    double get_float(std::string key) const
    {
      return this->float_vars.at(key);
    }

    std::string get_str(std::string key) const
    {
      return this->str_vars.at(key);
    }

    double get_float_or_default(std::string key, double default_value) const
    {
      auto it = this->float_vars.find(key);
      if (it == this->float_vars.end())
        return default_value;
      else
        return it->second;
    }

    std::string get_str_or_default(std::string key, std::string default_value) const
    {
      auto it = this->str_vars.find(key);
      if (it == this->str_vars.end())
        return default_value;
      else
        return it->second;
    }

    operator double() const
    {
      return this->get_number();
    }

    bool operator==(const ProjectData &other)
    {
      return (this->number == other.number)
        && (this->str_vars == other.str_vars)
        && (this->float_vars == other.float_vars);
    }
};

