#include "args.hpp"
#include "connect.hpp"

int main(int argc, const char **argv)
{
  ClientArgs args = parse_args(argc, argv);

  ServerConnection conn = ServerConnection(args.server_address, args.server_port);
  conn.send("hello");
}
