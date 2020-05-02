#include <string>
#include <sstream>

#include "../chemistry/element.hpp"
#include "../util/random.hpp"
#include "../util/thesaurus.hpp"
#include "../constants.hpp"

#include "star.hpp"


SystemObject_ptr Star::generate(System_ptr system, double position)
{
  auto star = std::make_shared<Star>(system, position);

  // diameter
  star->object_diameter = lognormal_rand(1.0, 0.3)*CONST_SOLDIA_AU;
  star->territory_diameter = star->object_diameter;

  // densities
  star->density = lognormal_rand(0.7, 1.0)*0.2;

  // atmospheric pressure
  star->pressure = lognormal_rand(-4, 1.0);

  // temperatures
  // TODO better estimation of temperature, perhaps linked to mass?
  star->temperature = std::abs(normal_rand(10000, 1000));

  // elements
  // TODO: special distribution for stars
  star->composition = Element::get_distribution(star->density);
  star->composition.sort(CompositionSortByAbundanceDescending());


  double mass = star->object_diameter*star->object_diameter*star->object_diameter*(1./6.)*M_PI*star->density;
  star->resources.luminosity = (26.408441543105592*mass - 23.67060648655879)*normal_rand(1.0, 0.1);
  double star_surface_area = star->object_diameter*star->object_diameter*CONST_AUm*CONST_AUm*M_PI;
  double prospectable_mass = star_surface_area*1e3*5.583*star->density;
  star->resources = Resources(star->composition, prospectable_mass);
  star->resources.volume += star_surface_area*2.2;

  star->colour = "yellow";

  return star;
}
