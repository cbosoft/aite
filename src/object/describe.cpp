#include <iostream>
#include <cmath>

#include "object.hpp"
#include "../chemistry/element.hpp"
#include "../constants.hpp"

const ObjectDescriptionData &SystemObject::describe()
{
  if (this->description_data.set)
    return this->description_data;

  this->description_data.diameter = this->object_diameter;

  this->description_data.density = this->density[3];
  this->description_data.gravitational_constant = CONST_G * this->density[3] * (1./6.) * M_PI * this->object_diameter * CONST_AUm;

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


  double avp = this->pressure[2];
  if (this->get_object_type() == SO_Planet)
  {
    if (avp < 0.01) {
      this->description_data.al = AL_None;
      this->description_data.pl = PL_Negligable;
    }
    else if (avp < 0.5) {
      this->description_data.al = AL_Thin;
      this->description_data.pl = PL_Low;
    }
    else if (avp < 1.5) {
      this->description_data.al = AL_EarthLike;
      this->description_data.pl = PL_Medium;
    }
    else if (avp < 10.0) {
      this->description_data.al = AL_Thick;
      this->description_data.pl = PL_High;
    }
    else {
      this->description_data.al = AL_Heavy;
      this->description_data.pl = PL_Crushing;
    }
  }
  else {
    this->description_data.al = AL_None;
    if (avp < 0.01) {
      this->description_data.pl = PL_Negligable;
    }
    else if (avp < 0.5) {
      this->description_data.pl = PL_Low;
    }
    else if (avp < 1.5) {
      this->description_data.pl = PL_Medium;
    }
    else if (avp < 10.0) {
      this->description_data.pl = PL_High;
    }
    else {
      this->description_data.pl = PL_Crushing;
    }
  }

  this->description_data.temperature = this->temperature[2];
  double t = this->temperature[2];
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
  this->description_data.apparent_composition = this->composition[2];
  this->description_data.set = true;

  return this->description_data;
}

