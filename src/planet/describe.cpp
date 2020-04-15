#include <iostream>
#include <cmath>

#include "planet.hpp"
#include "../element/element.hpp"
#include "../constants.hpp"

const PlanetDescriptionData &Planet::describe()
{
  if (this->description_data.set)
    return this->description_data;

  this->description_data.diameter = this->diameter;
  int logdia = std::round(std::log(this->diameter));
  if (logdia < -4) {
    this->description_data.sc = SC_Small;
  }
  else if (logdia < -3) {
    this->description_data.sc = SC_EarthLike;
  }
  else if (logdia < -1) {
    this->description_data.sc = SC_Large;
  }
  else if (logdia < 2) {
    this->description_data.sc = SC_Huge;
  }
  else {
    this->description_data.sc = SC_Giant;
  }

  this->description_data.density = this->density_average;
  this->description_data.gravitational_constant = CONST_G * this->density_average * (1./6.) * M_PI * this->diameter * CONST_AUm;

  if (this->description_data.gravitational_constant < 0.001) {
    this->description_data.gl = GL_NonExistant;
  }
  else if (this->description_data.gravitational_constant < 0.5) {
    this->description_data.gl = GL_Weak;
  }
  else if (this->description_data.gravitational_constant < 2.0) {
    this->description_data.gl = GL_Normal;
  }
  else if (this->description_data.gravitational_constant < 5.0) {
    this->description_data.gl = GL_Heavy;
  }
  else if (this->description_data.gravitational_constant < 10.0) {
    this->description_data.gl = GL_Oppressive;
  }
  else { // if (this->description_data.gravitational_constant < 100.0) {
    this->description_data.gl = GL_SpineCrushing;
  }


  if (this->pressure_average < 0.01) {
    this->description_data.al = AL_None;
  }
  else if (this->pressure_average < 0.5) {
    this->description_data.al = AL_Thin;
  }
  else if (this->pressure_average < 1.5) {
    this->description_data.al = AL_EarthLike;
  }
  else if (this->pressure_average < 10.0) {
    this->description_data.al = AL_Thick;
  }
  else {
    this->description_data.al = AL_Heavy;
  }

  double pdiff = (this->pressure_high - this->pressure_low) / this->pressure_average;
  int wl = std::round(std::log(pdiff*10.0));
  if (wl < 1) {
    this->description_data.wl = WL_None;
  }
  else if (wl < 2) {
    this->description_data.wl = WL_Negligable;
  }
  else if (wl < 3) {
    this->description_data.wl = WL_Strong;
  }
  else if (wl < 4) {
    this->description_data.wl = WL_Gale;
  }
  else {
    this->description_data.wl = WL_Ferocious;
  }


  this->description_data.temperature = this->temp_average;
  double t = this->temp_average;
  if (t < 10) {
    this->description_data.tl = TL_NearAbsoluteZero;
  }
  else if (t < 100) {
    this->description_data.tl = TL_ExtremeCold;
  }
  else if (t < 250) {
    this->description_data.tl = TL_VeryCold;
  }
  else if (t < 270) {
    this->description_data.tl = TL_Cold;
  }
  else if (t < 310) {
    this->description_data.tl = TL_Temperate;
  }
  else if (t < 370) {
    this->description_data.tl = TL_Hot;
  }
  else if (t < 500) {
    this->description_data.tl = TL_VeryHot;
  }
  else if (t < 1000) {
    this->description_data.tl = TL_ExtremeHeat;
  }
  else {
    this->description_data.tl = TL_Scorching;
  }
  this->description_data.apparent_composition = this->composition_surface;
  this->description_data.set = true;

  return this->description_data;
}
