#include <ctime>
#include "time.hpp"

unsigned long get_system_time()
{
  unsigned long t = time(nullptr);
  return t;
}
