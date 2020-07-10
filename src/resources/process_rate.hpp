#pragma once

#include "resource_pool.hpp"
#include "processed_resources.hpp"

class ProcessingRates {

public:
	double OCHNPS_food;
	double metallic_ore_metal;
	double nonmetallic_ore_ceramics;
	double high_density_ore_heavy_metal;
	double high_activity_ore_nuclear_fuel;
	double luminosity_solar_collection_area;
	double volume_habitable_volume;

	ProcessingRates(
		double food=0.0,
		double metal=0.0,
		double ceramics=0.0,
		double heavy_metal=0.0,
		double nuclear_fuel=0.0,
		double solar=0.0,
		double volume=0.0
		);

	void process(ResourcePool &res, ProcessedResources &pres, double dt);

};