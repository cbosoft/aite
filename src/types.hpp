#pragma once
#include <memory>


class Element;
typedef std::shared_ptr<Element> Element_ptr;

class Colony;
typedef std::shared_ptr<Colony> Colony_ptr;

class Planet;
typedef std::shared_ptr<Planet> Planet_ptr;

class Star;
typedef std::shared_ptr<Star> Star_ptr;

class System;
typedef std::shared_ptr<System> System_ptr;

class Galaxy;
typedef std::shared_ptr<Galaxy> Galaxy_ptr;

class Universe;
typedef std::shared_ptr<Universe> Universe_ptr;
