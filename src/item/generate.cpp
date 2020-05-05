#include "../util/sqlite.hpp"
#include "../util/exception.hpp"

#include "item.hpp"

typedef struct ItemPrototype {
  std::string name;
  double effort_required;
  Resources requirements;
  ProcessedResources processed_requirements;
} ItemPrototype;


std::map<std::string, ItemPrototype> &get_prototypes()
{
  static std::map<std::string, ItemPrototype> prototypes;
  static bool loaded = false;

  if (not loaded) {
    SQLiteInterface db = SQLiteInterface::get_resource_db();

    SQLiteResults res = db.execute("SELECT * FROM ITEMS;");

    for (unsigned int i = 0; i < res.size(); i++) {
      auto row = res[i];
      Resources r(
            row["RequiredOCHNPS"],
            row["RequiredMetallicOre"],
            row["RequiredNonmetallicOre"],
            row["RequiredHighDensityOre"],
            row["RequiredHighActivityOre"],
            row["RequiredLuminosity"],
            row["RequiredVolume"]
          );
      ProcessedResources pr(
            row["RequiredFood"],
            row["RequiredMetal"],
            row["RequiredHeavyMetal"],
            row["RequiredCeramics"],
            row["RequiredNuclearFuel"],
            row["RequiredHabitableVolume"],
            row["RequiredFoodPower"],
            row["RequiredFoodSolarCollectionArea"]
          );
      ItemPrototype p = {
        .name = row["Name"],
        .effort_required = row["RequiredEffort"],
        .requirements = r,
        .processed_requirements = pr
      };
    }

  }

  return prototypes;
}

Item_ptr Item::generate(std::string name)
{
  auto prototypes = get_prototypes();

  auto it = prototypes.find(name);
  if (it == prototypes.end())
    throw AuthorError(Formatter() << "Unknown item requested: " << name << ".");

  auto prototype = it->second;
  return std::make_shared<Item>(prototype.name, prototype.effort_required, prototype.requirements, prototype.processed_requirements);
}
