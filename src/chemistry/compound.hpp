#pragma once

#include <map>
#include <initializer_list>

#include "../types.hpp"
#include "element.hpp"


class Compound {

  private:

    std::list<std::pair<Element_ptr, int>> form;

  public:

    Compound(std::initializer_list<std::pair<Element_ptr, int>> form);
    ~Compound();

    double get_boiling_point(double pressure, double temperature) const;
    double get_melting_point(double pressure, double temperature) const;
    Phase get_phase(double pressure, double temperature) const;
    std::string get_name() const;

    static std::list<std::pair<Compound_ptr, double>> get_probable_compounds(std::list<std::pair<Element_ptr, double>> elemental_composition);

};
