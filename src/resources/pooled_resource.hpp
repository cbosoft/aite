#pragma once
#include <list>

#include "resource.hpp"

class PooledResource {

  private:

    std::list<Resource *> pool;
    std::list<Resource> obj_pool;
  public:

    void add_dummy(double amount);
    void add_resource(Resource *resource);
    double use(double amount);
    void add_equally(double amount);
    double get_amount_available() const;

    PooledResource &operator -=(double amount)
    {
      this->use(amount);
      return *this;
    }

    operator double() const
    {
      return this->get_amount_available();
    }

};
