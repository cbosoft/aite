#include "../universe/universe.hpp"
#include "recon.hpp"

Recon::Recon(Colony &colony, const ProjectData &acd)
  : Project(colony, acd, "recon")
{
  // TODO
  // maybe get recon focus from acd.vars
  // focus being planets, stars, or maybe a specific direction?
}

Recon::~Recon()
{
}

ProjectStatus Recon::update()
{
  // Universe_ptr universe = Universe::get_universe();

  // for (auto galaxy : universe->get_galaxies())
  // {
  // }

  return PS_Finished;
}
