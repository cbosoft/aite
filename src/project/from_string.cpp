#include "../util/exception.hpp"


#include "project.hpp"
#include "recon.hpp"
#include "baby_boom.hpp"
#include "construct_habitat.hpp"


Project_ptr Project::from_string(std::string s, Colony &colony, const ProjectData &data)
{
  Project_ptr project = nullptr;

  if (s.compare("recon") == 0) {
    project = std::make_shared<Recon>(colony, data);
  }
  else if (s.compare("babyboom") == 0) {
    project = std::make_shared<BabyBoom>(colony, data);
  }
  else if (s.compare("constructhabitat") == 0) {
    project = std::make_shared<ConstructHabitat>(colony, data);
  }
  else {
    throw ArgumentError(Formatter() << "Project name not understood: \"" << s << "\".");
  }

  return project;
}
