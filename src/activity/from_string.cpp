#include "../util/exception.hpp"
#include "activity.hpp"
#include "recon.hpp"
#include "baby_boom.hpp"
#include "construct_habitat.hpp"


Activity_ptr Activity::from_string(std::string s, Colony &colony)
{
  Activity_ptr activity = nullptr;

  if (s.compare("recon") == 0) {
    activity = Recon::create(colony);
  }
  else if (s.compare("babyboom") == 0) {
    activity = std::make_shared<BabyBoom>(colony);
  }
  else if (s.compare("constructhabitat") == 0) {
    activity = std::make_shared<ConstructHabitat>(colony);
  }
  else {
    throw ArgumentError(Formatter() << "Activity name not understood: \"" << s << "\".");
  }

  return activity;
}
