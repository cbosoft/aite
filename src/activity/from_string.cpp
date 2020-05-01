#include "../util/exception.hpp"
#include "activity.hpp"
#include "recon.hpp"
#include "baby_boom.hpp"
#include "construct_habitat.hpp"


Activity_ptr Activity::from_string(std::string s, Colony &colony, const ActivityConstructorData &acd)
{
  Activity_ptr activity = nullptr;

  if (s.compare("recon") == 0) {
    activity = std::make_shared<Recon>(colony, acd);
  }
  else if (s.compare("babyboom") == 0) {
    activity = std::make_shared<BabyBoom>(colony, acd);
  }
  else if (s.compare("constructhabitat") == 0) {
    activity = std::make_shared<ConstructHabitat>(colony, acd);
  }
  else {
    throw ArgumentError(Formatter() << "Activity name not understood: \"" << s << "\".");
  }

  if (activity->try_start())
    return activity;
  else
    return nullptr;
}
