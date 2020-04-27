#pragma once

#include "pooled_resource.hpp"

class ResourcePool {

  private:

    PooledResource foodstock;
    PooledResource metals;
    PooledResource ceramics;
    PooledResource heavy_metals;
    PooledResource radiosource;
    PooledResource luminance;
    PooledResource volume;

};
