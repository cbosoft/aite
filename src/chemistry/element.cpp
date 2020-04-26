#include "element.hpp"


Element::Element(
    std::string name, std::string symbol, int number_electrons, 
    double molecular_weight, double halflife, 
    double boiling_point_m, double boiling_point_c,
    double melting_point_m, double melting_point_c
    )
  : 
    name(name),
    symbol(symbol),
    number_electrons(number_electrons),
    molecular_weight(molecular_weight),
    halflife(halflife), 
    boiling_point_m(boiling_point_m),
    boiling_point_c(boiling_point_c),
    melting_point_m(melting_point_m),
    melting_point_c(melting_point_c)
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
