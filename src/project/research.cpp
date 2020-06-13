#include "../util/formatter.hpp"

#include "research.hpp"

Research::Research(Colony &colony, const ProjectData &data)
  : Project(colony, data, Formatter()<<"researching " <<data.get_str_or_default("focus", "(no focus)"))
{
}
