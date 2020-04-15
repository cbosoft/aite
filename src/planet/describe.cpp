#include <iomanip>
#include <sstream>
#include <cmath>

#include "planet.hpp"
#include "../element/element.hpp"

std::string Planet::describe() const
{

  int atmosphere = -1, temperature = -1, gravity = -1;
  //bool has_hydrogen, has_carbon, has_oxygen, has_nitrogen, has_water;
  int weather_storms = 0;//, weather_rains = 0;

  const double G = 6.67408e-11;
  const double AU2m = 1.496e11;
  double g = G * this->density_average * (1./6.) * M_PI * this->diameter * AU2m;

  if (g < 0.001) {
    gravity = 0;
  }
  else if (g < 0.1) {
    gravity = 1; // too weak
  }
  else if (g < 1.0) {
    gravity = 2; // weak, but manageable
  }
  else if (g < 3.0) {
    gravity = 3; // ideal
  }
  else if (g < 10.0) {
    gravity = 4; // heavy
  }
  else if (g < 100.0) {
    gravity = 5; // spine-crushing
  }
  else {
    gravity = 6; // smoosh
  }


  if (this->pressure_average > 10.0) {
    atmosphere = 6;
  }
  else if (this->pressure_average > 5.0) {
    atmosphere = 5;
  }
  else if (this->pressure_average > 1.5) {
    atmosphere = 4;
  }
  else if (this->pressure_average > 0.5) {
    atmosphere = 3;
    double pdiff = (this->pressure_high - this->pressure_low) / this->pressure_average;
    if (pdiff > 0.1) {
      weather_storms = std::round(std::log(pdiff*100.0));
    }
    else {
      weather_storms = 0.0;
    }
  }
  else if (this->pressure_average > 0.1) {
    atmosphere = 2;
  }
  else if (this->pressure_average > 0.01) {
    atmosphere = 1;
  }
  else {
    atmosphere = 0;
  }

  double t = this->temp_average;
  if (t < 10) {
    temperature = 0; // extreme cold
  }
  else if (t < 100) {
    temperature = 1; // not as extreme, but not much better
  }
  else if (t < 250) {
    temperature = 2; // darn cold!
  }
  else if (t < 270) {
    temperature = 3; // uncomfortably low, but doable
  }
  else if (t < 310) {
    temperature = 4; // ideal!
  }
  else if (t < 370) {
    temperature = 5; // uncomfortably high, but doable
  }
  else if (t < 500) {
    temperature = 6; // some soft materials melt. water is gaseous.
  }
  else if (t < 1000) {
    temperature = 7; // hot!
  }
  else {
    temperature = 8;
  }




  std::stringstream ss;

  ss << std::setprecision(1) << std::fixed
    << "This planet has a diameter of " 
    << this->diameter 
    << " AU and a density " << this->density_average 
    << " times Earth's. This results in a";

  switch (gravity) {

    case 0:
      ss << "n almost none existant";
      break;

    case 1:
      ss << " very weak";
      break;

    case 2:
      ss << " weak";
      break;

    case 3:
      ss << "n Earth-like";
      break;

    case 4:
      ss << " opressive";
      break;

    case 5:
      ss << " spine-crushing";
      break;

    case 6:
      ss << " insurmountable";
      break;
  }

  ss << " gravitational field (g = " << g << "). ";

  if (atmosphere) {
    ss << "The planet has a";

    switch (atmosphere) {
      case 1:
        ss << " very thin";
        break;

      case 2:
        ss << " thin";
        break;

      case 3:
        ss << "n ";
        break;

      case 4:
        ss << " thick";
        break;

      case 5:
        ss << " very thick";
        break;

      case 6:
        ss << "n almost liquid";
        break;
    }

    ss << " atmosphere";

    if ((atmosphere >= 2) and (atmosphere <= 4)) {
      ss << " that could potentially support life";
    }
    ss << ". ";

    // weather/wind
    ss << "Pressure differentials indicate";
    switch (weather_storms) {

      case 0:
        ss << " there is little wind";
        break;

      case 1:
        ss << " mild winds akin to that on Earth";
        break;

      case 2:
        ss << " strong winds, storms uncommon on Earth";
        break;

      case 3:
      case 4:
      case 5:
        ss << " incredible winds, strong enough to tear down structures";
        break;

      case 6:
      case 7:
        ss << " unrelenting harsh winds and storms bombarding the surface";
        break;

    }
    ss << ". ";

  }

  ss << "Average surface temperature is " << this->temp_average << "K; ";
  switch(temperature) {

    case 0:
      ss << "not far from absolute zero.";
      break;

    case 1:
      ss << "where most elements are solid.";
      break;

    case 2:
      ss << "almost inhospitably cold.";
      break;

    case 3:
      ss << "very cold.";
      break;

    case 4:
      ss << "temperate.";
      break;

    case 5:
      ss << "hot.";
      break;

    case 6:
      ss << "extremely hot.";
      break;

    case 7:
      ss << "scorching.";
      break;

    case 8:
      ss << "many materials warp and deform under these temperatures.";
      break;
  }

  // TODO check out elements and see what compounds are likely
  ss << "\n\nSpectral emissions indicate the presence of:\n";
  for (auto element_abundance_pair : this->composition_surface) {
    auto element = element_abundance_pair.first;
    double abundance = element_abundance_pair.second;
    double perc = abundance * 100.0;

    ss << "  - " << element->get_name() << " (" << perc << "%)\n";
  }


  // TODO check if planet has life

  return ss.str();
}
