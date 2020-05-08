#include "system.hpp"

unsigned long System::next_id()
{
  static unsigned long id = 0;
  return id++;
}
