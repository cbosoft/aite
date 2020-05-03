#include <iomanip>
#include <sstream>

#include "../util/format.hpp"
#include "colony.hpp"

std::string Colony::get_status() const
{
  std::stringstream ss;

  ss << std::setprecision(3)
    << "Name," << this->name << "|"
    << "population," << format_number(std::round(this->stats.population.number.get_base()))
    << " (" << format_number(std::round(this->stats.population.number.get_value())) << ")|"
    << "Growth rate," << this->stats.derived.growth_rate->get_value() << "|"
    << "Occupied stellar objects," << this->inhabited_objects.size() << "|"
    << "Projects," << this->projects.size() << "|"
    << "Travel speed (LY/I)," << this->stats.derived.travel_speed->get_value() << "|"
    //<< "Research effort," << this->stats.get_research_effort() << "|"
    << "Volume," << format_number(this->resources.volume) << "|"
    << "Habitable Volume," << format_number(this->processed_resources.habitable_volume) << "|"
    << "Proto organic matter," << format_number(this->resources.OCHNPS) << "|"
    << "Metallic ore," << format_number(this->resources.metallic_ore) << "|"
    << "Luminosity," << format_number(this->resources.luminosity) << "|"
    << "Mood," << format_number(this->stats.derived.mood->get_value()) << "|"
    ;

  return ss.str();
}


std::string Colony::get_project_status() const
{
  std::stringstream ss;

  int n = 0;
  for (auto kv : this->projects) {
    auto project = kv.second;

    if (n++) ss << "|";
    ss << project->get_name() << ":" << project->get_status_string();
  }

  return ss.str();
}
