#include <sstream>
#include <cmath>

#include "format.hpp"

std::string format_number_as_scientific(double number)
{
  std::stringstream ss;

  double p = std::round(std::log10(number));
  double v = number / std::pow(10.0, p);

  ss << v << "×10^" << int(p);
  return ss.str();
}

std::string format_number(double number)
{
  std::stringstream ss;

  if ((number > 1000) or (std::log10(number) < -1.0))
    ss << format_number_as_scientific(number);
  else
    ss << number;
  return ss.str();
}
