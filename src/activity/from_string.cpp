#include "../util/exception.hpp"
#include "activity.hpp"
#include "recon.hpp"


Activity_ptr from_string(std::string s, Colony &colony)
{
  Activity_ptr activity = nullptr;

  if (s.compare("recon") == 0) {
    activity = Recon::create(colony);
  }
  else {
    throw ArgumentError(Formatter() << "Activity name not understood: \"" << s << "\".");
  }

  return activity;
}
