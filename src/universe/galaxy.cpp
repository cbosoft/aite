#include "universe.hpp"
#include "../galaxy/galaxy.hpp"
#include "../util/random.hpp"

Galaxy_ptr Universe::get_galaxy(Vec3 position)
{

  for (auto galaxy : this->galaxies) {
    Vec3 dr = galaxy->get_position() - position;
    double dist = dr.magnitude();

    if (dist < lognormal_rand(15, 2)) {
      return galaxy;
    }
  }

  return Galaxy::generate(position);
}

