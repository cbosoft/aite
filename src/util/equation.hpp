#pragma once

class LinearEqn {

  private:
    double m, c;

  public:
    LinearEqn(double m, double c);
    
    double get_value(double x);
};
