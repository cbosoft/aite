#pragma once
#include <string>

#include "../types.hpp"
#include "object.hpp"


class Star final: public SystemObject {

  public:

    Star(System_ptr system, double position) : SystemObject(system, position) { }
    ~Star() {}

    SystemObjectType get_object_type() const override { return SO_Star; }
    std::string get_object_name() const override { return "star"; }

    static SystemObject_ptr generate(System_ptr system, double position);
};
