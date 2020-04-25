#include "object.hpp"
#include "planet.hpp"

SystemObject_ptr SystemObject::generate(System_ptr system, double position, SystemObjectType type)
{
  SystemObject_ptr obj = nullptr;

  switch (type) {

    default:
    case SO_Planet:
      obj = Planet::generate(system, position);
      break;

    case SO_EarthlikePlanet:
      obj = EarthlikePlanet::generate(system, position);
      break;

  }

  return obj;
}
