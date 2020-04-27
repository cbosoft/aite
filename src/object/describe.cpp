#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#include "../util/formatter.hpp"
#include "../chemistry/element.hpp"
#include "../constants.hpp"

#include "object.hpp"

struct PhaseCompFunctor {
  bool operator()(std::pair<double, Phase> left, std::pair<double, Phase> right) {
    return left.first > right.first;
  }
} phase_comp_functor;

std::string phase2str(Phase p)
{
  std::string rv;
  switch (p) {

    case PhaseSolid:
      rv = "solid";
      break;

    case PhaseLiquid:
      rv = "liquid";
      break;

    case PhaseGas:
      rv = "gas";
      break;

    case PhasePlasma:
      rv = "plasma";
      break;

  }
  return rv;
}

const ObjectDescriptionData &SystemObject::describe()
{
  if (this->description_data.set)
    return this->description_data;

  this->description_data.diameter = this->object_diameter;
  int logdia = std::round(std::log10(this->object_diameter));
  if (logdia < -4) {
    this->description_data.sc = SC_Small;
  }
  else if (logdia < -3) {
    this->description_data.sc = SC_EarthSized;
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
  std::vector<std::pair<double, Phase>> phase_abundance;
  for (int i = 0; i < 4; i++)
    phase_abundance.push_back(std::make_pair(double(0.0), Phase(i)));

  constexpr int N_MOST_ABUNDANT = 3;
  std::string most_abundant [N_MOST_ABUNDANT];
  {
    int i = 0;
    for (auto kv : this->composition[2]) {

      auto elem = kv.first;
      auto amount = kv.second;
      Phase phase = elem->get_phase(this->pressure[2], this->temperature[2]);

      phase_abundance[int(phase)].first += amount;

      if (i < N_MOST_ABUNDANT)
        most_abundant[i++] = elem->get_name();
    }
  }


  std::sort(phase_abundance.begin(), phase_abundance.end(), phase_comp_functor);

  for (auto kv : phase_abundance) {
    std::cerr << "  " << phase2str(kv.second) << ": " << kv.first << std::endl;
  }

  std::stringstream ss;
  // if ((phase_abundance[0].first > phase_abundance[1].first + 0.5) and (phase_abundance[1].first > 0.0)) {
  //   ss << "consists of " << phase2str(phase_abundance[0].second) << " elements: ";
  // }
  // else if ((phase_abundance[0].first > phase_abundance[1].first + 0.3) and (phase_abundance[1].first > 0.0)) {
  //   ss << "contains a mix of " << phase2str(phase_abundance[0].second) << " and " << phase2str(phase_abundance[0].second) << " elements: ";
  // }
  // else {
    ss << "consists primarily of ";
  //}

  for (int i = 0; i < N_MOST_ABUNDANT-1; i++) {
    ss << most_abundant[i] << ", ";
  }
  ss << "and " << most_abundant[N_MOST_ABUNDANT-1] << ".";

  this->description_data.composition_summary = ss.str();


  // TODO resource abundance


  this->description_data.set = true;

  return this->description_data;
}

