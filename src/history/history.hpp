#pragma once
#include <string>

#include "../types.hpp"

/*
 * A history element is a facet of the planet/star/system/galaxy past that a
 * colony has uncovered, and thus gained some experience or knowledge that helps
 * them develop.
 *
 * A history is generated for an object with history upon generation. This
 * history will impact on the description of the object (an intense bombardment
 * of meteors will result in craters for example), it will impact in the
 * generation sub-objects (a galaxy with a black hole neighbour will have
 * gravity wrenched systems that are sub-normal, an exploded star will shower
 * rich deposits of minerals across the galaxy and so on).
 *
 * A history event is super-normal: normal expected events in the lifetime of
 * the object go without saying, and are not allocated events.
 *
 * */


enum HistoryElementTriggerType {HT_Underground, HT_Surface, HT_Space};

enum HistoryElementRewardType {HR_Technology, HR_Culture, HR_Mixed};

enum HistoryElementObjectType {
  HO_Galaxy,
  HO_System,
  HO_InterSystem,
  HO_Planet,
  HO_Star,
  HO_Moon,
  HO_Asteroid,
  HO_Nebula,
  HO_Any
};


typedef struct HistoryPrototype {
  std::string name;
  std::string description;
  double relative_date_mean;
  double relative_date_std;
  HistoryElementObjectType object_type;
  HistoryElementTriggerType trigger_type;
  HistoryElementRewardType reward_type;
  double reward_xp_mean;
  double reward_xp_std;
  bool has_linked_feature;
  std::string linked_feature_name;
} HistoryPrototype;


class HistoryElement {

  private:

    std::string name, description;
    double date, xp_reward;
    HistoryElementObjectType object_type;
    HistoryElementTriggerType trigger_type;
    HistoryElementRewardType reward_type;
    
    static HistoryElementRewardType str2reward(std::string s);
    static HistoryElementTriggerType str2trigger(std::string s);
    static HistoryElementObjectType str2object(std::string s);
    static std::list<HistoryPrototype> &get_prototypes_list();

  public:

    HistoryElement(std::string name, std::string description, double date, double reward, HistoryElementObjectType object_type, HistoryElementTriggerType trigger_type, HistoryElementRewardType reward_type);
    HistoryElement(std::string name, std::string description, double date, double reward, HistoryElementObjectType object_type, HistoryElementTriggerType trigger_type, HistoryElementRewardType reward_type, Feature_ptr feat);
    ~HistoryElement();

    std::string describe() const;

    static HistoryElement_ptr generate(HistoryElementObjectType object);
    static HistoryElement_ptr generate(HistoryElementObjectType object, HistoryElementTriggerType trigger);
    static HistoryElement_ptr generate(HistoryElementObjectType object, HistoryElementRewardType reward);
    static HistoryElement_ptr generate(HistoryElementObjectType object, HistoryElementTriggerType trigger, HistoryElementRewardType reward);
};
