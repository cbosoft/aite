#include <iostream>
#include <ctime>

#include "planet/planet.hpp"
#include "random/random.hpp"

int main(void)
{
  seed(time(NULL));

  auto planet = Planet::generate();
  std::cerr << planet->describe() << std::endl;
}
