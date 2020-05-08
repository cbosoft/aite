#include <sstream>

#include "colony.hpp"

#include "../galaxy/galaxy.hpp"
#include "../system/system.hpp"
#include "../object/object.hpp"

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
    return Thesaurus::getref().get_random_synonym("start");
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

  auto thesaurus = Thesaurus::getref();
  std::string system_name = thesaurus.capitalise(thesaurus.generate_from_syllables());
  this->system_log[id] = system_name;
  return system_name;
}

bool Colony::have_discovered(const System_ptr system) const
{
  unsigned long id = system->get_id();
  return (this->system_log.find(id) != this->system_log.end());
}



// OBJECT


void Colony::discover(const SystemObject_ptr object)
{
  std::string name = this->get_name(object);
  this->object_log[object->get_id()] = name;

  this->add_message(Formatter() 
      << BOLD << "Discovered " << object->get_object_name() << RESET << ". It has been named " << name 
      << ". " << this->describe(object) );
}


std::string Colony::get_name(SystemObject_ptr object)
{
  auto id = object->get_id();
  auto res = this->object_log.find(id);
  if (res != this->object_log.end()) {
    return (*res).second;
  }

  auto thesaurus = Thesaurus::getref();
  return thesaurus.capitalise(thesaurus.generate_from_syllables());
}

bool Colony::have_discovered(const SystemObject_ptr object) const
{
  unsigned long id = object->get_id();
  return (this->object_log.find(id) != this->object_log.end());
}
