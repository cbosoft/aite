#include <iostream>

#include "element.hpp"
#include "../util/random.hpp"

// TODO: planets are generally made of elements, but stars and the weirder parts
// of space can be composed of not much more than subatomic particles or
// smaller. This system needs to be reworked I think.


std::list<std::pair<std::shared_ptr<Element>, double>> Element::get_distribution(double density)
{

  std::array<double, 118> abundance;
  double nrho = (std::log(density) + 3.0)/9.0;
  int high_abundant_range_start = int(nrho*7.0/0.33) + uniform_rand_i(0, 3);
  int high_abundant_range_end = uniform_rand_i(5, 8) + int(13.0*nrho/0.33) + high_abundant_range_start;


  for (int z = 1; z <= 118; z++) {
    double a = 118.0 / double(z);

    if (z % 6) {
      a *= 4.0;
    }
    else if (z % 2) {
      a *= 2.0;
    }

    double mult = 1.0;
    if (z < high_abundant_range_start) {
      if (z < 3) {
        mult = 0.01/density;
      }
      else {
        mult = 0.1;
      }
    }
    else if (z >= 95) {
      mult = 1e-5*density;
    }
    else if (z > high_abundant_range_end) {
      mult = 1e-2;
    }

    a = a*mult;
    abundance[z-1] = a*uniform_rand(0.1, 10.0);

  }

  std::list<std::pair<std::shared_ptr<Element>, double>> dist;

  double total = 0.0;
  for (int i = 0; i < 118; i++)
    total += abundance[i];

  for (int i = 0; i < 118; i++) {
    if (abundance[i] <= 0) continue;
    auto elem = Element::get_element_by_n(i+1);
    auto pair = std::make_pair(elem, double(abundance[i]) / total);
    dist.push_back(pair);
  }

  return dist;
}
