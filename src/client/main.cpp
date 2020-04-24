#include <iostream>

#include "../util/formatter.hpp"
#include "args.hpp"
#include "connect.hpp"


void batchmain(ClientArgs args)
{
  ServerConnection conn = ServerConnection(args.server_address, args.server_port);
  conn.join(args.colony_name);
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
