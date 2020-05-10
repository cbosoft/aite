#pragma once

#include <memory>
#include <string>
#include <list>

#include "../types.hpp"
#include "chemical_component.hpp"

class Element : public virtual ChemicalComponent {

  private:

    std::string symbol;
    int number_electrons;
    double halflife;

  public:

    Element(std::string name, std::string symbol,
        int number_electrons, double molecular_weight, double halflife,
        LinearEqn boiling_point, LinearEqn melting_point);
    ~Element();

    int get_number_electrons() const;
    Phase get_phase(double pressure, double temperature) const override;
    bool is_radioactive() const;

    static std::list<std::pair<Element_ptr, double>> get_distribution(double density);
    static Element_ptr get_element_by_n(int n);

};


class ElementsSortByNumberElectrons {

  public:
    bool operator()(std::pair<Element_ptr, double> left, std::pair<Element_ptr, double> right)
    {
      double z_left = left.first->get_number_electrons();
      double z_right = right.first->get_number_electrons();
      return z_left < z_right;
    }
};
