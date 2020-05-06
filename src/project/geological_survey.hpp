#pragma once
#include "project.hpp"

/*
 * A geological survey is as it sounds: an in depth survey of a location
 *
 * */

class GeologicalSurvey : public virtual Project {

  public:

    GeologicalSurvey(Colony &colony, const ProjectData &data);
    ~GeologicalSurvey();

    ProjectStatus get_status() override;
    void do_work() override;
};
