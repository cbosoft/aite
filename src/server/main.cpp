#include "server.hpp"
#include "args.hpp"

int main(int argc, const char **argv)
{
  ServerArgs args = parse_args(argc, argv);

  GameServer game = GameServer(args.port);
  game.start();
}
