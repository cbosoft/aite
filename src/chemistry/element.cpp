#include <limits>

#include "element.hpp"


Element::Element(
    std::string name, std::string symbol, int number_electrons,
    double molecular_weight, double halflife,
    LinearEqn boiling_point, LinearEqn melting_point)
  :
    ChemicalComponent(name, molecular_weight, 0.0, halflife, number_electrons, boiling_point, melting_point),
    symbol(symbol)
{
  // do nothing
}


Element::~Element()
{
  // do nothing
}
