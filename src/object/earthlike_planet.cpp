#include "planet.hpp"
#include "../chemistry/element.hpp"
#include "../util/random.hpp"


SystemObject_ptr EarthlikePlanet::generate(System_ptr system, double position)
{
  auto planet = std::make_shared<EarthlikePlanet>(system, position);

  // diameter
  planet->object_diameter = 0.1 * normal_rand(1.0, 0.1);
  planet->territory_diameter = planet->object_diameter;

  // densities
  std::list<double> densities;
  for (int i = 0; i < 4; i++) {
    double rn = normal_rand(1.0, 0.05);
    densities.push_back(rn);
  }
  densities.sort();

  double tot = 0.0;
  for (unsigned int i = 0; i < planet->density.size() - 1; i++) {
    planet->density[i] = densities.front(); densities.pop_front();
    tot += planet->density[i];
  }
  planet->density[3] = tot/double(planet->density.size() - 1);

  // atmospheric pressure
  double pressure_base = normal_rand(1.0, 0.1);

  std::list<double> pressures;
  for (int i = 0; i < 3; i++)
    pressures.push_back(pressure_base * normal_rand(1.0, 0.3));
  pressures.sort();

  planet->pressure[0] = pressures.front(); pressures.pop_front(); // low
  planet->pressure[2] = pressures.front(); pressures.pop_front(); // average
  planet->pressure[1] = pressures.front(); // high

  // temperatures
  double base_temperature = normal_rand(310, 10.0);
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

  return planet;
}

