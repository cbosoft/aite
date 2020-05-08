#include "../util/random.hpp"

#include "system.hpp"


System::System(Vec3 position, double size, Galaxy_ptr galaxy)
  :
    id(System::next_id()),
    size(size),
    position(position),
    galaxy(galaxy)
{
  // do nothing
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


SystemObject_ptr System::get_random_object()
{
  return *select_randomly(this->objects.begin(), this->objects.end());
}


const std::vector<SystemObject_ptr> &System::get_objects() const
{
  return this->objects;
}


unsigned int System::get_object_index(SystemObject_ptr object) const
{
  unsigned int index = 0;
  auto it = this->objects.begin();
  for (;it != this->objects.end(); it++, index++) {
    auto other_object = (*it);

    if (object == other_object) {
      return index;
    }

  }

  throw IndexError("Object not found in system!");
}


Galaxy_ptr System::get_galaxy() const
{
  return this->galaxy;
}
