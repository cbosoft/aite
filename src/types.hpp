#pragma once
#include <list>
#include <map>
#include <memory>

enum Phase { PhaseSolid, PhaseLiquid, PhaseGas, PhasePlasma };

class Item;
typedef std::shared_ptr<Item> Item_ptr;

class Feature;
typedef std::shared_ptr<Feature> Feature_ptr;

class HistoryElement;
typedef std::shared_ptr<HistoryElement> HistoryElement_ptr;

class Project;
typedef std::shared_ptr<Project> Project_ptr;

class Message;
typedef std::shared_ptr<Message> Message_ptr;

class Event;
typedef std::shared_ptr<Event> Event_ptr;

class ChemicalComponent;
typedef std::shared_ptr<ChemicalComponent> ChemicalComponent_ptr;
typedef std::list<std::pair<ChemicalComponent_ptr, double>> ChemicalComposition;

class Element;
typedef std::shared_ptr<Element> Element_ptr;

class Compound;
typedef std::shared_ptr<Compound> Compound_ptr;

class Colony;
typedef std::shared_ptr<Colony> Colony_ptr;

class SystemObject;
typedef std::shared_ptr<SystemObject> SystemObject_ptr;

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
