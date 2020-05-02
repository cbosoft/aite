#include <iomanip>
#include <sstream>

#include "../util/format.hpp"
#include "colony.hpp"

std::string Colony::get_status() const
{
  std::stringstream ss;

  ss << std::setprecision(3)
    << "Name," << this->name << "|"
    << "Total population,"; 
  double n = this->stats.population.number.get_value();
  
  if (n < 1000)
    ss << int(n);
  else
    ss << std::scientific << n << std::fixed;
  
  ss << "|"
    << "Growth rate," << this->stats.derived.growth_rate->get_value() << "|"
    << "Occupied stellar objects," << this->inhabited_objects.size() << "|"
    << "Projects," << this->projects.size() << "|"
    << "Travel speed (LY/I)," << this->stats.derived.travel_speed->get_value() << "|"
    //<< "Research effort," << this->stats.get_research_effort() << "|"
    << "Volume," << format_number(this->resources.volume) << "|"
    << "Habitable Volume," << format_number(this->processed_resources.habitable_volume) << "|"
    << "Proto organic matter," << format_number(this->resources.OCHNPS) << "|"
    << "Metallic ore," << format_number(this->resources.metallic_ore) << "|"
    ;

  return ss.str();
}
