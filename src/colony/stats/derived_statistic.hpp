#pragma once

#include <list>
#include <memory>

#include "statistic.hpp"

class DerivedStatistic : public virtual Statistic {

  protected:

    std::list<Statistic *> base_stats;
    virtual double get_base() const override;

  public:

    DerivedStatistic();
    DerivedStatistic(Statistic *base_stat);
    DerivedStatistic(std::list<Statistic *> base_stats);
    ~DerivedStatistic();

};
typedef std::shared_ptr<DerivedStatistic> DerivedStatistic_ptr;

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


class SumDerivedStatistic : public virtual DerivedStatistic {

  private:

    virtual double get_base() const override;

  public:

    SumDerivedStatistic(std::list<Statistic *> base_stats);
    ~SumDerivedStatistic();

};
