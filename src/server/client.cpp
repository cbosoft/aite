#include <unistd.h>
#include <iostream>
#include <cstring>

#include "../util/exception.hpp"

#include "server.hpp"


void GameServer::process_client_requests(int client_fd)
{
  char buffer[1024] = {0};

  while (this->running) {

    int l = read(client_fd, buffer, 1023);
    std::cerr << l << " ";
    if (l < 0) {
      std::cerr << "read error" << std::endl;
    }
    else if (l == 0) {
      std::cerr << "read of 0 in blocking read: connection is closed." << std::endl;
      break;
    }
    else {
      std::cerr << buffer << std::endl;
    }

  }

  std::cerr << "client exited" << std::endl;
  // TODO mark this fd as exit
}

void GameServer::process_client_requests_in_bg(int client_fd)
{
  std::cerr << "launching connection thread for client " << client_fd << std::endl;
  std::lock_guard<std::mutex> lock(this->threads_mutex);

  this->threads[client_fd] = std::thread(&GameServer::process_client_requests, this, client_fd);
}
