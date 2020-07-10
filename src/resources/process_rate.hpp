#pragma once

#include "resource_pool.hpp"
#include "processed_resources.hpp"

class ProcessingRates {

private:
	double OCHNPS_food;
	double metallic_ore_metal;
	double nonmetallic_ore_ceramics;
	double high_density_ore_heavy_metal;
	double high_activity_ore_nuclear_fuel;
	double luminosity_solar_collection_area;
	double volume_habitable_volume;

public:

	void process(ResourcePool &res, ProcessedResources &pres, double dt);

};