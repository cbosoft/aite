#pragma once
#include <map>
#include <string>

class Statistic {

  private:
    double base_value;
    std::map<std::string, double> additive_modifiers;
    std::map<std::string, double> multiplicative_modifiers;

  public:

    Statistic(double base_value);
    ~Statistic();

    void set_additive_modifier(std::string name, double value);
    void set_multiplicative_modifier(std::string name, double value);
    void remove_additive_modifier(std::string name);
    void remove_multiplicative_modifier(std::string name);
    void set_base(double value);
    void increase_base(double increment);
    double get_value() const;
    std::string get_repr() const;

};
