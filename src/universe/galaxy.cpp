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

  Galaxy_ptr galaxy = Galaxy::generate(position);
  this->galaxies.push_back(galaxy);
  this->galaxies_by_id[galaxy->get_id()] = galaxy;
  return galaxy;
}


Galaxy_ptr Universe::get_galaxy(unsigned long id) const
{
  auto it = this->galaxies_by_id.find(id);
  if (it == this->galaxies_by_id.end()) {
    throw IndexError(Formatter() << "Galaxy with ID " << id << " not in universe.");
  }

  return (*it).second;
}
