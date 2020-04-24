#include <stdlib.h>

#include "../util/args.hpp"
#include "../util/exception.hpp"
#include "../port.hpp"

#include "args.hpp"

ClientArgs default_args()
{
  ClientArgs args = {
    .server_address = "127.0.0.1",
    .server_port = DEFAULT_PORT,
    .colony_name = "guest",
    .mode = CM_GUI
  };

  return args;
}


ClientArgs parse_args(int argc, const char **argv)
{
  ClientArgs args = default_args();

  argc--; argv++;
  for (int i = 0; i < argc; i++) {
    if (ARG_EITHER("-i", "--server-ip-address")) {
      args.server_address = argv[++i];
    }
    else if (ARG_EITHER("-p", "--server-port")) {
      args.server_port = atoi(argv[++i]);
    }
    else if (ARG_EITHER("-c", "--colony-name")) {
      args.colony_name = argv[++i];
    }
    else if (ARG_EITHER("-m", "--mode")) {
      i++;
      if (ARG_EQ("batch")) {
        args.mode = CM_Batch;
      }
      else if (ARG_EQ("tui")) {
        args.mode = CM_TUI;
      }
      else if (ARG_EQ("gui")) {
        args.mode = CM_GUI;
      }
      else {
        throw ArgumentError(Formatter() << "Argument " << argv[i] << " not a valid mode.");
      }
    }
    else {
      throw ArgumentError(Formatter() << "Argument " << argv[i] << " not recognised.");
    }
  }

  return args;
}
