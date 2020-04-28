#include <sstream>

#include "colony.hpp"

std::string Colony::get_status() const
{
  std::stringstream ss;

  ss
    << "Name," << this->name << "\n"
    << "Total population," << this->stats.population_stats.number.get_value() << "\n"
    << "Growth rate," << this->stats.derived_stats.growth_rate->get_value() << "\n"
    << "Occupied stellar objects," << this->inhabited_objects.size() << "\n"
    //<< "activities," << this->activities.size() << "\n"
    << "Travel speed (LY/I)," << this->stats.derived_stats.travel_speed->get_value() << "\n"
    << "Research effort," << this->stats.get_research_effort() << "\n"
    ;

  return ss.str();
}
