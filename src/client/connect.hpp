#pragma once
#include <string>
#include <list>

#include "reply.hpp"


typedef struct ColonyState {
  std::list<std::string> messages;
  std::list<std::string> activities;
} ColonyState;


class ServerConnection {

  private:

    int fd;
    ColonyState state;

  public:
    ServerConnection(const char *address, int port);
    ~ServerConnection();

    ServerReply send(std::string message);
    void sync();
};
