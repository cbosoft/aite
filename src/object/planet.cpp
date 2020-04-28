#include <string>
#include <sstream>

#include "../chemistry/element.hpp"
#include "../util/random.hpp"
#include "../util/thesaurus.hpp"

#include "planet.hpp"


SystemObject_ptr Planet::generate(System_ptr system, double position)
{
  auto planet = std::make_shared<Planet>(system, position);

  // diameter
  planet->object_diameter = bilognormal_rand(-2.5, 0.7, 0.5, 0.6, 0.8);
  planet->territory_diameter = planet->object_diameter;

  // densities
  std::list<double> densities;
  for (int i = 0; i < 3; i++) {
    double rn = lognormal_rand(0.7, 1.0);
    while ( std::log(rn) > 7 ) {
      rn = lognormal_rand(0.7, 1.0);
    }
    densities.push_back(rn);
  }
  densities.sort();

  planet->density[0] = densities.front(); densities.pop_front();
  planet->density[1] = densities.front(); densities.pop_front();
  planet->density[2] = densities.front();

  planet->density[3] = (planet->density[0] + planet->density[1] + planet->density[2])/3.0;

  // atmospheric pressure
  double pressure_base = lognormal_rand(-2, 1.0);

  std::list<double> pressures;
  for (int i = 0; i < 3; i++)
    pressures.push_back(pressure_base * normal_rand(1.0, 0.3));
  pressures.sort();

  planet->pressure[0] = pressures.front(); pressures.pop_front(); // low
  planet->pressure[2] = pressures.front(); pressures.pop_front(); // average
  planet->pressure[1] = pressures.front(); // high

  // temperatures
  double base_temperature = std::abs(normal_rand(1100, 600));
  std::list<double> temperatures;
  for (int i = 0; i < 3; i++)
    temperatures.push_back(base_temperature * normal_rand(1.0, 0.1));
  temperatures.sort();

  planet->temperature[0] = temperatures.front(); temperatures.pop_front();
  planet->temperature[2] = temperatures.front(); temperatures.pop_front();
  planet->temperature[1] = temperatures.front();

  // elements
  for (unsigned int i = 0; i < planet->density.size() - 1; i++) {
    planet->composition[i] = Element::get_distribution(planet->density[i]);
    planet->composition[i].sort(CompositionSortByAbundanceDescending());
  }

  // TODO
  // generate resources

  std::stringstream ss;
  ss << Thesaurus::getref().get_random_colour()
    << " and "
    << Thesaurus::getref().get_random_colour();
  if (planet->pressure[2] > 0.5) {
    if (check_likelihood(Likelihood_Common)) {
      ss << ", with clouds of " << Thesaurus::getref().get_random_colour();
    }
  }
  planet->colour = ss.str();

  return planet;
}
