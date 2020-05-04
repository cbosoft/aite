#include <iostream>

#include "../util/colour.hpp"

#include "args.hpp"

void show_help(bool extended)
{
  std::cout
    << BOLD "Àite" RESET << " client\n"
    << "\n"
    << "This client can be used to send commands to the game server.\n"
    << "\n"
    << BOLD "Usage:" RESET << "\n"
    << "  aite_client [options] --mode batch command [args]\n"
    << "  aite_client [options] --mode tui|gui\n"
    ;

  if (extended) {
    // TODO
  }
}
