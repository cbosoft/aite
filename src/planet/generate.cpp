#include "planet.hpp"
#include "../random/random.hpp"

std::shared_ptr<Planet> Planet::generate()
{
  auto planet = std::make_shared<Planet>();

  // diameter
  planet->diameter = bilognormal_rand(-2.5, 0.7, 0.5, 0.6, 0.8);

  // densities
  std::list<double> densities;
  for (int i = 0; i < 4; i++) {
    double rn = lognormal_rand(0.7, 1.0);
    while ( std::log(rn) > 7 ) {
      rn = lognormal_rand(0.7, 1.0);
    }
    densities.push_back(rn);
  }
  densities.sort();

  planet->density_core = densities.front();
  densities.pop_front();
  planet->density_mantle = densities.front();
  densities.pop_front();
  planet->density_deep = densities.front();
  densities.pop_front();
  planet->density_surface = densities.front();

  planet->density_average = (planet->density_core + 
      planet->density_mantle + planet->density_deep + 
      planet->density_surface)*0.25;

  // atmospheric pressure
  double pressure_base = lognormal_rand(-2, 1.0);

  std::list<double> pressures;
  for (int i = 0; i < 3; i++)
    pressures.push_back(pressure_base * normal_rand(1.0, 0.3));
  pressures.sort();

  planet->pressure_low = pressures.front();
  planet->pressure_average = pressures.front();
  planet->pressure_high = pressures.front();

  // temperatures
  double base_temperature = std::abs(normal_rand(1100, 600));
  std::list<double> temperatures;
  for (int i = 0; i < 3; i++)
    temperatures.push_back(base_temperature * normal_rand(1.0, 0.1));
  temperatures.sort();
  planet->temp_low = temperatures.front();
  temperatures.pop_front();
  planet->temp_average = temperatures.front();
  temperatures.pop_front();
  planet->temp_high = temperatures.front();

  return planet;
}
