#pragma once
#include <map>
#include <string>
#include <mutex>

#include <nlohmann/json.hpp>

class Statistic {

  private:

    double initial_value;
    double base_value;
    std::map<std::string, double> additive_modifiers;
    std::map<std::string, double> multiplicative_modifiers;

    mutable std::mutex m;

  public:

    Statistic();
    Statistic(const Statistic &other);
    Statistic(double base_value);
    ~Statistic();

    virtual double get_base() const;

    void set_additive_modifier(std::string name, double value);
    void set_multiplicative_modifier(std::string name, double value);
    void remove_additive_modifier(std::string name);
    void remove_multiplicative_modifier(std::string name);
    void set_base(double value);
    void increase_base(double increment);
    void multiply_base(double factor);
    double get_value() const;
    double get_delta() const;
    std::string get_repr() const;

    operator double() const {
      return this->get_value();
    }

    Statistic &operator =(const Statistic &other)
    {
      this->initial_value = other.initial_value;
      this->base_value = other.base_value;
      this->additive_modifiers = other.additive_modifiers;
      this->multiplicative_modifiers = other.multiplicative_modifiers;
      return *this;
    }

    nlohmann::json to_serial() const;
    static Statistic from_serial(nlohmann::json ser);

};
