#include "element.hpp"


Element::Element(
    std::string name, std::string symbol, int number_electrons, 
    double molecular_weight, double covalent_radius, double boiling_point_m, 
    double melting_point_m)
  : name(name), symbol(symbol), number_electrons(number_electrons),
  molecular_weight(molecular_weight), covalent_radius(covalent_radius), 
  boiling_point_m(boiling_point_m), melting_point_m(melting_point_m)
{
  // do nothing
}


Element::~Element()
{
  // do nothing
}


std::string Element::get_name() const
{
  return this->name;
}

int Element::get_number_electrons() const
{
  return this->number_electrons;
}
