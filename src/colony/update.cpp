#include "../util/formatter.hpp"
#include "../util/colour.hpp"
#include "../project/project.hpp"

#include "colony.hpp"

void Colony::update(double dt)
{
  // Stats
  // this->stats.update(dt);
  // double dpop = this->stats.population_stats.number.get_delta();

  // static bool notified_1 = false;
  // if ((dpop >= 1.0) and not notified_1) {
  //   this->add_message(Formatter() 
  //       << BOLD << "First colonial birth." << RESET);
  //   notified_1 = true;
  // }
 

  // Research progress 
  this->stats.population.number
    .multiply_base(1.0 + this->stats.derived.growth_rate->get_value()*dt);

  if (this->stats.technology.research_effort == 0.0) {

   double research_each = this->stats.technology.research_effort;
   switch (this->research_focus) {

     case RF_Equal:
       research_each /= 5.0;
       this->stats.technology.agriculture.increase_base(research_each);
       this->stats.technology.materials_gathering.increase_base(research_each);
       this->stats.technology.materials_processing.increase_base(research_each);
       this->stats.technology.power_generation.increase_base(research_each);
       this->stats.technology.astrogation.increase_base(research_each);
       break;

     case RF_Agriculture:
     case RF_Food:
       this->stats.technology.agriculture.increase_base(research_each);
       break;

     case RF_Resource:
       research_each /= 3.0;
       this->stats.technology.materials_gathering.increase_base(research_each);
       this->stats.technology.materials_processing.increase_base(research_each);
       this->stats.technology.power_generation.increase_base(research_each);
       break;

     case RF_Astrogation:
     case RF_Exploration:
       this->stats.technology.astrogation.increase_base(research_each);
       break;

     case RF_MaterialsGathering:
       this->stats.technology.materials_gathering.increase_base(research_each);
       break;

     case RF_MaterialsProcessing:
       this->stats.technology.materials_processing.increase_base(research_each);
       break;

     case RF_Power:
       this->stats.technology.power_generation.increase_base(research_each);
       break;
   }
  }


  // Update projects
  for (auto it = this->projects.begin(); it != this->projects.end(); it++) {
    auto project = it->second;
    auto status = project->update();
  
    if ((status == PS_Finished) or (status == PS_Error)) {
      this->projects.erase(it++);

      if (status == PS_Finished) {
        this->add_message(Formatter() << BOLD "Project \"" << project->get_name() << "\" complete." << RESET);
      }
      else {
        this->add_message(Formatter() << BOLD << FG_RED << "Project \"" << project->get_name() << "\" cancelled: " << RESET << project->get_error());
      }

    }

  }

}
