#pragma once
#include <list>
#include <map>
#include <memory>

class Feature;
typedef std::shared_ptr<Feature> Feature_ptr;

class HistoryElement;
typedef std::shared_ptr<HistoryElement> HistoryElement_ptr;

class Activity;
typedef std::shared_ptr<Activity> Activity_ptr;

class Message;
typedef std::shared_ptr<Message> Message_ptr;

class Event;
typedef std::shared_ptr<Event> Event_ptr;

class Element;
typedef std::shared_ptr<Element> Element_ptr;
typedef std::list<std::pair<std::shared_ptr<Element>, double>> ElementalAbundance;

class Compound;
typedef std::shared_ptr<Compound> Compound_ptr;

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
