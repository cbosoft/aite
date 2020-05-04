#pragma once

#include <string>
#include <list>

enum ClientMode { CM_Batch, CM_TUI, CM_GUI };

typedef struct ClientArgs {
  bool try_load_config_from_file;
  const char *server_address;
  int server_port;
  const char *colony_name;
  ClientMode mode;
  std::string command;
  std::list<std::string> args;
} ClientArgs;

ClientArgs parse_args(int argc, const char **argv);
