#pragma once

#include <memory>

#include "statistic.hpp"

class DerivedStatistic : public virtual Statistic {

  protected:

    Statistic *base_stat;
    virtual double get_base() const override;

  public:

    DerivedStatistic(Statistic *base_stat);
    ~DerivedStatistic();

};

class LinearDerivedStatistic : public virtual DerivedStatistic {

  private:

    double m, c;
    virtual double get_base() const override;

  public:

    LinearDerivedStatistic(Statistic *base_stat, double m, double c);
    ~LinearDerivedStatistic();

};


class PowerDerivedStatistic : public virtual DerivedStatistic {

  private:

    double p, m, c;
    virtual double get_base() const override;

  public:

    PowerDerivedStatistic(Statistic *base_stat, double p, double m, double c);
    ~PowerDerivedStatistic();

};

typedef std::shared_ptr<DerivedStatistic> DerivedStatistic_ptr;
