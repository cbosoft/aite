#pragma once
#include <string>
#include <list>
#include <map>

#include "reply.hpp"


typedef struct ColonyState {
  std::list<std::string> messages;
  std::list<std::string> activities;
  std::map<std::string, std::string> status;
  std::map<std::string, std::string> projects_status;
} ColonyState;


class ServerConnection {

  private:

    int fd;
    ColonyState state;

    ServerReply send(std::string message);
    void welcome();
    void join(std::string colony_name);

  public:
    ServerConnection(const char *address, int port, std::string colony_name);
    ~ServerConnection();

    void sync();
    void request_project(std::string activity_name);
    void show_messages();
    void show_status();
    void show_status_projects();
};
