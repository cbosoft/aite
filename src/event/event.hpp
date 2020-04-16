#pragma once

#include "../types.hpp"

class Event {

  public:

    Event();
    virtual ~Event();

    virtual void execute(Universe_ptr universe) =0;

};
