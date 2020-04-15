#include "element.hpp"
#include "../random/random.hpp"

#define E(name, symbol, electrons, weight) std::make_shared<Element>(Element(name, symbol, electrons, weight))

static std::array<std::shared_ptr<Element>, 118> table = {
  E("Hydrogen",      "H",   1,   1.0),
  E("Helium",        "He",  2,   4.0),
  E("Lithium",       "Li",  3,   6.9),
  E("Beryllium",     "Be",  4,   9.0),
  E("Boron",         "B",   5,  10.8),
  E("Carbon",        "C",   6,  12.0),
  E("Nitrogen",      "N",   7,  14.0),
  E("Oxygen",        "O",   8,  16.0),
  E("Flourine",      "F",   9,  19.0),

  E("Neon",          "Ne", 10,  20.2),
  E("Sodium",        "Na", 11,  23.0),
  E("Magnesium",     "Mg", 12,  24.3),
  E("Aluminium",     "Al", 13,  27.0),
  E("Silicon",       "Si", 14,  28.1),
  E("Phosphorous",   "P",  15,  31.0),
  E("Sulphur",       "S",  16,  32.1),
  E("Chlorine",      "Cl", 17,  35.5),
  E("Argon",         "Ar", 18,  40.0),
  E("Potassium",     "K",  19,  39.1),

  E("Calcium",       "Ca", 20,  40.1),
  E("Scandium",      "Sc", 21,  45.0),
  E("Titanium",      "Ti", 22,  47.9),
  E("Vanadium",      "V",  23,  50.9),
  E("Chromium",      "Cr", 24,  52.0),
  E("Manganses",     "Mn", 25,  54.9),
  E("Iron",          "Fe", 26,  55.8),
  E("Cobalt",        "Co", 27,  58.9),
  E("Nickel",        "Ni", 28,  58.7),
  E("Copper",        "Cu", 29,  63.5),

  E("Zinc",          "Zn", 30,  65.4),
  E("Gallium",       "Ga", 31,  69.7),
  E("Germanum",      "Ge", 32,  72.6),
  E("Arsenic",       "As", 33,  74.9),
  E("Selenium",      "Se", 34,  79.0),
  E("Bromine",       "Br", 35,  79.9),
  E("Krypton",       "Kr", 36,  83.8),
  E("Rubidium",      "Rb", 37,  85.5),
  E("Strontium",     "Sr", 38,  87.6),
  E("Yttrium",       "Y",  38,  88.9),

  E("Zirconium",     "Zr", 40,  91.2),
  E("Niobium",       "Nb", 41,  92.9),
  E("Molybdenum",    "Mo", 42,  96.0),
  E("Technetium",    "Tc", 43,  98.9),
  E("Ruthenium",     "Ru", 44, 101.7),
  E("Rhodium",       "Rh", 45, 102.9),
  E("Palladium",     "Pd", 46, 106.4),
  E("Silver",        "Ag", 47, 107.9),
  E("Cadmium",       "Cd", 48, 112.4),
  E("Indium",        "In", 49, 114.8),

  E("Tin",           "Sn", 50, 118.7),
  E("Antimony",      "Sb", 51, 121.8),
  E("Tellurium",     "Te", 52, 127.6),
  E("Iodine",        "I", 53,  126.9),
  E("Xenon",         "Xe", 54, 131.3),
  E("Caesium",       "Cs", 55, 132.9),
  E("Barium",        "Ba", 56, 137.3),
  E("Lanthanum",     "La", 57, 138.9),
  E("Cerium",        "Ce", 58, 140.1),
  E("Praseodymium",  "Pr", 59, 140.9),

  E("Neodymium",     "Nd", 60, 144.2),
  E("Promethium",    "Pm", 61, 144.9),
  E("Samarium",      "Sm", 62, 150.4),
  E("Europium",      "Eu", 63, 152.0),
  E("Gadolinium",    "Gd", 64, 157.3),
  E("Terbium",       "Tb", 65, 158.9),
  E("Dysprosium",    "Dy", 66, 162.5),
  E("Holmium",       "Ho", 67, 164.9),
  E("Erbium",        "Er", 68, 167.3),
  E("Thulium",       "Tm", 69, 168.9),

  E("Ytterbium",     "Yb", 70, 173.6),
  E("Lutetium",      "Lu", 71, 174.9),
  E("Hafnium",       "Hf", 72, 178.5),
  E("Tantalum",      "Ta", 73, 180.9),
  E("Tungsten",      "W", 74,  183.8),
  E("Rhenium",       "Re", 75, 186.2),
  E("Osmium",        "Os", 76, 190.2),
  E("Iridium",       "Ir", 77, 192.2),
  E("Platinum",      "Pt", 78, 195.1),
  E("Gold",          "Au", 79, 197.0),

  E("Mercury",       "Hg", 80, 200.6),
  E("Thallium",      "Tl", 81, 204.4),
  E("Lead",          "Pb", 82, 207.2),
  E("Bismuth",       "Bi", 83, 209.0),
  E("Polonium",      "Po", 84, 209.0),
  E("Astatine",      "At", 85, 210.0),
  E("Radon",         "Rn", 86, 222.0),
  E("Francium",      "Fr", 87, 223.0),
  E("Radium",        "Ra", 88, 226.0),
  E("Actinium",      "Ac", 89, 227.0),

  E("Thorium",       "h", 90, 232.0),
  E("Protactinium",  "h", 91, 231.0),
  E("Uranium",       "h", 92, 238.0),
  E("Neptunium",     "h", 93, 237.0),
  E("Plutonium",     "h", 94, 244.1),
  E("Americium",     "h", 95, 243.1),
  E("Curium",        "h", 96, 247.1),
  E("Berkelium",     "h", 97, 247.1),
  E("Californium",   "h", 98, 251.1),
  E("Einsteinium",   "h", 99, 245.0),

  E("Fermium",       "h", 100, 257.1),
  E("Mendelevium",   "h", 101, 258.1),
  E("Nobelium",      "h", 102, 259.1),
  E("Lawrencium",    "h", 103, 262.0),
  E("Rutherfordium", "h", 104, 261.0),
  E("Dubnium",       "h", 105, 262.0),
  E("Seaborgium",    "h", 106, 266.0),
  E("Bohrium",       "h", 107, 264.0),
  E("Hassium",       "h", 108, 269.0),
  E("Meitnerium",    "h", 109, 278.0),

  E("Darmstadtium",  "h", 110, 281.0),
  E("Roentgenum",    "h", 111, 280.0),
  E("Copernicum",    "h", 112, 285.0),
  E("Nihonium",      "h", 113, 286.0),
  E("Flerovium",     "h", 114, 289.0),
  E("Moscovium",     "h", 115, 289.0),
  E("Livermorium",   "h", 116, 293.0),
  E("Tennessine",    "h", 117, 294.0),
  E("Oganesson",     "h", 118, 294.0),
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
  const double std = 30.0;
  const double std_min = 30.0;
  const double drho = 3.9 - (-2.2);

  double dstd_drho = 40.0 / drho;
  double mean = dstd_drho * std::log(density) + std_min;


  std::array<int, 118> hist;
  for (int i = 0; i < 1000; i++) {
    int n = std::abs(std::round(normal_rand(mean, std)));
    if (n > 117)
      n = 117 - (n % 117);
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
