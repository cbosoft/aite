#pragma once
#include <string>

class ServerConnection {

  private:
    int fd;

  public:
    ServerConnection(const char *address, int port);
    ~ServerConnection();

    void send(std::string message);
};
