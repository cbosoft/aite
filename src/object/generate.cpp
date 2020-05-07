#include "../util/random.hpp"

#include "planet.hpp"

#include "object.hpp"

static std::map<SystemObjectType, RandomLikelihood> object_likelihoods = {
  {SO_Moon, Likelihood_Common},

  {SO_Planet, Likelihood_Certain},
  {SO_Planetoid, Likelihood_Common},
  {SO_GasGiant, Likelihood_Uncommon},
  {SO_EarthlikePlanet, Likelihood_Rare},

  {SO_Star, Likelihood_Certain},
  {SO_MainSequenceStar, Likelihood_Common},
  {SO_MassiveStar, Likelihood_Common},
  {SO_SupergiantStar, Likelihood_Uncommon},
  {SO_Supernova, Likelihood_Rare},
  {SO_NeutronStar, Likelihood_Uncommon},
  {SO_BlackHole, Likelihood_VeryRare},
  {SO_PairedStars, Likelihood_Rare},

  {SO_Nebula, Likelihood_Common},
  {SO_StellarNebula, Likelihood_Common},
  {SO_PlanetaryNebula, Likelihood_Common},

  {SO_AsteroidField, Likelihood_Common}
};

static std::map<SystemObjectType, std::list<SystemObjectType>> object_subtypes = {
  {SO_Moon, {SO_Moon}},
  {SO_Planet, {SO_Planet, SO_Planetoid, SO_GasGiant, SO_EarthlikePlanet}},
  {SO_Star, {SO_Star, SO_MainSequenceStar, SO_MassiveStar, SO_SupergiantStar, SO_Supernova, SO_NeutronStar, SO_BlackHole, SO_PairedStars}},
  {SO_Nebula, {SO_Nebula, SO_StellarNebula, SO_PlanetaryNebula}},
  {SO_AsteroidField, {SO_AsteroidField}}
};


SystemObject_ptr SystemObject::generate_object_or_subtype(System_ptr system, double position, SystemObjectType type)
{
  std::list<SystemObjectType> types = object_subtypes[type];
  std::list<RandomLikelihood> likelihoods;
  for (auto type : types) {
    likelihoods.push_back(object_likelihoods[type]);
  }

  type = probability_weighted_choice(likelihoods, types);
  return SystemObject::generate(system, position, type);
}


SystemObject_ptr SystemObject::generate(System_ptr system, double position, SystemObjectType type)
{
  SystemObject_ptr obj = nullptr;

  switch (type) {

    default:
    case SO_Planet:
      obj = Planet::generate(system, position);
      break;

    case SO_EarthlikePlanet:
      obj = EarthlikePlanet::generate(system, position);
      break;

  }

  return obj;
}
