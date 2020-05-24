#include "../util/exception.hpp"


#include "project.hpp"
#include "recon.hpp"
#include "baby_boom.hpp"
#include "construct_habitat.hpp"


Project_ptr Project::from_name(std::string name, Colony &colony)
{
  return Project::from_args({name}, colony);
}

Project_ptr Project::from_args(std::vector<std::string> args, Colony &colony)
{
  Project_ptr project = nullptr;
  ProjectData data(args);
  const std::string &name = args[0];

  if (name.compare("recon") == 0) {
    project = std::make_shared<Recon>(colony, data);
  }
  else if (name.compare("babyboom") == 0) {
    project = std::make_shared<BabyBoom>(colony, data);
  }
  else if (name.compare("constructhabitat") == 0) {
    project = std::make_shared<ConstructHabitat>(colony, data);
  }
  else {
    throw ArgumentError(Formatter() << "Project name not understood: \"" << name << "\".");
  }

  return project;
}
