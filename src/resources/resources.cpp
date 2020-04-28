#include <limits>

#include "../chemistry/element.hpp"
#include "resources.hpp"

#define BETWEEN(L,U) ((L < Z) && (Z < U))

Resources::Resources()
{
  // do nothing
}

Resources::Resources(ElementalAbundance elements, double mass)
{

  for (auto kv: elements) {
    auto elem = kv.first;
    double mass_element = mass * kv.second;

    int Z = elem->get_number_electrons();
    if (elem->is_radioactive() && (Z > 85)) {
      this->high_activity_ore += mass_element;
    }

    if ((Z == 1) or (Z == 4) or (Z == 8) or (Z == 15) or (Z == 9) or (Z == 19)) {
      this->OCHNPS += mass_element;
    }
    else if (BETWEEN(2,5) or BETWEEN(10,14) or 
        BETWEEN(18,33) or BETWEEN(36,52) or 
        BETWEEN(54,85) or BETWEEN(86,118)) {
      if (elem->get_molecular_weight() > 200) {
        this->high_density_ore += mass_element;
      }
      else {
        this->metallic_ore += mass_element;
      }
    }
    else {
      this->nonmetallic_ore += mass_element;
    }

  }

}
