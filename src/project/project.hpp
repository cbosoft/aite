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

    // This method returns status of the project given the current state of the
    // colony, deciding whether the project can continue, or should pause, finish
    // or fail.
    virtual ProjectStatus get_status();

    // This method is the most important of the project object; it is called
    // every time-step to update the status of the project. In this method the
    // effects of the project should be enacted (item production should be
    // increased, research increased, exploration position increased and so on).
    virtual void do_work();

    // The next few methods may not need to be overridden, but if they are be
    // sure to call the base version too:
    // " Project::method() "

    // These methods call the release_- and take_resources methods respectively
    // as well as manage the status enum of the project and set the err string
    // accordingly.
    virtual void pause(std::string err="");
    virtual void unpause();

    // check if the project has sufficient resource to start. By default, this
    // just checks if the required population is available.
    virtual bool check_can_start();

    // set the project status, and take the required resources.
    virtual void start();

    // These two methods manage the *non-consumed* resources of the project
    // (people, volume, etc) that will be returned to the colony resource pool 
    // whenever the project is paused (or when it finishes).
    virtual void take_resources();
    virtual void release_resources();


    // The remaining methods are non-virtual.
    ProjectStatus update();

    std::string get_status_string() const;

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
