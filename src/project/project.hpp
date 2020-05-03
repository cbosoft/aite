#pragma once

#include <string>
#include <map>

#include "../util/format.hpp"
#include "../types.hpp"
#include "../colony/colony.hpp"
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
};



class Project {

  private:

    std::string name, reason;
    bool started;

  protected:

    ProjectData data;
    Colony &colony;

  public:

    Project(Colony &colony, ProjectData data, std::string name);
    virtual ~Project();

    bool check_can_start();
    std::string get_reason_cannot_start() const;
    void start();

    virtual bool check()
    {
      return true;
    }

    std::string get_name() const
    {
      return this->name;
    }

    ProjectData get_data() const
    {
      return this->data;
    }

    void set_data(ProjectData data)
    {
      this->data = data;
    }

    double get_start_time() const
    {
      return this->data.get_start_time();
    }

    double get_elapsed_time() const
    {
      return Universe::get_universe()->get_time() - this->get_start_time();
    }

    static Project_ptr from_string(std::string s, Colony &colony, const ProjectData &data);

    Project &operator=(const Project &proj)
    {
      if (this->name.compare(proj.name) != 0) {
        throw AuthorError("projects of different type cannot be set equal to one another");
      }

      this->data = proj.data;

      return *this;
    }
};
