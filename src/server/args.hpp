#pragma once

typedef struct ServerArgs {
  int port;
} ServerArgs;

ServerArgs parse_args(int argc, const char **argv);
