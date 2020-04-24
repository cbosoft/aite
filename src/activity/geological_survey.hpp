#pragma once
#include "activity.hpp"

/*
 * A geological survey is as it sounds: an in depth survey of a location
 *
 * */

class GeologicalSurvey : public virtual Activity {

  private:

    double ptime;

  public:

    GeologicalSurvey(Colony &colony) : Activity(colony) {}
    ~GeologicalSurvey(){}

    static Activity_ptr create(Colony &colony)
    {
      return std::make_shared<GeologicalSurvey>(colony);
    }

    void update();
};
