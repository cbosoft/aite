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

    ServerReply send(std::string message);
  public:
    ServerConnection(const char *address, int port);
    ~ServerConnection();

    void join(std::string colony_name);
    void sync();
};
