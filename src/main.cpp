#include <iostream>
#include <ctime>

#include "colony/colony.hpp"
#include "planet/planet.hpp"
#include "universe/universe.hpp"
#include "util/thesaurus.hpp"
#include "util/random.hpp"

int main(void)
{

  seed(time(NULL));

  Thesaurus &thesaurus = Thesaurus::getref();

  std::cerr << thesaurus.get_random_synonym("home", "noun") << std::endl;

}
