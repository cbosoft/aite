#include "alphabet.hpp"
#include "exception.hpp"

static const char LATIN_ALPHABET[26] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

char latin_alphabet(unsigned int index)
{
  if (index > 26) {
    throw IndexError(Formatter() << "Index " << index << " invalid. There are only 26 chars in the latin alphabet!");
  }

  return LATIN_ALPHABET[index];
}
