#pragma once
#include <string>
#include <list>
#include <map>

#include <arpa/inet.h>



typedef struct ColonyState {
  std::list<std::string> messages;
  std::list<std::string> activities;
  std::map<std::string, std::string> status;
  std::map<std::string, std::string> projects_status;
} ColonyState;
#include <nlohmann/json.hpp>


class GameClient {

  private:

    int fd;
    struct sockaddr_in server_address;
    std::string name;
    ColonyState state;
    bool connected;

    nlohmann::json send(const nlohmann::json& to_send);
    void welcome();
    void join(std::string colony_name);
    void connect();
    void disconnect();

  public:
    GameClient(const char *address, int port, std::string colony_name);
    ~GameClient();

    void sync();
    void execute(std::string command, std::list<std::string> args);
    void request_project(std::string activity_name);
    void show_messages();
    void show_status();
    void show_status_projects();
};
