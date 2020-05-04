#include <iostream>

#include "../util/formatter.hpp"
#include "../util/exception.hpp"
#include "args.hpp"

#include "connect.hpp"


void batchmain(ClientArgs args)
{
  ServerConnection conn = ServerConnection(args.server_address, args.server_port, args.colony_name);
  conn.execute(args.command, args.args);
}


void tuimain(ClientArgs args)
{
  (void)args;
  std::cerr << "TUI not yet available." << std::endl;
}


void guimain(ClientArgs args)
{
  (void)args;
  std::cerr << "GUI not yet available." << std::endl;
}


int main(int argc, const char **argv)
{
  ClientArgs args = parse_args(argc, argv);

  try {
  switch (args.mode) {

    case CM_Batch:
      batchmain(args);
      break;

    case CM_TUI:
      tuimain(args);
      break;

    case CM_GUI:
      guimain(args);
      break;

  }
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
