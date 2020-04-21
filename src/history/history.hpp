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

enum HistoryElementTriggerType {HE_TriggerUnderground, HE_TriggerSurface, HE_TriggerOuterSpace};

enum HistoryElementRewardType {HE_RewardTechnology, HE_RewardCulture};

class HistoryElement {

  private:

    std::string name, description;
    double date, xp_reward;

  public:

    HistoryElement(std::string name, std::string description, double date);
    ~HistoryElement();

    static HistoryElement_ptr get_history(HistoryElementTriggerType trigger);
};
