#include "process_rate.hpp"

ProcessingRates::ProcessingRates(
		double food,
		double metal,
		double ceramics,
		double heavy_metal,
		double nuclear_fuel,
		double solar,
		double volume)
	:
	OCHNPS_food(food),
	metallic_ore_metal(metal),
	nonmetallic_ore_ceramics(ceramics),
	high_density_ore_heavy_metal(heavy_metal),
	high_activity_ore_nuclear_fuel(nuclear_fuel),
	luminosity_solar_collection_area(solar),
	volume_habitable_volume(volume)
{
	// do nothing
}

void ProcessingRates::process(ResourcePool &res, ProcessedResources &pres, double dt)
{
	{
		double food_conv = dt*this->OCHNPS_food;
		double remainder = res.OCHNPS.use(food_conv);
		pres.food += (food_conv - remainder);
	}

	{
		double metal_conv = dt*this->metallic_ore_metal;
		double remainder = res.metallic_ore.use(metal_conv);
		pres.metal += (metal_conv - remainder);
	}

	{
		double ceramic_conv = dt*this->nonmetallic_ore_ceramics;
		double remainder = res.nonmetallic_ore.use(ceramic_conv);
		pres.ceramics += (ceramic_conv - remainder);
	}

	{
		double heavy_metal_conv = dt*this->high_density_ore_heavy_metal;
		double remainder = res.high_density_ore.use(heavy_metal_conv);
		pres.heavy_metal += (heavy_metal_conv - remainder);
	}

	{
		double nuclear_conv = dt*this->high_activity_ore_nuclear_fuel;
		double remainder = res.high_activity_ore.use(nuclear_conv);
		pres.nuclear_fuel += (nuclear_conv - remainder);
	}

	{
		double solar_conv = dt*this->luminosity_solar_collection_area;
		double remainder = res.luminosity.use(solar_conv);
		pres.solar_collection_area += (solar_conv - remainder);
	}

	{
		double volume_conv = dt*this->volume_habitable_volume;
		double remainder = res.volume.use(volume_conv);
		pres.habitable_volume += (volume_conv - remainder);
	}
}