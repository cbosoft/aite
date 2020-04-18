#include "universe.hpp"
#include "../colony/colony.hpp"
#include "../galaxy/galaxy.hpp"
#include "../system/system.hpp"
#include "../planet/planet.hpp"
#include "../util/random.hpp"

Colony_ptr Universe::add_colony(std::string name)
{

  Galaxy_ptr galaxy = this->get_galaxy(vec3_urand(-this->size, this->size));
  System_ptr system = galaxy->new_system();
  Planet_ptr planet = system->get_random_planet();

  std::cerr << "new colony being introduced: " << name << " on Planet #" << planet->get_id() << std::endl;

  Colony_ptr colony = std::make_shared<Colony>(name, planet, this->time);
  this->colonies[name] = colony;

  this->add_event(colony->get_bootstrap_event());
  return colony;
}

bool Universe::has_colony(std::string name)
{
  return this->colonies.find(name) != this->colonies.end();
}
