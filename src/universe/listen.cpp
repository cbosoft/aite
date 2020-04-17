#include <netinet/in.h>
#include <sys/socket.h>
#include "universe.hpp"
#include "../util/exception.hpp"


// in Universe class, function "int listen(int, int)" is overshadowed by method
// "void Universe::listen(int)". This is very annoying. Therefore, create a
// pointer to the function listen with the name x_listen.
int (*x_listen)(int, int) = &listen;


void Universe::listen(int port)
{
  int opt = 1;

  this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!this->server_fd)
    throw SocketError("Failed to create server socket.", true);

  if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    throw SocketError("Failed to set socket options.", true);
  }

  struct sockaddr_in address;
  int addrlen = sizeof(address);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  struct sockaddr *addr_ptr = (struct sockaddr *)&address;

  if (bind(this->server_fd, addr_ptr, addrlen) < 0) {
    throw SocketError("Failed to bind socket.", true);
  }

  if ((*x_listen)(server_fd, 5) < 0) {
    throw SocketError("Failed to set listening.", true);
  }

  while(this->running) {
    // TODO I think this will block until a connection is accepted or errored:
    // is there a way to make it non-blocking?
    int client_fd = accept(server_fd, addr_ptr, (socklen_t*)&addrlen);
    if (client_fd < 0) {
      // connection unsuccessful
    }
    else {
      std::cerr << "client connected " << client_fd << std::endl;
      this->process_client_requests_in_bg(client_fd);
    }
  }

}


void Universe::listen_in_bg(int port)
{
  std::lock_guard<std::mutex> lock(this->threads_mutex);
  this->threads.push_back(std::thread(&Universe::listen, this, port));
}
