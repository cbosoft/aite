#include <limits>

#include "element.hpp"


Element::Element(
    std::string name, std::string symbol, int number_electrons, 
    double molecular_weight, double halflife, 
    LinearEqn boiling_point, LinearEqn melting_point
    )
  :
    ChemicalComponent(name, molecular_weight, boiling_point, melting_point),
    symbol(symbol),
    number_electrons(number_electrons),
    halflife(halflife)
{
  // do nothing
}


Element::~Element()
{
  // do nothing
}


const std::string &Element::get_name() const
{
  return this->name;
}

int Element::get_number_electrons() const
{
  return this->number_electrons;
}


double Element::get_boiling_point(double pressure) const
{
  return this->boiling_point_m*pressure + boiling_point_c;
}


double Element::get_melting_point(double pressure) const
{
  return this->melting_point_m*pressure + melting_point_c;
}

Phase Element::get_phase(double pressure, double temperature) const
{
  double mp = this->get_melting_point(pressure);

  if (temperature < mp)
    return PhaseSolid;

  double bp = this->get_boiling_point(pressure);

  if (temperature < bp)
    return PhaseLiquid;

  if (temperature < 6000)
    return PhaseGas;

  return PhasePlasma;
}


bool Element::is_radioactive() const
{
  return this->halflife < std::numeric_limits<double>::infinity();
}

double Element::get_molecular_weight() const
{
  return this->molecular_weight;
}
