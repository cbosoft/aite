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
  data["number"] = this->number;

  nlohmann::json res;
  res["OCHNPS"] = double(this->resources.OCHNPS);
  res["metallic_ore"] = double(this->resources.metallic_ore);
  res["nonmetallic_ore"] = double(this->resources.nonmetallic_ore);
  res["high_density_ore"] = double(this->resources.high_density_ore);
  res["high_activity_ore"] = double(this->resources.high_activity_ore);
  res["luminosity"] = double(this->resources.luminosity);
  res["volume"] = double(this->resources.volume);

  data["resources"] = res;

  nlohmann::json pres;
  pres["food"] = double(this->processed_resources.food);
  pres["metal"] = double(this->processed_resources.metal);
  pres["heavy_metal"] = double(this->processed_resources.heavy_metal);
  pres["ceramics"] = double(this->processed_resources.ceramics);
  pres["nuclear_fuel"] = double(this->processed_resources.nuclear_fuel);
  pres["habitable_volume"] = double(this->processed_resources.habitable_volume);
  pres["power"] = double(this->processed_resources.power);
  pres["solar_collection_area"] = double(this->processed_resources.solar_collection_area);

  data["processed_resources"] = pres;
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
  rv->number = data["number"];

  nlohmann::json res = data["resources"];
  rv->resources.OCHNPS.add_dummy(res["OCHNPS"]);
  rv->resources.metallic_ore.add_dummy(res["metallic_ore"]);
  rv->resources.nonmetallic_ore.add_dummy(res["nonmetallic_ore"]);
  rv->resources.high_density_ore.add_dummy(res["high_density_ore"]);
  rv->resources.high_activity_ore.add_dummy(res["high_activity_ore"]);
  rv->resources.luminosity.add_dummy(res["luminosity"]);
  rv->resources.volume.add_dummy(res["volume"]);

  nlohmann::json pres = data["processed_resources"];
  rv->processed_resources.food = pres["food"];
  rv->processed_resources.metal = pres["metal"];
  rv->processed_resources.heavy_metal = pres["heavy_metal"];
  rv->processed_resources.ceramics = pres["ceramics"];
  rv->processed_resources.nuclear_fuel = pres["nuclear_fuel"];
  rv->processed_resources.habitable_volume = pres["habitable_volume"]  ;
  rv->processed_resources.power = pres["power"];
  rv->processed_resources.solar_collection_area = pres["solar_collection_area"];
  
  // TODO: other data members
  // stats
  // planets etc
  return rv;
}
