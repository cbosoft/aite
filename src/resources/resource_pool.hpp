#pragma once

#include "resources.hpp"
#include "pooled_resource.hpp"

class ResourcePool {

  public:

    PooledResource OCHNPS;
    PooledResource metallic_ore;
    PooledResource nonmetallic_ore;
    PooledResource high_density_ore;
    PooledResource high_activity_ore;
    PooledResource luminosity;
    PooledResource volume;

    void add_source(Resources *resources);

};
