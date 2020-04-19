#pragma once

class SystemObject {

  protected:
    double position;

  public:

    SystemObject(double position) : position(position) {}

    double get_position() const { return this->position; }
};
