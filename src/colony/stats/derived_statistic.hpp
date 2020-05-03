#pragma once

#include <list>
#include <memory>

#include "statistic.hpp"

class DerivedStatistic;
typedef std::shared_ptr<DerivedStatistic> DerivedStatistic_ptr;
class DerivedStatistic : public virtual Statistic {

  protected:

    bool rawptr;
    std::list<Statistic *> base_stats_rawptr;
    std::list<DerivedStatistic_ptr> base_stats_shrd;
    virtual double get_base() const override;

  public:

    DerivedStatistic();
    DerivedStatistic(Statistic *base_stat);
    DerivedStatistic(std::list<Statistic *> base_stats);
    DerivedStatistic(DerivedStatistic_ptr base_stat);
    DerivedStatistic(std::list<DerivedStatistic_ptr> base_stats);
    ~DerivedStatistic();

};

template<typename R>
class DerivedResource : public virtual DerivedStatistic {

  protected:

    R *base_resource;
    virtual double get_base() const override
    {
      return this->base_resource->get_amount_available();
    }

  public:

    DerivedResource(R *base_resource)
      : base_resource(base_resource)
    {
    }
    ~DerivedResource() {}

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


class SumDerivedStatistic : public virtual DerivedStatistic {

  private:

    virtual double get_base() const override;

  public:

    SumDerivedStatistic(std::list<DerivedStatistic_ptr> parts);
    ~SumDerivedStatistic();

};


class LessThanDerivedStatistic : public virtual DerivedStatistic {

  private:
    DerivedStatistic_ptr left, right;
    double value_true, value_false;
    virtual double get_base() const override;

  public:

    LessThanDerivedStatistic(DerivedStatistic_ptr base_stat, DerivedStatistic_ptr compared_to, double if_true, double if_false);
    ~LessThanDerivedStatistic();

};
