#pragma once
#include <string>

#include "../types.hpp"

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
