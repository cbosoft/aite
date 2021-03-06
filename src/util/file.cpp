#include <sys/stat.h>
#include "file.hpp"

bool file_exists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
