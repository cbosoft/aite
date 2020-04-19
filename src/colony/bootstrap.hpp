#include "colony.hpp"
#include "../event/event.hpp"

class BootstrapColonyEvent;
typedef std::shared_ptr<BootstrapColonyEvent> BootstrapColonyEvent_ptr;

class BootstrapColonyEvent : public virtual Event{

  private:

    Colony &colony;

  public:

    BootstrapColonyEvent(Colony &colony) : colony(colony) {}
    ~BootstrapColonyEvent() {}

    static BootstrapColonyEvent_ptr create(Colony &colony);

    void execute(Universe_ptr universe) override;

    double get_time() override
    {
      return -1.0;
    }
};

