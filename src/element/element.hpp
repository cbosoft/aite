#pragma once

#include <memory>
#include <string>
#include <list>

enum ElementPhase { PhaseSolid, PhaseLiquid, PhaseGas, PhasePlasma };

class Element {

  private:
    int number_electrons;
    double molecular_weight;
    std::string name, symbol;

  public:

    Element(std::string name, std::string symbol, int number, double weight);
    ~Element();

    bool is_reactive() const;
    ElementPhase get_phase(double temperature, double pressure) const;

    static std::list<std::pair<std::shared_ptr<Element>, double>> get_distribution(double density);
    static std::shared_ptr<Element> get_element_by_n(int n);

};

