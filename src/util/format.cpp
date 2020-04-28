#include <sstream>
#include <cmath>

#include "format.hpp"


std::string format_number(double number)
{
  std::stringstream ss;

  if (number > 1000)
    ss << std::scientific;

  if (std::log10(number) < -1)
    ss << std::scientific;

  ss << number;
  return ss.str();
}
