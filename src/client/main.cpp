#include <iostream>

#include "../util/formatter.hpp"
#include "args.hpp"
#include "connect.hpp"

int main(int argc, const char **argv)
{
  ClientArgs args = parse_args(argc, argv);

  ServerConnection conn = ServerConnection(args.server_address, args.server_port);

  std::string reply = conn.send(Formatter() << "join|" << args.colony_name);
  std::cerr << reply << std::endl;

  reply = conn.send(Formatter() << "query|number");
  std::cerr << reply << std::endl;
}
