#pragma once
#include <string>
#include <list>
#include <map>

#include <arpa/inet.h>

#include "../types.hpp"

#include <nlohmann/json.hpp>


class GameClient {

  private:

    int fd;
    struct sockaddr_in server_address;
    std::string name;
    Colony_ptr colony;
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
    void show_messages();
    void show_status();
};
