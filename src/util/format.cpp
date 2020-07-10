#include <sstream>
#include <cmath>
#include <iomanip>

#include "format.hpp"

std::string format_number_as_scientific(double number)
{
  std::stringstream ss;

  double p = std::round(std::log10(number));
  double v = number / std::pow(10.0, p);

  ss << std::setprecision(3) << v << "×10^" << int(p);
  return ss.str();
}

std::string format_number(double number)
{
  std::stringstream ss;

  if ((number != 0.0) and ((number > 1000) or (std::log10(number) < -1.0)))
    ss << format_number_as_scientific(number);
  else
    ss << number;
  return ss.str();
}

std::string format_number_no_decimal(double number)
{
  std::stringstream ss;

  if ((number != 0.0) and ((number > 1000) or (std::log10(number) < -1.0)))
    ss << format_number_as_scientific(number);
  else
    ss << int(number);
  return ss.str();
}
