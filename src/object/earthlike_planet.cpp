#include <string>
#include <sstream>

#include "../chemistry/element.hpp"
#include "../util/random.hpp"
#include "../util/thesaurus.hpp"

#include "planet.hpp"


SystemObject_ptr EarthlikePlanet::generate(System_ptr system, double position)
{
  auto planet = std::make_shared<EarthlikePlanet>(system, position);

  // diameter
  planet->object_diameter = 0.1 * normal_rand(1.0, 0.1);
  planet->territory_diameter = planet->object_diameter;

  planet->density = normal_rand(1.0, 0.05);
  planet->pressure = normal_rand(1.0, 0.1);
  planet->temperature = normal_rand(310, 10.0);

  // elements
  planet->composition = Element::get_distribution(planet->density);
  planet->composition.sort(CompositionSortByAbundanceDescending());

  // TODO
  // resources

  std::stringstream ss;
  ss << Thesaurus::getref().get_random_colour()
    << " and "
    << Thesaurus::getref().get_random_colour();
  if (planet->pressure > 0.5) {
    if (check_likelihood(Likelihood_Common)) {
      ss << " with clouds of " << Thesaurus::getref().get_random_colour();
    }
  }
  planet->colour = ss.str();

  return planet;
}

