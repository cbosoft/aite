#pragma once

#include <thread>
#include <map>
#include "../util/safeq.hpp"
#include "../types.hpp"

class GameServer {

  private:

    bool running;
    int fd, port;

    std::mutex threads_mutex;
    std::map<int, std::thread> threads;

    Universe_ptr universe;

    void listen();
    void listen_in_bg();

    void process_client_requests(int client_fd);
    void process_client_requests_in_bg(int client_fd);

  public:

    GameServer(int port);
    ~GameServer();

    void start();
    void stop();

};
