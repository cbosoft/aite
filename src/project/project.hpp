#pragma once

#include <string>
#include <map>

#include "../util/format.hpp"
#include "../types.hpp"
#include "../universe/universe.hpp"
#include "project_data.hpp"



enum ProjectStatus { PS_Inactive, PS_Active, PS_Paused, PS_Finished, PS_Error };


class Project {

  private:

    std::string name;

  protected:

    std::string error;
    ProjectStatus status;
    ProjectData data;
    Colony &colony;

  public:

    Project(Colony &colony, ProjectData data, std::string name);
    virtual ~Project();

    virtual void pause(std::string err="");
    virtual void unpause();
    virtual bool check_can_start();
    virtual void start();
    virtual void take_resources();
    virtual void release_resources();

    std::string get_status_string() const;

    virtual ProjectStatus update();

    std::string get_error() const;
    std::string get_name() const;
    double get_start_time() const;
    double get_elapsed_time() const;
    ProjectData get_data() const;
    void set_data(ProjectData data);

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
