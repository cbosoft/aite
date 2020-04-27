#include "history.hpp"
#include "../util/sqlite.hpp"
#include "../util/random.hpp"


std::list<HistoryPrototype> &HistoryElement::get_prototypes_list() {
  static std::list<HistoryPrototype> prototypes_list;
  static bool loaded = false;

  if (not loaded) {

    SQLiteInterface db = SQLiteInterface::get_resource_db();

    SQLiteResults res = db.execute("SELECT * FROM HistoryElements;");

    for (unsigned int i = 0; i < res.size(); i++) {
      SQLiteRow row = res[i];

      HistoryPrototype hp = {
        .name = row["Name"],
        .description = row["Description"],
        .relative_date_mean = row["RelativeDateMean"],
        .relative_date_std = row["RelativeDateStd"],
        .object_type = HistoryElement::str2object(row["ObjectType"]),
        .trigger_type = HistoryElement::str2trigger(row["TriggerType"]),
        .reward_type = HistoryElement::str2reward(row["RewardType"]),
        .reward_xp_mean = row["RewardMean"],
        .reward_xp_std = row["RewardStd"],
        .has_linked_feature = false,
        .linked_feature_name = "no" // TODO
      };

      if (row["LinkedFeatureID"].is_null()) {
        prototypes_list.push_back(hp);
      }
      else {
        // TODO add feature reference too
        std::cerr << "feature not linked" << std::endl;
        prototypes_list.push_back(hp);
      }

    }

    loaded = true;

  }

  return prototypes_list;
}
