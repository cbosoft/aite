#include "chemical_component.hpp"


ChemicalComponent::ChemicalComponent(std::string name, double weight,
    double charge, double halflife, int Z, LinearEqn melting_point, LinearEqn boiling_point)
  :
    name(name),
    weight(weight),
    charge(charge),
    halflife(halflife),
    Z(Z),
    melting_point(melting_point),
    boiling_point(boiling_point)
{
  // do nothing
}


ChemicalComponent::~ChemicalComponent()
{
}


const std::string &ChemicalComponent::get_name() const
{
  return this->name;
}


double ChemicalComponent::get_weight() const
{
  return this->weight;
}


double ChemicalComponent::get_charge() const
{
  return this->charge;
}


Phase ChemicalComponent::get_phase(double pressure, double temperature) const
{
  double mp = this->melting_point(pressure);

  if (temperature < mp)
    return PhaseSolid;

  double bp = this->boiling_point(pressure);

  if (temperature < bp)
    return PhaseLiquid;

  // TODO better cut off for plasma?
  if (temperature < 6000)
    return PhaseGas;

  return PhasePlasma;
}

int ChemicalComponent::get_Z() const
{
  return this->Z;
}


bool ChemicalComponent::is_radioactive() const
{
  return this->halflife < std::numeric_limits<double>::infinity();
}
