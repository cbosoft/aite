#include <iostream>
#include "../util/format.hpp"
#include "../colony/colony.hpp"
#include "client.hpp"


void GameClient::show_status()
{

	double total_ore = 0.0;
	total_ore += this->colony->resources.metallic_ore;
	total_ore += this->colony->resources.nonmetallic_ore;
	total_ore += this->colony->resources.high_density_ore;

	double total_materials = 0.0;
	total_materials += this->colony->processed_resources.metal;
	total_materials += this->colony->processed_resources.heavy_metal;
	total_materials += this->colony->processed_resources.ceramics;



  std::cerr
  << "            Name: " << this->colony->get_name() << "\n"
  << "      Population: " << format_number_no_decimal(this->colony->get_number()) << "\n"
  << "            Food: " << format_number(this->colony->processed_resources.food) << " kg\n"
  << "       Resources: " << format_number(total_materials) << " kg (" << format_number(total_ore) << " kg)\n"
//  << "         Nuclear Fuel: " << format_number(this->colony->processed_resources.nuclear_fuel) << " kg\n"
  << "Habitable Volume: " << format_number(this->colony->processed_resources.habitable_volume) << " m³ (" << format_number(this->colony->resources.volume) << " m³)\n"
  << "Solar Coll. Area: " << format_number(this->colony->processed_resources.solar_collection_area) << " m²\n"
  ;
}