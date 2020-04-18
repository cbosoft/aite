#include "galaxy.hpp"
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

  return System::generate(position);
}
