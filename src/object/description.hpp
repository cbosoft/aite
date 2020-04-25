#pragma once
#include "../types.hpp"

enum TemperatureLevel {
  TL_NearAbsoluteZero,
  TL_ExtremeCold,
  TL_VeryCold,
  TL_Cold,
  TL_Temperate,
  TL_Hot,
  TL_VeryHot,
  TL_ExtremeHeat,
  TL_Scorching
};

enum AtmosphereLevel {
  AL_None,
  AL_Thin,
  AL_EarthLike,
  AL_Thick,
  AL_Heavy
};

enum WindLevel {
  WL_None,
  WL_Negligable,
  WL_Strong,
  WL_Gale,
  WL_Ferocious
};

enum GravityLevel {
  GL_NonExistant,
  GL_Weak,
  GL_Normal,
  GL_Heavy,
  GL_Oppressive,
  GL_SpineCrushing
};

enum SizeCategory {
  SC_Small,
  SC_EarthSized,
  SC_Large,
  SC_Huge,
  SC_Giant
};

typedef struct ObjectDescriptionData {
  bool set;

  double diameter;
  SizeCategory sc;

  double temperature;
  TemperatureLevel tl;
  AtmosphereLevel al;
  WindLevel wl;

  double density;
  double gravitational_constant;
  GravityLevel gl;

  ElementalAbundance apparent_composition;
} ObjectDescriptionData;
