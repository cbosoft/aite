#pragma once

#include <memory>
#include <string>
#include <list>

enum Phase { PhaseSolid, PhaseLiquid, PhaseGas, PhasePlasma };

class Element {

  private:
    std::string name, symbol;
    int number_electrons;
    double molecular_weight;
    double covalent_radius;
    double boiling_point_m, melting_point_m;

  public:

    Element(std::string name, std::string symbol, int number_electrons, double molecular_weight, double covalent_radius, double boiling_point_m, double melting_point_m);
    ~Element();

    int get_number_electrons() const;
    std::list<double> get_emission_spectrum();
    double get_boiling_point(double pressure, double temperature) const;
    double get_melting_point(double pressure, double temperature) const;
    Phase get_phase(double pressure, double temperature) const;
    std::string get_name() const;

    static std::list<std::pair<std::shared_ptr<Element>, double>> get_distribution(double density);
    static std::shared_ptr<Element> get_element_by_n(int n);

};


class CompositionSortByAbundance {

  public:
    bool operator()(std::pair<std::shared_ptr<Element>, double> left, std::pair<std::shared_ptr<Element>, double> right)
    {
      double aleft = left.second;
      double aright = right.second;
      return aleft < aright;
    }
};

class CompositionSortByAbundanceDescending {

  public:
    bool operator()(std::pair<std::shared_ptr<Element>, double> left, std::pair<std::shared_ptr<Element>, double> right)
    {
      double aleft = left.second;
      double aright = right.second;
      return aleft > aright;
    }
};


class CompositionSortByNumberElectrons {

  public:
    bool operator()(std::pair<std::shared_ptr<Element>, double> left, std::pair<std::shared_ptr<Element>, double> right)
    {
      double z_left = left.first->get_number_electrons();
      double z_right = right.first->get_number_electrons();
      return z_left < z_right;
    }
};
