#include <iomanip>
#include <sstream>

#include "colony.hpp"

std::string Colony::get_status() const
{
  std::stringstream ss;

  ss << std::setprecision(3)
    << "Name," << this->name << "|"
    << "Total population,"; 
  double n = this->stats.population_stats.number.get_value();
  
  if (n < 1000)
    ss << int(n);
  else
    ss << std::scientific << n << std::fixed;
  
  ss << "|"
    << "Growth rate," << this->stats.derived_stats.growth_rate->get_value() << "|"
    << "Occupied stellar objects," << this->inhabited_objects.size() << "|"
    //<< "activities," << this->activities.size() << "|"
    << "Travel speed (LY/I)," << this->stats.derived_stats.travel_speed->get_value() << "|"
    << "Research effort," << this->stats.get_research_effort() << "|"
    ;

  return ss.str();
}
