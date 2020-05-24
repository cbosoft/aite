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

    ProjectData(double number);
    ProjectData(std::string s);
    ~ProjectData();

    void set_number_population(double number);
    void set_float(std::string key, double value);
    void set_str(std::string key, std::string value);
    double get_number() const;
    double get_start_time() const;
    double get_float(std::string key) const;
    std::string get_str(std::string key) const;
    double get_float_or_default(std::string key, double default_value) const;
    std::string get_str_or_default(std::string key, std::string default_value) const;

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

