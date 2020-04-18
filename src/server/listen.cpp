#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#include "server.hpp"
#include "../util/exception.hpp"


// function "int listen(int, int)" is overshadowed by method "void
// GameServer::listen(int)". This is very annoying. Therefore, create a pointer
// to the function listen with new name.

int (*socket_listen)(int, int) = &listen;


void GameServer::listen()
{

  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!this->fd)
    throw SocketError("Failed to create server socket.", true);

  int opt = 1;
  if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    throw SocketError("Failed to set socket options.", true);
  }

  struct sockaddr_in address;
  int addrlen = sizeof(address);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(this->port);
  struct sockaddr *addr_ptr = (struct sockaddr *)&address;

  if (bind(this->fd, addr_ptr, addrlen) < 0) {
    throw SocketError("Failed to bind socket.", true);
  }

  if ((*socket_listen)(this->fd, 5) < 0) {
    throw SocketError("Failed to set listening.", true);
  }

  fcntl(this->fd, F_SETFL, O_NONBLOCK);

  while(this->running) {

    {
      std::lock_guard<std::mutex> lock(this->fds_mutex);
      if (this->invalid_fds.size()) {
        for (auto fd : this->invalid_fds) {
          this->threads[fd].join();
          this->threads.erase(fd); // okay to delete after thread close?
          close(fd);
        }
        this->invalid_fds = std::list<int>();
      }
    }

    int client_fd = accept(this->fd, addr_ptr, (socklen_t*)&addrlen);
    if (client_fd < 0) {
      // connection unsuccessful
    }
    else {
      std::cerr << "client connected " << client_fd << std::endl;
      this->process_client_requests_in_bg(client_fd);
    }

    usleep(100*1000);

  }

  std::cerr << "listener stopped" << std::endl;
}


void GameServer::listen_in_bg()
{
  std::lock_guard<std::mutex> lock(this->threads_mutex);

  // start listening thread
  // key is normall fd
  // -1 is an invalid fd so shouldn't collide
  this->threads[-1] = std::thread(&GameServer::listen, this);
}
