#pragma once

enum ClientMode { CM_Batch, CM_TUI, CM_GUI };

typedef struct ClientArgs {
  const char *server_address;
  int server_port;
  const char *colony_name;
  ClientMode mode;
} ClientArgs;

ClientArgs parse_args(int argc, const char **argv);
