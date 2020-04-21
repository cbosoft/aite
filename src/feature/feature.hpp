#pragma once
#include <string>

#include "../util/random.hpp"
#include "../types.hpp"

/*
 * A feature is a describeable aspect of a planet, star, system, galaxy,
 * nebula etc. Features may have attached historic events, or be just brought
 * about by no special mechanism explicitly.
 *
 * Features have different types, reflecting how a colony may discover them.
 *
 * Features with an attached history cause the history element to be discovered
 * if the feature is investigated.
 *
 * A feature may be difficult to find, reflected by a "discovery chance" - a
 * probability that the feature is found, compounded over time spent with the
 * object.
 * */

enum FeatureType {

  // A geographical feature is found on discovery if weather is not in the way.
  // These are features like particular arrangements of landmass, mountains, or
  // peculiar arrangements (of planets, of caves or gorges). Geographic in terms
  // of systems and galaxys refers more abstractly to system or galactic object
  // position and phenomena
  FT_Geographical,

  // Weather, if present, is the likely the first discovered feature and coveres
  // air and wind patterns, as well as cycles similar to the water cycle on
  // earth, and astro-weather such as solar and radiation "storms".
  FT_Weather,

  // Geological features are centred around the mineral make-up of the object;
  // normally applying to solid objects (planets, moons, asteroids), it can also
  // refer to the dust inbetween objects in fields, systems, and galaxies.
  FT_Geological,

  // Anthropological features are those created by sentient life forms, and are
  // equivalent to archaeological finds and such.
  FT_Anthropological,

  // A zoological feature relates to non-sentient life discovery and associated
  // effects.
  FT_Zoological
};

enum FeatureObject {
  FO_Galaxy,
  FO_System,
  FO_InterSystem,
  FO_Planet,
  FO_Star,
  FO_Moon,
  FO_Asteroid,
  FO_Nebula
};



class Feature {

  private:

    std::string name;
    std::string description;
    // existence is the likelihood that the feature exists at all and occurrence
    // is likelihood that a colony, inhabiting the object experiences the
    // feature
    RandomLikelihood existence_likelihood, occurence_likelihood;
    HistoryElement_ptr associated_history;

  public:
    Feature(std::string name, std::string description, RandomLikelihood existence_likelihood, 
        RandomLikelihood occurence_likelihood);
    Feature(std::string name, std::string description, RandomLikelihood existence_likelihood, 
        RandomLikelihood occurence_likelihood, HistoryElement_ptr associated_history);
    ~Feature();

    std::string describe() const;
    bool has_history() const;
    HistoryElement_ptr get_history() const;

    static Feature_ptr generate(FeatureObject obj);
    static Feature_ptr generate(FeatureObject obj, FeatureType type);
};
