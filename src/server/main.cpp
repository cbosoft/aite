#include <ctime>
#
#include "server.hpp"
#include "args.hpp"
#include "../util/random.hpp"

int main(int argc, const char **argv)
{

  seed(time(NULL));

  ServerArgs args = parse_args(argc, argv);

  GameServer game = GameServer(args.port);
  game.start();
}
