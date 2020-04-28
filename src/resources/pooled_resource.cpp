#include "../util/exception.hpp"

#include "pooled_resource.hpp"

void PooledResource::use(double amount)
{
  double remainder = double(this->pool.size());
  double per_source_cost = amount / remainder;

  for (auto it = this->pool.begin(); it != this->pool.end(); it++) {

    auto res = *it;

    remainder -= 1.0;

    double av = res->get_amount_available();
    if (av < per_source_cost) {
      amount -= av;
      per_source_cost = amount / remainder;
      res->use(av);

      this->pool.erase(it++);

    }
    else {
      amount -= per_source_cost;
      res->use(per_source_cost);
    }

  }

  if (amount > 0.0)
    throw ResourceError("Insufficient resource!");
}

void PooledResource::add_resource(Resource *resource)
{
  this->pool.push_back(resource);
}

void PooledResource::add_equally(double amount)
{
  double amount_each = amount / double(this->pool.size());

  for (auto resource : this->pool) {
    resource->increase(amount_each);
  }
}

double PooledResource::get_amount_available() const
{
  double tot = 0.0;
  for (auto resource : this->pool) {
    tot += resource->get_amount_available();
  }
  return tot;
}
