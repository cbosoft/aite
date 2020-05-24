#include <regex>
#include <sstream>

#include "project_data.hpp"


ProjectData::ProjectData(double number)
  : number(number), start_time(Universe::get_universe()->get_time())
{
}

ProjectData::ProjectData(std::vector<std::string> args)
  : number(1), start_time(Universe::get_universe()->get_time())
{
  static std::regex KV_RE("([^|]+)=([^|]+)");
  static std::regex FLOAT_RE("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?$");

  for (const auto &arg : args) {
    std::smatch match;
    std::regex_match(arg, match, KV_RE);
    std::string key = match[1];
    std::string value = match[2];

    std::cerr << arg << " (" << key << ": " << value << ")" << std::endl;

    if (std::regex_match(value, FLOAT_RE)) {

      double value_float = std::stof(value);
      if (key.compare("number") == 0) {
        this->number = value_float;
      }
      else {
        this->set_float(key, value_float);
      }

    }
    else {

      this->set_str(key, value);

    }

  }
}


ProjectData::~ProjectData()
{
}


void ProjectData::set_number_population(double number)
{
  this->number = number;
}


void ProjectData::set_float(std::string key, double value)
{
  this->float_vars[key] = value;
}


void ProjectData::set_str(std::string key, std::string value)
{
  this->str_vars[key] = value;
}


double ProjectData::get_number() const
{
  return this->number;
}


double ProjectData::get_start_time() const
{
  return this->start_time;
}


double ProjectData::get_float(std::string key) const
{
  return this->float_vars.at(key);
}


std::string ProjectData::get_str(std::string key) const
{
  return this->str_vars.at(key);
}


double ProjectData::get_float_or_default(std::string key, double default_value) const
{
  auto it = this->float_vars.find(key);
  if (it == this->float_vars.end())
    return default_value;
  else
    return it->second;
}


std::string ProjectData::get_str_or_default(std::string key, std::string default_value) const
{
  auto it = this->str_vars.find(key);
  if (it == this->str_vars.end())
    return default_value;
  else
    return it->second;
}
