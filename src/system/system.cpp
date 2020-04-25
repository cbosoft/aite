#include "system.hpp"
#include "../object/object.hpp"
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


SystemObject_ptr System::get_random_object()
{
  return this->objects[uniform_rand_i(0, this->objects.size()-1)];
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

  int nplanets = std::round(normal_rand(10, 2));
  double object_distance = 0.0;
  for (int i = 0; i < nplanets; i++) {
    object_distance += lognormal_rand(10, 1);
    SystemObject_ptr object = SystemObject::generate(system, object_distance, SO_Planet);
    system->objects.push_back(object);
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
