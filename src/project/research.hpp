#include "project.hpp"


class Research : public virtual Project {

  private:

  public:

    Research(Colony &colony, const ProjectData &data);
    ~Research();

    ProjectStatus update() override;
};
