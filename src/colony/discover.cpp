#include <sstream>

#include "colony.hpp"

#include "../galaxy/galaxy.hpp"
#include "../system/system.hpp"
#include "../planet/planet.hpp"

#include "../util/alphabet.hpp"
#include "../util/thesaurus.hpp"


void Colony::discover(const Galaxy_ptr galaxy)
{
  std::string name = this->get_name(galaxy);
  this->galaxy_log[galaxy->get_id()] = name;
}


std::string Colony::get_name(Galaxy_ptr galaxy)
{
  unsigned long id = galaxy->get_id();
  if (this->galaxy_log.find(id) != this->galaxy_log.end()) {
    return this->galaxy_log[id];
  }

  if (this->galaxy_log.size() == 0) {
    return get_random_synonym("start", NOUN);
  }

  // TODO: name galaxies
  // possible naming rules:
  //   random combination of syllables
  //   names of famous scientists (esp astronomers/physicists/explorers)
  //   shapes
  //   countries
  //   inoccuous things like "the big one", "little cluster", "the dog" etc
  return "galaxy";
}

bool Colony::have_discovered(const Galaxy_ptr galaxy) const
{
  unsigned long id = galaxy->get_id();
  return (this->galaxy_log.find(id) != this->galaxy_log.end());
}




// SYSTEM

void Colony::discover(const System_ptr system)
{
  std::string name = this->get_name(system);
  this->system_log[system->get_id()] = name;
}


std::string Colony::get_name(System_ptr system)
{
  unsigned long id = system->get_id();
  if (this->system_log.find(id) != this->system_log.end()) {
    return this->system_log[id];
  }

  // TODO: name system
  // possible naming rules:
  //   random combination of syllables
  //   names of famous scientists (esp astronomers/physicists/explorers)
  return "system";
}

bool Colony::have_discovered(const System_ptr system) const
{
  unsigned long id = system->get_id();
  return (this->system_log.find(id) != this->system_log.end());
}



// PLANET


void Colony::discover(const Planet_ptr planet)
{
  std::string name = this->get_name(planet);
  this->planet_log[planet->get_id()] = name;
}


std::string Colony::get_name(Planet_ptr planet)
{
  auto id = planet->get_id();
  if (this->planet_log.find(id) != this->planet_log.end()) {
    return this->planet_log[id];
  }

  System_ptr system = planet->get_system();
  if (!this->have_discovered(system)) {
    this->discover(system);
  }

  auto planet_number = system->get_planet_index(planet);

  return Formatter() << this->get_name(system) << " " << latin_alphabet(planet_number);
}

bool Colony::have_discovered(const Planet_ptr planet) const
{
  unsigned long id = planet->get_id();
  return (this->planet_log.find(id) != this->planet_log.end());
}
