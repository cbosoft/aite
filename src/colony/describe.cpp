#include <iomanip>
#include <sstream>

#include "../util/thesaurus.hpp"
#include "../util/format.hpp"
#include "../system/system.hpp"
#include "../object/object.hpp"
#include "../chemistry/element.hpp"

#include "colony.hpp"

std::string Colony::describe(const Galaxy_ptr galaxy)
{
  // TODO
  (void) galaxy;
  return "nope";
}


std::string Colony::describe(const System_ptr system)
{
  // TODO
  (void) system;
  return "nope";
}


std::string Colony::describe(const SystemObject_ptr object)
{
  auto d = object->describe();

  std::stringstream ss;

  if (this->object_log.find(object->get_id()) == this->object_log.end()) {
    return "Yet to discover that object, you cannot describe it. It remains a mystery to you.";
  }

  std::string name = this->object_log.at(object->get_id());

  auto system = object->get_system();
  int i = system->get_object_index(object);

  if (i == 0) {
    ss << name << " is the " << object->get_object_name() << " at the centre of its system. ";
  }
  else {
    ss << name << " is the " << Thesaurus::getref().position(i) << " "
      << object->get_object_name() << " of the " << this->get_name(system) << " system. ";
  }

  ss
    << name << " is coloured " << object->get_colour() << ". "
    << "It has a diameter of " << format_number(d.diameter) << " AU"
    << " and a density " << format_number(d.density)
    << " times Earth's. This results in a";

  switch (d.gl) {

    case GL_NonExistant:
      ss << "n almost none existant";
      break;

    case GL_Weak:
      ss << " very weak";
      break;

    case GL_Normal:
      ss << "n Earth-like";
      break;

    case GL_Heavy:
      ss << " heavy";
      break;

    case GL_Oppressive:
      ss << " unbearably strong";
      break;

    case GL_SpineCrushing:
      ss << " insurmountable";
      break;
  }

  ss << " gravitational field (g = " << format_number(d.gravitational_constant) << "). ";

  if (d.al != AL_None) {
    ss << "The " << object->get_object_name() << " has a";

    switch (d.al) {
      case AL_Thin:
        ss << " very thin";
        break;

      case AL_EarthLike:
        ss << "n";
        break;

      case AL_Thick:
        ss << " thick";
        break;

      case AL_Heavy:
        ss << " very heavy";
        break;

      default:
        break;
    }

    ss << " atmosphere. ";
  }


  ss << "Average surface temperature is " << format_number(d.temperature) << "K; ";
  switch(d.tl) {

    case TL_NearAbsoluteZero:
      ss << "not far from absolute zero.";
      break;

    case TL_ExtremeCold:
      ss << "extremely cold.";
      break;

    case TL_VeryCold:
      ss << "very cold.";
      break;

    case TL_Cold:
      ss << "cold.";
      break;

    case TL_Temperate:
      ss << "relatively mild.";
      break;

    case TL_Hot:
      ss << "hot.";
      break;

    case TL_VeryHot:
      ss << "very hot.";
      break;

    case TL_ExtremeHeat:
      ss << "extremely hot.";
      break;

    case TL_Scorching:
      ss << "scorching.";
      break;

    case TL_Unfathomable:
      ss << "unfathomably hot.";
      break;
  }

  ss << " The " << object->get_object_name() << " " << d.composition_summary;

  return ss.str();
}
