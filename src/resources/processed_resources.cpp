#include "processed_resources.hpp"

ProcessedResources::ProcessedResources()
{
}

ProcessedResources::ProcessedResources(double food, double metal, double heavy_metal,
    double ceramics, double nuclear_fuel, double habitable_volume,
    double power, double solar_collection_area)
{
  this->food = food;
  this->metal = metal;
  this->heavy_metal = heavy_metal;
  this->ceramics = ceramics;
  this->nuclear_fuel = nuclear_fuel;
  this->habitable_volume = habitable_volume;
  this->power = power;
  this->solar_collection_area = solar_collection_area;
}
