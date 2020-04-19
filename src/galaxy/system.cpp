#include "galaxy.hpp"
#include "../universe/universe.hpp"
#include "../colony/colony.hpp"
#include "../system/system.hpp"
#include "../util/random.hpp"

System_ptr Galaxy::new_system()
{
  Vec3 position;

  bool unsuitable = true;
  while (unsuitable) {

    position = vec3_urand(-this->size, this->size);
    unsuitable = false;

    for (auto system : this->systems) {

      Vec3 dr = system->get_position() - position;
      double dist = dr.magnitude();

      if (dist < lognormal_rand(3, 1)) {
        unsuitable = true;
      }

    }

  }

  Galaxy_ptr self_ptr = Universe::get_universe()->get_galaxy(this->id);
  return System::generate(position, self_ptr);
}
