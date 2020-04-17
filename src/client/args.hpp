#pragma once

typedef struct ClientArgs {
  const char *server_address;
  int server_port;
  const char *colony_name;
} ClientArgs;

ClientArgs parse_args(int argc, const char **argv);
