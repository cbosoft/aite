#include "system.hpp"
#include "../planet/planet.hpp"
#include "../util/random.hpp"


System::System(Vec3 position, double size, unsigned long id, Galaxy_ptr galaxy)
{
  this->position = position;
  this->size = size;
  this->id = id;
  this->galaxy = galaxy;
}


System::~System()
{
  // do nothing
}


Vec3 System::get_position() const
{
  return this->position;
}

unsigned long System::get_id() const
{
  return this->id;
}

Planet_ptr System::get_random_planet()
{
  return this->planets[uniform_rand_i(0, this->planets.size()-1)];
}

unsigned int System::get_planet_index(Planet_ptr planet) const
{
  unsigned int index = 0;
  auto it = this->planets.begin();
  for (;it != this->planets.end(); it++, index++) {
    auto other_planet = (*it);

    if (planet == other_planet) {
      return index;
    }

  }

  throw IndexError("Planet not found in system!");
}

Galaxy_ptr System::get_galaxy() const
{
  return this->galaxy;
}



static unsigned long id_counter = 0;

System_ptr System::generate(Vec3 position, Galaxy_ptr galaxy)
{
  double size = lognormal_rand(3, 1);
  System_ptr system = std::make_shared<System>(position, size, id_counter++, galaxy);

  int nplanets = std::round(normal_rand(10, 2));
  double planet_distance = 0.0;
  for (int i = 0; i < nplanets; i++) {
    planet_distance += lognormal_rand(10, 1);
    Planet_ptr planet = Planet::generate(planet_distance, system);
    system->planets.push_back(planet);
  }

  // int nstars = 1;
  // for (int i = 1; i < System::max_number_stars; i++) {
  //   if (uniform_rand(0, 1) < 0.05) {
  //     nstars ++;
  //   }
  // }
  // TODO generate star(s)

  return system;
}
