#pragma once

#include <string>
#include <map>

#include "../universe/universe.hpp"

class ProjectData {

  private:

    double number;
    double start_time;
    std::map<std::string, double> vars;

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

    void set_var(std::string key, double value)
    {
      this->vars[key] = value;
    }

    double get_number() const
    {
      return this->number;
    }

    double get_start_time() const
    {
      return this->start_time;
    }

    double get_var(std::string key) const
    {
      return this->vars.at(key);
    }

    operator double() const
    {
      return this->get_number();
    }

    double operator[](std::string s) const
    {
      return this->get_var(s);
    }

    bool operator==(const ProjectData &other)
    {
      return (this->number == other.number) && (this->vars == other.vars);
    }
};

