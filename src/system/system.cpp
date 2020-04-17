#include "system.hpp"
#include "../planet/planet.hpp"
#include "../util/random.hpp"


System::System(Vec3 position, double size, unsigned long id)
{
  this->position = position;
  this->size = size;
  this->id = id;
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


static unsigned long id_counter = 0;

System_ptr System::generate(Vec3 position)
{
  double size = lognormal_rand(3, 1);
  auto system = std::make_shared<System>(position, size, id_counter++);

  int nplanets = std::round(normal_rand(10, 2));
  double planet_distance = 0.0;
  for (int i = 0; i < nplanets; i++) {
    planet_distance += lognormal_rand(10, 1);
    Planet_ptr planet = Planet::generate(planet_distance);
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
