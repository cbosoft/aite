#include "feature.hpp"
#include "../util/exception.hpp"
#include "../util/thesaurus.hpp"


Feature::Feature(FeaturePrototype prototype)
  :
    name(prototype.name),
    existence_likelihood(prototype.existence_likelihood),
    occurence_likelihood(prototype.occurrence_likelihood),
    object_type(prototype.object_type)
{
  this->description = Thesaurus::getref().substitute_in_prototype(prototype.description_prototype);
}


Feature::~Feature()
{
  // do nothing
}


bool Feature::has_history() const
{
  return this->associated_history == nullptr;
}


HistoryElement_ptr Feature::get_history() const
{
  return this->associated_history;
}


std::string Feature::describe() const
{
  return this->description;
}


FeatureObject Feature::str2object(std::string s)
{
  if (s.compare("galaxy") == 0) {
    return FO_Galaxy;
  }
  else if (s.compare("system") == 0) {
    return FO_System;
  }
  else if (s.compare("intersystem") == 0) {
    return FO_InterSystem;
  }
  else if (s.compare("planet") == 0) {
    return FO_Planet;
  }
  else if (s.compare("star") == 0) {
    return FO_Star;
  }
  else if (s.compare("moon") == 0) {
    return FO_Moon;
  }
  else if (s.compare("asteroid") == 0) {
    return FO_Asteroid;
  }
  else if (s.compare("nebula") == 0) {
    return FO_Nebula;
  }
  else if (s.compare("any") == 0) {
    return FO_Any;
  }
  else {
    throw AuthorError(Formatter() << "Unknown object: " << s << ".");
  }
}


FeatureType Feature::str2type(std::string s)
{
  if (s.compare("geographical") == 0) {
    return FT_Geographical;
  }
  else if (s.compare("meteorological") == 0) {
    return FT_Meteorological;
  }
  else if (s.compare("geological") == 0) {
    return FT_Geological;
  }
  else if (s.compare("zoological") == 0) {
    return FT_Zoological;
  }
  else if (s.compare("anthropological") == 0) {
    return FT_Anthropological;
  }
  else if (s.compare("any") == 0) {
    return FT_Any;
  }
  else {
    throw AuthorError(Formatter() << "Unknown feature type: " << s << ".");
  }
}
