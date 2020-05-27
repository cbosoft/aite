#pragma once

#include "../types.hpp"

// Event. An Event is a /thing/ that happens in the universe at a specified
// time. This event is Event::execute()'d when its time comes. This is intended
// to be used for non-monitored actions, like a random or unexpected occurence
// like a weather pattern. An event may be linked to a HistoryElement or a
// Feature. An event may only affect a certain location or certain colony, this
// will effect the discovery of the HE/F associated with the Event. The class is
// abstract, intended to be derived from.

class Event {

  public:

    Event() {};
    virtual ~Event() {};

    // This method is called by the Universe when the event is due.
    virtual void execute(Universe_ptr universe) =0;

    // This method returns the time at which the event should be executed. Note:
    // due to the granularity of the Universe, the event may occur slightly
    // after its proscribed time.
    virtual double get_time() =0;

    // Parses a string into an Event_ptr. TODO: change to another method (json?
    // map?) of passing arbitrary data into the event.
    static Event_ptr from_string(std::string s);

};



// Functor class which facilitates comparison of sorting Event_ptrs.

class EventCompareByTime {

  public:

    bool operator()(Event_ptr left, Event_ptr right)
    {
      return left->get_time() < right->get_time();
    }
};
