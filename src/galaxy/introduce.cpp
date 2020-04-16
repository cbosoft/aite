#include "galaxy.hpp"
#include "../colony/colony.hpp"
#include "../system/system.hpp"
#include "../util/random.hpp"

void Galaxy::introduce(Colony_ptr colony)
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

  System_ptr system = System::generate(position);

  system->introduce(colony);
}
