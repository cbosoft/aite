#include "colony.hpp"

// issue with definition of an "assert" macro in nlohmann if in 3rdparty first
// include order
#include <nlohmann/json.hpp>


nlohmann::json Colony::to_serial() const
{
  // encode colony into chosen serialisation format
  // return serial'd data

  nlohmann::json data;

  data["name"] = this->name;
  // TODO: other data members
  // stats
  // planets etc
  return data;
}

Colony_ptr Colony::from_serial(std::string s)
{
  nlohmann::json data = nlohmann::json::parse(s);
  return Colony::from_serial(data);
}

Colony_ptr Colony::from_serial(nlohmann::json data)
{
  Colony_ptr rv = std::make_shared<Colony>();

  rv->name = data["name"];
  // TODO: other data members
  // stats
  // planets etc
  return rv;
}
