#pragma once
#include <string>
#include "reply.hpp"


class ServerConnection {

  private:
    int fd;

  public:
    ServerConnection(const char *address, int port);
    ~ServerConnection();

    ServerReply send(std::string message);
};
