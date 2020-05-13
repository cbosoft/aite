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
  TL_Scorching,
  TL_Unfathomable
};

enum AtmosphereLevel {
  AL_None,
  AL_Thin,
  AL_EarthLike,
  AL_Thick,
  AL_Heavy
};

enum PressureLevel {
  PL_Negligable,
  PL_Low,
  PL_Medium,
  PL_High,
  PL_Crushing
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

  SizeCategory sc;
  double diameter;

  double temperature;
  TemperatureLevel tl;
  AtmosphereLevel al;
  PressureLevel pl;

  double density;
  double gravitational_constant;
  GravityLevel gl;

  ChemicalComposition apparent_composition;
  std::string composition_summary;
} ObjectDescriptionData;
