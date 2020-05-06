#include "../colony/colony.hpp"

#include "geological_survey.hpp"

ProjectStatus GeologicalSurvey::get_status()
{
  switch (this->status) {

    case PS_Paused:
      if (this->colony.has_free_item("geosurvey equipment")) {
        this->colony.use_item("geosurvey equipment");
        this->status = PS_Active;
      }
      else {
        // start produce item project
      }
      break;

    case PS_Active:
      // TODO
      break;

    default:
      break;
  }

  return this->status;
}

void GeologicalSurvey::do_work()
{
}
