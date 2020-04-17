#include <stdlib.h>
#include "../util/args.hpp"
#include "../util/exception.hpp"
#include "args.hpp"


ServerArgs default_args()
{
  ServerArgs args = {
    867
  };

  return args;
}


ServerArgs parse_args(int argc, const char **argv)
{
  ServerArgs args = default_args();

  argc--; argv++;
  for (int i = 0; i < argc; i++) {
    if (ARG_EITHER("-p", "--port")) {
      args.port = std::atoi(argv[++i]);
    }
    else throw ArgumentError(Formatter() << "Argument " << argv[i] << " not recognised.");
  }

  return args;
}
