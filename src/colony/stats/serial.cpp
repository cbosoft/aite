#include "statistic.hpp"

nlohmann::json modifier_to_json(std::map<std::string, double> mod)
{
    nlohmann::json json;

    for (const auto &kv : mod) {
        json[kv.first] = kv.second;
    }
    return json;
}

std::map<std::string, double> json_to_modifier(nlohmann::json json)
{
    std::map<std::string, double> rv;
    for (auto &elem : json.items()) {
        rv[elem.key()] = elem.value();
    }
    return rv;
}

nlohmann::json Statistic::to_serial() const
{
    nlohmann::json json;
    json["base_value"] = this->base_value;
    json["initial_value"] = this->inital_value;
    json["additive_modifiers"] = modifier_to_json(this->additive_modifiers);
    json["multiplicative_modifiers"] = modifier_to_json(this->multiplicative_modifiers);
    return json;
}

Statistic Statistic::from_serial(nlohmann::json json)
{
    Statistic rv;
    // TODO safe get to avoid loading from broken JSON
    rv.base_value = json["base_value"];
    rv.inital_value = json["initial_value"];
    rv.additive_modifiers = json_to_modifier(json["additive_modifiers"]);
    rv.multiplicative_modifiers = json_to_modifier(json["multiplicative_modifiers"]);
    return rv;
}