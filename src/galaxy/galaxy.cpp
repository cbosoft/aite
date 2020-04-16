#include "galaxy.hpp"
#include "../util/random.hpp"

Galaxy::Galaxy(Vec3 position, double size, unsigned long id)
{
  this->position = position;
  this->size = size;
  this->id = id;
}

Galaxy::~Galaxy()
{
  // do nothing
}


Vec3 Galaxy::get_position() const
{
  return this->position;
}


static unsigned long id_counter = 0;

Galaxy_ptr Galaxy::generate(Vec3 position)
{

  double size = lognormal_rand(9, 2);
  Galaxy_ptr galaxy = std::make_shared<Galaxy>(position, size, id_counter++);

  return galaxy;
}
