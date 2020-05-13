#pragma once

#include <memory>

#include "../types.hpp"
#include "../util/equation.hpp"

class ChemicalComponent {

  protected:

    std::string name;
    double weight;
    double charge;
    double halflife;
    int Z;
    LinearEqn melting_point;
    LinearEqn boiling_point;

  public:

    ChemicalComponent(std::string, double weight, double charge, double halflife, int Z, LinearEqn mp, LinearEqn bp);
    virtual ~ChemicalComponent();

    const std::string &get_name() const;
    double get_weight() const;
    double get_charge() const;
    int get_Z() const;
    bool is_radioactive() const;

    virtual Phase get_phase(double pressure, double temperature) const;

};

class CompositionSortByAbundance {

  public:
    bool operator()(std::pair<ChemicalComponent_ptr, double> left, std::pair<ChemicalComponent_ptr, double> right)
    {
      double aleft = left.second;
      double aright = right.second;
      return aleft < aright;
    }
};

class CompositionSortByAbundanceDescending {

  public:
    bool operator()(std::pair<ChemicalComponent_ptr, double> left, std::pair<ChemicalComponent_ptr, double> right)
    {
      double aleft = left.second;
      double aright = right.second;
      return aleft > aright;
    }
};
