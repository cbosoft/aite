#pragma once

class Resource {

  private:

    double total;
    double amount_used;

  public:

    Resource();
    Resource(double amount);
    ~Resource();

    double get_total() const;
    double get_amount_available() const;
    void use(double amount);
    void increase(double amount);

    Resource &operator -=(double amount)
    {
      this->use(amount);
      return *this;
    }

    Resource &operator +=(double amount)
    {
      this->increase(amount);
      return *this;
    }

    operator double() const
    {
      return this->get_amount_available();
    }

    Resource &operator=(double v)
    {
      this->total = v;
      return *this;
    }

};
