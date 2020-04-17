#pragma once

#include "../types.hpp"

class Event {

  public:

    Event();
    virtual ~Event();

    virtual void execute(Universe_ptr universe) =0;
    virtual double get_time() =0;

    static Event_ptr from_string(std::string s);


};

class EventCompareByTime {

  public:

    bool operator()(Event_ptr left, Event_ptr right)
    {
      return left->get_time() < right->get_time();
    }
};
