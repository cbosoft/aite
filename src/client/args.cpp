#include <fstream>
#include <sstream>
#include <cstdlib>

#include "../util/args.hpp"
#include "../util/exception.hpp"
#include "../port.hpp"

#include "args.hpp"

ClientArgs default_args()
{
  ClientArgs args = {
    .try_load_config_from_file = true,
    .server_address = "127.0.0.1",
    .server_port = DEFAULT_PORT,
    .colony_name = "guest",
    .mode = CM_TUI,
    .command = "status",
    .args = {}
  };

  return args;
}

void parse_args_from_file(ClientArgs &args)
{
  const char *hdir = std::getenv("HOME");
  std::string path = Formatter() << hdir << "/.aite_config";
  std::ifstream ifs(path);

  if (ifs.fail())
    return;

  std::string line, key, value;
  while (std::getline(ifs, line)) {
    std::stringstream ss(line);
    std::getline(ss, key, ' ');
    std::getline(ss, value);

    if (key.compare("colony_name") == 0) {
      args.colony_name = strdup(value.c_str());
    }
    else if (key.compare("server_port") == 0) {
      args.server_port = std::stoi(value);
    }
    else if (key.compare("server_address") == 0) {
      args.server_address = strdup(value.c_str());
    }

  }

  (void) args;

}

void save_args_to_file(ClientArgs &args)
{
  const char *hdir = std::getenv("HOME");
  std::string path = Formatter() << hdir << "/.aite_config";
  std::ofstream ofs(path);
  if (ofs.fail())
    return;

  ofs
    << "colony_name " << args.colony_name << std::endl
    << "server_address " << args.server_address << std::endl
    << "server_port " << args.server_port << std::endl
    ;
}


ClientArgs parse_args(int argc, const char **argv)
{
  ClientArgs args = default_args();

  argc--; argv++;
  for (int i = 0; i < argc; i++) {
    if (ARG_EITHER("-i", "--server-ip-address")) {
      args.try_load_config_from_file = false;
      args.server_address = argv[++i];
    }
    else if (ARG_EITHER("-p", "--server-port")) {
      args.try_load_config_from_file = false;
      args.server_port = atoi(argv[++i]);
    }
    else if (ARG_EITHER("-c", "--colony-name")) {
      args.try_load_config_from_file = false;
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

  if (args.try_load_config_from_file)
    parse_args_from_file(args);
  save_args_to_file(args);

  return args;
}
