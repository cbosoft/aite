#include "system.hpp"
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

  // TODO generate planets

  return system;
}
