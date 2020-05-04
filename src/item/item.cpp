#include "../util/exception.hpp"
#include "../colony/colony.hpp"

#include "item.hpp"


Item::Item(std::string name, double effort_required, Resources requirements, ProcessedResources processed_requirements)
  :
    name(name),
    in_use(false),
    effort_required(effort_required),
    requirements(requirements),
    processed_requirements(processed_requirements)
{
}


std::string Item::get_name() const
{
  return this->name;
}


void Item::use()
{
  if (this->in_use)
    throw ItemInUseError(Formatter() << "Can't use " << this->name << " it is already in use!");

  this->in_use = true;
}


void Item::release()
{
  this->in_use = false;
}


#define GETFROM(R) \
  if (this->requirements. R > this->status. R) {\
    double amount_needed = this->requirements. R .get_amount_available() - this->status. R .get_amount_available();\
    double amount_available = colony.resources. R .get_amount_available();\
    double amount_transferred = (amount_available > amount_needed) ? amount_needed : amount_available; \
    if (amount_available < amount_needed) satisfied = false;\
    this->status. R += amount_transferred;\
    colony.resources. R -= amount_transferred;\
  }

#define GETFROM_PROCESSED(R) \
  if (this->processed_requirements. R > this->status_processed. R) {\
    double amount_needed = this->processed_requirements. R .get_amount_available() - this->status_processed. R .get_amount_available();\
    double amount_available = colony.processed_resources. R .get_amount_available();\
    double amount_transferred = (amount_available > amount_needed) ? amount_needed : amount_available; \
    if (amount_available < amount_needed) satisfied = false;\
    this->status_processed. R += amount_transferred;\
    colony.processed_resources. R -= amount_transferred;\
  }

bool Item::get_supplies(Colony &colony)
{

  bool satisfied = true;

  GETFROM(OCHNPS);
  GETFROM(metallic_ore);
  GETFROM(nonmetallic_ore);
  GETFROM(high_density_ore);
  GETFROM(high_activity_ore);
  GETFROM(luminosity);
  GETFROM(volume);

  GETFROM_PROCESSED(food);
  GETFROM_PROCESSED(metal);
  GETFROM_PROCESSED(heavy_metal);
  GETFROM_PROCESSED(ceramics);
  GETFROM_PROCESSED(nuclear_fuel);
  GETFROM_PROCESSED(habitable_volume);
  GETFROM_PROCESSED(power);
  GETFROM_PROCESSED(solar_collection_area);

  return satisfied;
}

bool Item::construct(double effort) {
  this->effort += effort;
  return this->effort >= this->effort_required;
}

bool Item::is_in_use() const
{
  return this->in_use;
}
