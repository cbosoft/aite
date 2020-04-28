#include "resource_pool.hpp"


void ResourcePool::add_source(Resources *resources)
{
  this->OCHNPS.add_resource(&resources->OCHNPS);
  this->metallic_ore.add_resource(&resources->metallic_ore);
  this->nonmetallic_ore.add_resource(&resources->nonmetallic_ore);
  this->high_density_ore.add_resource(&resources->high_density_ore);
  this->high_activity_ore.add_resource(&resources->high_activity_ore);
  this->luminance.add_resource(&resources->luminance);
  this->volume.add_resource(&resources->volume);
}
