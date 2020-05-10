#pragma once

#include <memory>

#include "../types.hpp"
#include "../util/equation.hpp"

class ChemicalComponent {

  protected:

    std::string name;
    double weight;
    double charge;
    LinearEqn boiling_point;
    LinearEqn melting_point;

  public:

    ChemicalComponent(std::string, double, double);
    virtual ~ChemicalComponent();

    std::string get_name() const;
    double get_weight() const;
    double get_charge() const;
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
