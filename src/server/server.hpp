#pragma once

#include <thread>
#include <list>
#include <map>
#include "../util/safeq.hpp"
#include "../types.hpp"

#include <nlohmann/json.hpp>

class GameServer {

  private:

    bool running;
    int fd, port;

    std::mutex threads_mutex;
    std::map<int, std::thread> threads;
    std::map<int, Colony_ptr> client_to_colony;
    std::mutex fds_mutex;
    std::list<int> invalid_fds;
    nlohmann::json config;

    Universe_ptr universe;

    void listen();
    void listen_in_bg();

    void send(int client_fd, nlohmann::json payload);

    void process_input(int client_fd, std::string s);

    void process_client_requests(int client_fd);
    void process_client_requests_in_bg(int client_fd);

    bool load_config(const std::string &path);
    void load_config();

  public:

    GameServer(int port);
    ~GameServer();

    void start();
    void stop();

};
