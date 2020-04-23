#include "history.hpp"
#include "../util/random.hpp"
#include "../util/exception.hpp"


HistoryElement_ptr HistoryElement::generate(HistoryElementObjectType object_type)
{
  auto list = get_prototypes_list();

  if (list.size() < 1)
    throw ResourceError("No history prototype found in resource db!");

  std::list<HistoryPrototype> sublist;
  if (object_type == HO_Any) {
    sublist = list;
  }
  else {
    for (auto proto : list) {
      if (proto.object_type == object_type)
        sublist.push_back(proto);
    }
  }

  HistoryPrototype prototype = (*select_randomly(sublist.begin(), sublist.end()));

  double date = normal_rand(
      prototype.relative_date_mean, prototype.relative_date_std);

  double reward = normal_rand(
      prototype.reward_xp_mean, prototype.reward_xp_std);

  return std::make_shared<HistoryElement>(
        prototype.name,
        prototype.description,
        date,
        reward,
        prototype.object_type, 
        prototype.trigger_type,
        prototype.reward_type
      );
}
