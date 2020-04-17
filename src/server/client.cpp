#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "../util/exception.hpp"

#include "server.hpp"

// GameServer method "send" overshadows socket send function. Create ref
// with different name to alleviate this.
static ssize_t (*socket_send)(int, const void *, size_t, int) = &send;


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

void GameServer::send(int client_fd, std::string message)
{
  // add a newline to the end of the message
  std::stringstream ss;
  ss << message << "\n";
  std::string s = ss.str();
  (*socket_send)(client_fd, s.data(), s.size(), 0);
}
