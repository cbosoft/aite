#include "element.hpp"
#include "../random/random.hpp"


std::list<std::pair<std::shared_ptr<Element>, double>> Element::get_distribution(double density)
{
  const double lambda_min = 2.0;
  const double logdens_low = -2.2;
  const double logdens_high = 3.9;
  const double drho = logdens_high - logdens_low;

  double dstd_drho = 5.0 / drho;
  double reduced_log_density = std::log(density) - logdens_low;
  double lambda = dstd_drho*reduced_log_density + lambda_min;


  std::array<int, 118> hist;
  hist.fill(0);
  for (int i = 0; i < 1000; i++) {
    int n = std::abs(std::round(normal_rand(20, lambda)));
    if (n > 117)
      n = 117 - (n % 117);

    if (uniform_rand(0.0, 1.0) < 0.5)
      hist[n]++;
    else
      i--;
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
