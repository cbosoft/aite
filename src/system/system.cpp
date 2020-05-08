#include "system.hpp"
#include "../object/object.hpp"
#include "../util/random.hpp"


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



static unsigned long id_counter = 0;

System_ptr System::generate(Vec3 position, Galaxy_ptr galaxy)
{
  double size = lognormal_rand(3, 1);
  System_ptr system = std::make_shared<System>(position, size, id_counter++, galaxy);

  SystemObject_ptr star = SystemObject::generate(system, 0.0, SO_Star);
  system->objects.push_back(star);

  double zero_luminance = star->get_luminosity();

  int nplanets = std::round(normal_rand(10, 2));
  double object_distance = 0.0;
  for (int i = 0; i < nplanets; i++) {
    object_distance += lognormal_rand(10, 1);
    SystemObject_ptr object = SystemObject::generate(system, object_distance, SO_Planet);
    object->set_luminosity(zero_luminance/std::pow(object_distance , 2.0));
    system->objects.push_back(object);
  }

  return system;
}


System_ptr System::generate_inhabitable(Vec3 position, Galaxy_ptr galaxy, SystemObject_ptr &object)
{
  double size = lognormal_rand(3, 1);
  System_ptr system = std::make_shared<System>(position, size, id_counter++, galaxy);

  int nplanets = std::round(normal_rand(10, 2));
  double object_distance = 0.0;
  int i = 0;
  for (; i < nplanets/2; i++) {
    object_distance += lognormal_rand(10, 1);
    SystemObject_ptr o = SystemObject::generate(system, object_distance, SO_Planet);
    system->objects.push_back(o);
  }

  i++;
  object_distance += lognormal_rand(10, 1);
  object = SystemObject::generate(system, object_distance, SO_EarthlikePlanet);
  system->objects.push_back(object);
  std::cerr << "generated habitable" << std::endl;

  for (; i < nplanets/2; i++) {
    object_distance += lognormal_rand(10, 1);
    SystemObject_ptr o = SystemObject::generate(system, object_distance, SO_Planet);
    system->objects.push_back(o);
  }

  return system;
}
