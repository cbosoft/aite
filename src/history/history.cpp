#include <list>
#include "history.hpp"
#include "../util/exception.hpp"

HistoryElement::HistoryElement(std::string name, std::string description, 
    double date, double reward, HistoryElementObjectType object_type, 
    HistoryElementTriggerType trigger_type, HistoryElementRewardType reward_type)
  : name(name), description(description), date(date), xp_reward(reward), 
  object_type(object_type), trigger_type(trigger_type), reward_type(reward_type)
{
  // do nothing
}

HistoryElement::~HistoryElement()
{
  // do nothing
}


HistoryElementTriggerType HistoryElement::str2trigger(std::string s)
{
  if (s.compare("underground") == 0) {
    return HT_Underground;
  }
  else if (s.compare("surface") == 0) {
    return HT_Surface;
  }
  else if (s.compare("air") == 0) {
    return HT_Space;
  }
  else {
    throw AuthorError(Formatter() << "Unknown trigger: " << s << ".");
  }
}


HistoryElementRewardType HistoryElement::str2reward(std::string s)
{
  if (s.compare("technology") == 0) {
    return HR_Technology;
  }
  else if (s.compare("culture") == 0) {
    return HR_Culture;
  }
  else if (s.compare("mixed") == 0) {
    return HR_Mixed;
  }
  else {
    throw AuthorError(Formatter() << "Unknown reward: " << s << ".");
  }
}


HistoryElementObjectType HistoryElement::str2object(std::string s)
{
  if (s.compare("galaxy") == 0) {
    return HO_Galaxy;
  }
  else if (s.compare("system") == 0) {
    return HO_System;
  }
  else if (s.compare("intersystem") == 0) {
    return HO_InterSystem;
  }
  else if (s.compare("planet") == 0) {
    return HO_Planet;
  }
  else if (s.compare("star") == 0) {
    return HO_Star;
  }
  else if (s.compare("moon") == 0) {
    return HO_Moon;
  }
  else if (s.compare("asteroid") == 0) {
    return HO_Asteroid;
  }
  else if (s.compare("nebula") == 0) {
    return HO_Nebula;
  }
  else if (s.compare("any") == 0) {
    return HO_Any;
  }
  else {
    throw AuthorError(Formatter() << "Unknown object: " << s << ".");
  }
}


std::string HistoryElement::describe() const
{
  return this->description;
}

