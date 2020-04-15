#include <iostream>

#include "element.hpp"
#include "../random/random.hpp"


std::list<std::pair<std::shared_ptr<Element>, double>> Element::get_distribution(double density)
{
  const double std = 10.0;
  const double mean_low = 0.0;
  const double mean_high = 55.0;
  const double dmean = mean_high - mean_low;
  const double logdens_low = -2.2;
  const double logdens_high = 3.9;
  const double drho = logdens_high - logdens_low;
  const double dmean_drho = dmean / drho;

  double reduced_log_density = std::log(density) - logdens_low;
  double mean = dmean_drho*reduced_log_density + mean_low;


  std::array<int, 118> hist;
  hist.fill(0);
  const int number_samples = 1000;
  for (int i = 0; i < number_samples; i++) {

    int n = 0.0;
    if (uniform_rand(0.0, 1.0) < 0.5) {
      n = std::round(normal_rand(mean, std));
    }
    else {
      n = std::round(normal_rand(mean, (std+mean)*2.0));
    }

    if (n < 0.0)
      n = std::abs(n) + mean;
    
    if (n > 117)
      n = 117 - (n % 117);

    hist[n]++;
  }

  std::list<std::pair<std::shared_ptr<Element>, double>> dist;

  for (int i = 0; i < 118; i++) {
    if (hist[i] == 0) continue;
    auto elem = Element::get_element_by_n(i+1);
    auto pair = std::make_pair(elem, double(hist[i]) / double(number_samples));
    dist.push_back(pair);
  }

  return dist;
}
