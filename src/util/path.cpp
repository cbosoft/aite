#include <list>

#include "../util/exception.hpp"
#include "../util/file.hpp"

#include "path.hpp"


static std::list<std::string> paths = {
  "resources.db",
  "/opt/aite/resources.db"
};


std::string get_resource_path()
{
  for (auto path :  paths) {
    if (file_exists(path)) {
      return path;
    }
  }

  throw ResourceError("Resources not found!", true);
}


void add_resource_path(std::string path)
{
  if (file_exists(path))
    throw ResourceError(Formatter() << "Cannot add path: \"" << path << "\" does not exist.", true);

  paths.push_front(path);
}


void add_resource_path_no_check(std::string path)
{
  paths.push_front(path);
}
