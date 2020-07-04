#include <iostream>

#include "../util/formatter.hpp"
#include "../util/exception.hpp"
#include "args.hpp"

#include "client.hpp"


int main(int argc, const char **argv)
{
  ClientArgs args = parse_args(argc, argv);

  try {
    GameClient conn = GameClient(args.server_address, args.server_port, args.colony_name);
    conn.execute(args.command, args.args);
  }
  catch (const SocketError &e) {
    std::cerr
     << "Error connecting: are the server address and port correct?\n"
     << "    IP: " << args.server_address << "\n"
     << "  Port: " << args.server_port << "\n" 
     ;
  }
  catch (const Exception &e) {
    std::cerr
      << e.what() << "\n"
      << "\"aite_client --help\" for help.\n"
      ;

    exit(1);
  }
}
