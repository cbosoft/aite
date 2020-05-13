#include <string>
#include <sstream>

#include "../chemistry/element.hpp"
#include "../util/random.hpp"
#include "../util/thesaurus.hpp"
#include "../constants.hpp"

#include "planet.hpp"

static ChemicalComposition get_distribution(double density)
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

  ChemicalComposition dist;

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


SystemObject_ptr Planet::generate(System_ptr system, double position, double source_luminosity)
{
  auto planet = std::make_shared<Planet>(system, position);

  // diameter
  planet->object_diameter = bilognormal_rand(-8.5, 0.7, -7, 0.1, 0.8);
  planet->territory_diameter = planet->object_diameter;

  // densities
  planet->density = lognormal_rand(0.7, 1.0);

  // atmospheric pressure
  planet->pressure = lognormal_rand(-2, 1.0);
  double pfrac = (planet->pressure - std::exp(-6.5)) / (std::exp(2.5) - std::exp(-6.5));
  planet->greenhouse_effect = pfrac;

  // temperatures
  // TODO generate temperature from luminosity and reflectivity
  // http://www.astronomynotes.com/solarsys/s3c.htm
  planet->albedo = uniform_rand(0.0, 1.0);
  double posm = position*CONST_AUm;
  planet->temperature = std::pow(source_luminosity*(1.0 - planet->albedo)/(16.0*M_PI*CONST_STEFAN_BOLTZMANN*posm*posm), 0.25);

  // elements
  planet->composition = get_distribution(planet->density);
  planet->composition.sort(CompositionSortByAbundanceDescending());

  double planet_surface_area = planet->object_diameter*planet->object_diameter*CONST_AUm*CONST_AUm*M_PI;
  double prospectable_mass = planet_surface_area*1e3*5.583*planet->density;
  planet->resources = Resources(planet->composition, prospectable_mass);
  planet->resources.volume += planet_surface_area*2.2;
  planet->resources.luminosity += (1.0 - planet->albedo)*source_luminosity/(position*position);

  std::stringstream ss;
  ss << Thesaurus::getref().get_random_colour()
    << " and "
    << Thesaurus::getref().get_random_colour();
  if (planet->pressure > 0.5) {
    if (check_likelihood(Likelihood_Common)) {
      ss << ", with clouds of " << Thesaurus::getref().get_random_colour();
    }
  }
  planet->colour = ss.str();

  return planet;
}
