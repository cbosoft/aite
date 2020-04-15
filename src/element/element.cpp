#include "element.hpp"


Element::Element(std::string name, std::string symbol, int number_electrons, double molecular_weight)
{
  this->name = name;
  this->symbol = symbol;
  this->number_electrons = number_electrons;
  this->molecular_weight = molecular_weight;
}


Element::~Element()
{
  // do nothing
}


std::string Element::get_name() const
{
  return this->name;
}
