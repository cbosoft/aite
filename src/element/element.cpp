#include "element.hpp"
#include "../random/random.hpp"

#define E(name, symbol, electrons, weight) std::make_shared<Element>(Element(name, symbol, electrons, weight))

static std::array<std::shared_ptr<Element>, 118> table = {
  E("Hydrogen",     "H",   1,   1.0),
  E("Helium",       "He",  2,   4.0),
  E("Lithium",      "Li",  3,   6.9),
  E("Beryllium",    "Be",  4,   9.0),
  E("Boron",        "B",   5,  10.8),
  E("Carbon",       "C",   6,  12.0),
  E("Nitrogen",     "N",   7,  14.0),
  E("Oxygen",       "O",   8,  16.0),
  E("Flourine",     "F",   9,  19.0),

  E("Neon",         "Ne", 10,  20.2),
  E("Sodium",       "Na", 11,  23.0),
  E("Magnesium",    "Mg", 12,  24.3),
  E("Aluminium",    "Al", 13,  27.0),
  E("Silicon",      "Si", 14,  28.1),
  E("Phosphorous",  "P",  15,  31.0),
  E("Sulphur",      "S",  16,  32.1),
  E("Chlorine",     "Cl", 17,  35.5),
  E("Argon",        "Ar", 18,  40.0),
  E("Potassium",    "K",  19,  39.1),

  E("Calcium",      "Ca", 20,  40.1),
  E("Scandium",     "Sc", 21,  45.0),
  E("Titanium",     "Ti", 22,  47.9),
  E("Vanadium",     "V",  23,  50.9),
  E("Chromium",     "Cr", 24,  52.0),
  E("Manganses",    "Mn", 25,  54.9),
  E("Iron",         "Fe", 26,  55.8),
  E("Cobalt",       "Co", 27,  58.9),
  E("Nickel",       "Ni", 28,  58.7),
  E("Copper",       "Cu", 29,  63.5),

  E("Zinc", "Zn", 30, 1),
  E("hydrogen", "h", 31, 1),
  E("hydrogen", "h", 32, 1),
  E("hydrogen", "h", 33, 1),
  E("hydrogen", "h", 34, 1),
  E("hydrogen", "h", 35, 1),
  E("hydrogen", "h", 36, 1),
  E("hydrogen", "h", 37, 1),
  E("hydrogen", "h", 38, 1),
  E("hydrogen", "h", 39, 1),

  E("hydrogen", "h", 40, 1),
  E("hydrogen", "h", 41, 1),
  E("hydrogen", "h", 42, 1),
  E("hydrogen", "h", 43, 1),
  E("hydrogen", "h", 44, 1),
  E("hydrogen", "h", 45, 1),
  E("hydrogen", "h", 46, 1),
  E("hydrogen", "h", 47, 1),
  E("hydrogen", "h", 48, 1),
  E("hydrogen", "h", 49, 1),

  E("hydrogen", "h", 50, 1),
  E("hydrogen", "h", 51, 1),
  E("hydrogen", "h", 52, 1),
  E("hydrogen", "h", 53, 1),
  E("hydrogen", "h", 54, 1),
  E("hydrogen", "h", 55, 1),
  E("hydrogen", "h", 56, 1),
  E("hydrogen", "h", 57, 1),
  E("hydrogen", "h", 58, 1),
  E("hydrogen", "h", 59, 1),

  E("hydrogen", "h", 60, 1),
  E("hydrogen", "h", 61, 1),
  E("hydrogen", "h", 62, 1),
  E("hydrogen", "h", 63, 1),
  E("hydrogen", "h", 64, 1),
  E("hydrogen", "h", 65, 1),
  E("hydrogen", "h", 66, 1),
  E("hydrogen", "h", 67, 1),
  E("hydrogen", "h", 68, 1),
  E("hydrogen", "h", 69, 1),

  E("hydrogen", "h", 70, 1),
  E("hydrogen", "h", 71, 1),
  E("hydrogen", "h", 72, 1),
  E("hydrogen", "h", 73, 1),
  E("hydrogen", "h", 74, 1),
  E("hydrogen", "h", 75, 1),
  E("hydrogen", "h", 76, 1),
  E("hydrogen", "h", 77, 1),
  E("hydrogen", "h", 78, 1),
  E("hydrogen", "h", 79, 1),

  E("hydrogen", "h", 80, 1),
  E("hydrogen", "h", 81, 1),
  E("hydrogen", "h", 82, 1),
  E("hydrogen", "h", 83, 1),
  E("hydrogen", "h", 84, 1),
  E("hydrogen", "h", 85, 1),
  E("hydrogen", "h", 86, 1),
  E("hydrogen", "h", 87, 1),
  E("hydrogen", "h", 88, 1),
  E("hydrogen", "h", 89, 1),

  E("hydrogen", "h", 90, 1),
  E("hydrogen", "h", 91, 1),
  E("hydrogen", "h", 92, 1),
  E("hydrogen", "h", 93, 1),
  E("hydrogen", "h", 94, 1),
  E("hydrogen", "h", 95, 1),
  E("hydrogen", "h", 96, 1),
  E("hydrogen", "h", 97, 1),
  E("hydrogen", "h", 98, 1),
  E("hydrogen", "h", 99, 1),

  E("hydrogen", "h", 100, 1),
  E("hydrogen", "h", 101, 1),
  E("hydrogen", "h", 102, 1),
  E("hydrogen", "h", 103, 1),
  E("hydrogen", "h", 104, 1),
  E("hydrogen", "h", 105, 1),
  E("hydrogen", "h", 106, 1),
  E("hydrogen", "h", 107, 1),
  E("hydrogen", "h", 108, 1),
  E("hydrogen", "h", 109, 1),

  E("hydrogen", "h", 110, 1),
  E("hydrogen", "h", 111, 1),
  E("hydrogen", "h", 112, 1),
  E("hydrogen", "h", 113, 1),
  E("hydrogen", "h", 114, 1),
  E("hydrogen", "h", 115, 1),
  E("hydrogen", "h", 116, 1),
  E("hydrogen", "h", 117, 1),
  E("hydrogen", "h", 118, 1),
};




Element::Element(std::string name, std::string symbol, int number_electrons, double molecular_weight)
{
  this->name = name;
  this->symbol = symbol;
  this->number_electrons = number_electrons;
  this->molecular_weight = molecular_weight;
}

Element::~Element()
{
  // do nothing
}


std::shared_ptr<Element> Element::get_element_by_n(int n)
{
  return table[n-1];
}


std::list<std::pair<std::shared_ptr<Element>, double>> Element::get_distribution(double density)
{
  const double nelem = 118.0;
  const double std = 30.0;
  double dn_drho = 0.7 * nelem / 5.2;
  double mean = dn_drho * std::log(density) + 1;


  std::array<int, 118> hist;
  for (int i = 0; i < 1000; i++) {
    int n = std::abs(std::round(normal_rand(mean, std)));
    if (n > 117)
      n = (2*117) - n;
    hist[n]++;
  }

  std::list<std::pair<std::shared_ptr<Element>, double>> dist;

  for (int i = 0; i < 118; i++) {
    if (hist[i] == 0) continue;
    auto elem = Element::get_element_by_n(i+1);
    auto pair = std::make_pair(elem, double(hist[i])*0.001);
    dist.push_back(pair);
  }

  return dist;
}
