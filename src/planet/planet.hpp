#pragma once
#include <list>
#include <utility>
#include <memory>

class Element;

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
  SC_EarthLike,
  SC_Large,
  SC_Huge,
  SC_Giant
};

typedef struct PlanetDescriptionData {
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

  std::list<std::pair<std::shared_ptr<Element>, double>> apparent_composition;
} PlanetDescriptionData;

class Planet {

  private:

    unsigned long long id;
    double distance;
    double diameter;
    double density_core, density_mantle, density_deep, density_surface, density_average;
    double pressure_low, pressure_high, pressure_average;
    double temp_low, temp_high, temp_average;

    // double humidity_low, humidity_high, humidity_average;
    // double water_coverage;

    std::list<std::pair<std::shared_ptr<Element>, double>> composition_surface;
    std::list<std::pair<std::shared_ptr<Element>, double>> composition_deep;
    std::list<std::pair<std::shared_ptr<Element>, double>> composition_mantle;
    std::list<std::pair<std::shared_ptr<Element>, double>> composition_core;

    PlanetDescriptionData description_data;

  public:

    Planet(unsigned long long id);
    ~Planet();

    static Planet_ptr generate(double distance);

    const PlanetDescriptionData &describe();

    double get_diameter() const;
    unsigned long long get_id() const;
};

