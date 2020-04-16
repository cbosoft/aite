#pragma once

#include "event.hpp"

class NewColonyEvent;
typedef std::shared_ptr<NewColonyEvent> NewColonyEvent_ptr;

class NewColonyEvent : public virtual Event {

  private:

    std::string name;

  public:

    NewColonyEvent();
    ~NewColonyEvent();

    static NewColonyEvent_ptr create(std::string name);

    void execute(Universe_ptr universe) override;

};

