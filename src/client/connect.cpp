#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "connect.hpp"
#include "../util/exception.hpp"


// ServerConnection method "send" overshadows socket send function. Create ref
// with different name to alleviate this.
static ssize_t (*socket_send)(int, const void *, size_t, int) = &send;


ServerConnection::ServerConnection(const char *ip_address, int port)
{
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->fd < 0) {
    throw SocketError("Socket creation error", true);
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0) {
    throw SocketError(Formatter() << "IP address given (" << ip_address << ") not understood.", true);
  }

  if (connect(this->fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
    throw SocketError("Connection failed.", true);
  }
}


ServerConnection::~ServerConnection()
{
  this->send("leaving");
  close(this->fd);
}


std::string ServerConnection::send(std::string message)
{
  (*socket_send)(this->fd, message.data(), message.size(), 0);

  // get reply
  char buffer[1024] = {0};
  int l = read(this->fd, buffer, 1023);

  if (l < 0) {
    throw SocketError("Error reading reply.", true);
  }

  return std::string(buffer);
}
