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
