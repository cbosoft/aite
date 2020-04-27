#pragma once
#include <list>

#include "resource.hpp"

class PooledResource {

  private:

    std::list<Resource *> pool;

  public:

    void add_resource(Resource *resource);
    void use(double amount);
    double get_amount_available() const;

    PooledResource &operator -=(double amount)
    {
      this->use(amount);
      return *this;
    }

    operator double()
    {
      return this->get_amount_available();
    }

};
