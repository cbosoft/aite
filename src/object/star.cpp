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

  // elements
  // TODO: special distribution for stars
  // star->composition = Element::get_distribution(star->density);
  // star->composition.sort(CompositionSortByAbundanceDescending());

  double H = normal_rand(90, 1);
  star->composition.push_back(std::make_pair(Element::get_element_by_n(1), H));
  star->composition.push_back(std::make_pair(Element::get_element_by_n(2), 100-H));

  double diam = star->object_diameter*CONST_AUm;
  double mass = (diam*diam*diam)*(1./6.)*M_PI*star->density;
  mass *= CONST_EARTH_DENSITY;
  star->temperature = 100*std::log(diam)*(1+(7*std::exp(-std::pow(1e7/diam, 0.5))));


  double star_surface_area = star->object_diameter*star->object_diameter*CONST_AUm*CONST_AUm*M_PI;
  double prospectable_mass = star_surface_area*1e3*5.583*star->density;
  star->resources = Resources(star->composition, prospectable_mass);
  star->resources.volume += star_surface_area*2.2;
  //star->resources.luminosity = (26.408441543105592*mass - 23.67060648655879)*normal_rand(1.0, 0.1);
  star->resources.luminosity = (diam/1.3927e9)*3.827e26;

  star->colour = "yellow";

  return star;
}
