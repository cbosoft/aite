#include "../util/exception.hpp"
#include "../util/thesaurus.hpp"
#include "feature.hpp"


Feature_ptr Feature::generate(FeatureObject obj, FeatureType type)
{
  auto list = Feature::get_prototypes_list();

  std::list<FeaturePrototype> sublist;

  if (obj == FO_Any) {
    sublist = list;
  }
  else {
    for (auto proto : list) {
      if (((proto.object_type == obj) or (proto.object_type = FO_Any)) 
          and ((proto.type == type) or (proto.type == FT_Any))) {
        sublist.push_back(proto);
      }
    }
  }

  if (sublist.size() == 0)
    throw AuthorError(Formatter() << "object type " << int(obj) << " prototypes not found.");

  std::list<FeaturePrototype> likely_prototypes;
  while (likely_prototypes.size() == 0){
    for (auto proto : sublist) {
      if (check_likelihood(proto.existence_likelihood))
        likely_prototypes.push_back(proto);
    }
  }

  FeaturePrototype proto = *select_randomly(likely_prototypes.begin(), likely_prototypes.end());
  return std::make_shared<Feature>(proto);
}
