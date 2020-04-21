#include "../util/exception.hpp"
#include "../util/thesaurus.hpp"
#include "feature.hpp"


typedef struct FeaturePrototype {
  FeatureType type;
  std::string name;
  std::string description_prototype;
  RandomLikelihood existence_likelihood;
  RandomLikelihood occurrence_likelihood;
} FeaturePrototype;


static const std::list<FeaturePrototype> fo_planet_prototypes = {
  { FT_Weather,         "Extremely strong wind",       "{{occasionally}}, the {{weather}} becomes strange: extraordinarily {{strong,adjective}} {{winds}} assault the surface for a period before returning to normal.", Likelihood_Uncommon, Likelihood_Rare},
  { FT_Geographical,    "Volcanic activity",           "The planet has {{a}} {{lively,adjective}} mantle; volcanic erruptions have marred the surface and unleash fire and brimstone {{occasionally}}.", Likelihood_Common, Likelihood_Rare},
  { FT_Anthropological, "Evidence of sentient life",   "Investigation of a cave system on the planet has revealed {{elaborate,adjective}} wall paintings indicative of intelligent life.", Likelihood_Rare, Likelihood_Uncommon},
  { FT_Geographical,    "Extensive system of canyons", "{{a}} {{very big,adjective}} system of canyons has formed, perhaps as a result of a {{violent,adjective}} tectonic history.", Likelihood_Uncommon, Likelihood_Common}
};

static const std::map<FeatureObject, std::list<FeaturePrototype>> feature_prototypes = {
  {FO_Planet, fo_planet_prototypes}
};



Feature_ptr Feature::generate(FeatureObject obj)
{

  auto getres = feature_prototypes.find(obj);
  if (getres == feature_prototypes.end())
    throw AuthorError(Formatter() << "FeatureObject " << int(obj) << " prototypes not found.");
  auto applicable_prototypes = (*getres).second;

  std::list<FeaturePrototype> likely_prototypes;

  while (likely_prototypes.size() == 0){
    for (auto proto : applicable_prototypes) {
      if (check_likelihood(proto.existence_likelihood))
        likely_prototypes.push_back(proto);
    }
  }

  FeaturePrototype proto = *select_randomly(likely_prototypes.begin(), likely_prototypes.end());

  std::string description = substitute_in_prototype(proto.description_prototype);

  return std::make_shared<Feature>(proto.name, description, proto.existence_likelihood, proto.occurrence_likelihood);
}
