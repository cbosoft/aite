#include "universe.hpp"
#include "../colony/colony.hpp"
#include "../galaxy/galaxy.hpp"
#include "../util/random.hpp"

Colony_ptr Universe::add_colony(std::string name)
{
  std::cerr << "new colony being introduced: " << name << std::endl;
  Colony_ptr colony = std::make_shared<Colony>(name);

  this->colonies[name] = colony;

  Galaxy_ptr galaxy = this->get_galaxy(vec3_urand(-this->size, this->size));

  galaxy->introduce(colony);

  return colony;
}

bool Universe::has_colony(std::string name)
{
  return this->colonies.find(name) != this->colonies.end();
}
