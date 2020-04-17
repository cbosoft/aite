#include "../universe/universe.hpp"
#include "args.hpp"

int main(int argc, const char **argv)
{
  ServerArgs args = parse_args(argc, argv);

  Universe_ptr universe = Universe::get_universe();
  universe->listen_in_bg(args.port);
  universe->run_events();
}
