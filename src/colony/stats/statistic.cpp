#include <sstream>
#include <iostream>

#include "../../util/colour.hpp"

#include "statistic.hpp"

Statistic::Statistic()
{
  // do nothing
}

Statistic::Statistic(double base_value)
  : base_value(base_value)
{
  this->inital_value = this->get_base();
}

Statistic::~Statistic()
{
  // do nothing
}

void Statistic::set_additive_modifier(std::string name, double value)
{
  std::lock_guard<std::mutex> l(this->m);
  this->additive_modifiers[name] = value;
}
void Statistic::set_multiplicative_modifier(std::string name, double value)
{
  std::lock_guard<std::mutex> l(this->m);
  this->multiplicative_modifiers[name] = value;
}

void Statistic::remove_additive_modifier(std::string name)
{
  std::lock_guard<std::mutex> l(this->m);
  auto it = this->additive_modifiers.find(name);

  if (it == this->additive_modifiers.end())
    return;

  this->additive_modifiers.erase(it);
}

void Statistic::remove_multiplicative_modifier(std::string name)
{
  std::lock_guard<std::mutex> l(this->m);
  auto it = this->multiplicative_modifiers.find(name);

  if (it == this->multiplicative_modifiers.end())
    return;

  this->multiplicative_modifiers.erase(it);
}

void Statistic::set_base(double value)
{
  std::lock_guard<std::mutex> l(this->m);
  this->base_value = value;
}

void Statistic::increase_base(double increment)
{
  this->set_base(this->get_base() + increment);
}

void Statistic::multiply_base(double factor)
{
  this->set_base(this->get_base()*factor);
}

double Statistic::get_value() const
{
  double tot = this->get_base();

  std::lock_guard<std::mutex> l(this->m);
  for (auto kv : this->additive_modifiers) {
    tot += kv.second;
  }
  for (auto kv : this->multiplicative_modifiers) {
    tot *= kv.second;
  }

  return tot;
}

std::string Statistic::get_repr() const
{
  std::stringstream ss;

  if (this->additive_modifiers.size() and this->multiplicative_modifiers.size()) {
    ss << "[";
  }

  ss << this->base_value << DIM " base" RESET;

  if (this->additive_modifiers.size()) {
    for (auto kv : this->additive_modifiers) {
      ss
        << " + " << kv.second
        << (kv.second > 0.0 ? FG_GREEN : FG_RED)
        << kv.first
        << RESET;
    }
    if (this->multiplicative_modifiers.size()) {
      ss << "]";
    }
  }

  if (this->multiplicative_modifiers.size()) {
    for (auto kv : this->multiplicative_modifiers) {
      ss
        << " ✕ " << kv.second
        << (kv.second > 1.0 ? FG_GREEN : FG_RED)
        << kv.first
        << RESET;
    }
  }



  return ss.str();
}

double Statistic::get_base() const
{
  std::lock_guard<std::mutex> l(this->m);
  return this->base_value;
}

double Statistic::get_delta() const
{
  double base = this->get_base();

  std::lock_guard<std::mutex> l(this->m);
  return base - this->inital_value;
}
