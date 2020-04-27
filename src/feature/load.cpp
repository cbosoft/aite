#include "feature.hpp"
#include "../util/sqlite.hpp"


std::list<FeaturePrototype> &Feature::get_prototypes_list()
{
  static std::list<FeaturePrototype> prototypes;
  static bool loaded = false;

  if (not loaded) {
    SQLiteInterface db = SQLiteInterface::get_resource_db();

    SQLiteResults res = db.execute("SELECT * FROM Features;");

    for (unsigned int i = 0; i < res.size(); i++) {
      SQLiteRow row = res[i];

      FeaturePrototype prototype = {
        .name = row["Name"],
        .description_prototype = row["DescriptionPrototype"],
        .existence_likelihood = str2likelihood(row["ExistenceRarity"]),
        .occurrence_likelihood = str2likelihood(row["OccurrenceRarity"]),
        .object_type = Feature::str2object(row["ObjectType"]),
        .type = Feature::str2type(row["FeatureType"])
      };

      prototypes.push_back(prototype);
    }

    loaded = true;
  }

  return prototypes;
}
