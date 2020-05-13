#pragma once

#include <memory>
#include <string>
#include <list>

#include "../types.hpp"
#include "chemical_component.hpp"

class Element : public virtual ChemicalComponent {

  private:

    std::string symbol;

  public:

    Element(std::string name, std::string symbol,
        int number_electrons, double molecular_weight, double halflife,
        LinearEqn boiling_point, LinearEqn melting_point);
    ~Element();

    static Element_ptr get_element_by_n(int n);

};


class ElementsSortByNumberElectrons {

  public:
    bool operator()(std::pair<Element_ptr, double> left, std::pair<Element_ptr, double> right)
    {
      double z_left = left.first->get_Z();
      double z_right = right.first->get_Z();
      return z_left < z_right;
    }
};
