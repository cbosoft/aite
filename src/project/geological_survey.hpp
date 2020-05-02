#pragma once
#include "project.hpp"

/*
 * A geological survey is as it sounds: an in depth survey of a location
 *
 * */

class GeologicalSurvey : public virtual Project {

  private:

    double ptime;

  public:

    GeologicalSurvey(Colony &colony, const ProjectData &data) : Project(colony, data, "geological survey") {}
    ~GeologicalSurvey(){}

    static Project_ptr create(Colony &colony)
    {
      return std::make_shared<GeologicalSurvey>(colony);
    }

    void update();
};
