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
  planet->density = lognormal_rand(0.7, 1.0);

  // atmospheric pressure
  planet->pressure = lognormal_rand(-2, 1.0);

  // temperatures
  planet->temperature = std::abs(normal_rand(1100, 600));

  // elements
  planet->composition = Element::get_distribution(planet->density);
  planet->composition.sort(CompositionSortByAbundanceDescending());

  // TODO
  // generate resources

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
