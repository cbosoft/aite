#pragma once

#include <string>
#include <map>

#include "../util/format.hpp"
#include "../types.hpp"
#include "../colony/colony.hpp"
#include "../universe/universe.hpp"



class ActivityConstructorData {

  private:

    double number;
    std::map<std::string, double> vars;

  public:

    ActivityConstructorData(double number)
      : number(number)
    {
    }

    ~ActivityConstructorData()
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
};



class Activity {

  private:

    double start_time;
    std::string name;
    bool started;

  protected:

    double number;
    Colony &colony;

  public:

    Activity(Colony &colony, double number, std::string name);
    virtual ~Activity();

    bool try_start();

    virtual bool check()
    {
      return true;
    }

    std::string get_name() const
    {
      return this->name;
    }

    double get_start_time() const
    {
      return this->start_time;
    }

    double get_elapsed_time() const
    {
      return Universe::get_universe()->get_time() - this->start_time;
    }

    static Activity_ptr from_string(std::string s, Colony &colony, const ActivityConstructorData &acd);
    static ActivityConstructorData default_constructor_data();
};
