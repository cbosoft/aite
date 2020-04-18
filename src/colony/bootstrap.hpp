#include "colony.hpp"
#include "../event/event.hpp"

class BootstrapColonyEvent;
typedef std::shared_ptr<BootstrapColonyEvent> BootstrapColonyEvent_ptr;

class BootstrapColonyEvent : public virtual Event{

  private:

    Colony &colony;
    double exec_time;

  public:

    BootstrapColonyEvent(Colony &colony);
    ~BootstrapColonyEvent();

    static BootstrapColonyEvent_ptr create(Colony &colony);

    void execute(Universe_ptr universe) override;
    double get_time() override;
};

