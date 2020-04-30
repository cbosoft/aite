#pragma once

class Resource {

  private:

    double total;
    double fraction_visible;
    double amount_used;

  public:

    Resource();
    Resource(double fraction_visible);
    ~Resource();

    double get_amount_available() const;
    void set_fraction_visible(double fraction);
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

};
