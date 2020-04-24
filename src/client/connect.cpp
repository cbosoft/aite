#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "connect.hpp"
#include "../util/exception.hpp"
#include "../util/socket.hpp"


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


ServerReply ServerConnection::send(std::string message)
{
  buffered_send(this->fd, message);

  // get reply
  std::string buffer;
  int l = buffered_read(this->fd, buffer);

  if (l < 0) {
    throw SocketError("Error reading reply.", true);
  }

  return ServerReply(buffer);
}






void ServerConnection::join(std::string colony_name)
{
  auto reply = this->send(Formatter() << "join|" <<colony_name);

  if (reply.category().compare("welcome") == 0) {
    this->welcome();
  }

  std::cout << "Syncing with server... " << std::flush;
  this->sync();
  std::cout << "done!" << std::endl;

  if (this->state.messages.size()) {
    std::cout << "You have messages:" << std::endl;
    for (auto m : this->state.messages) {
      std::cout << "  " << m << std::endl;
    }
  }

}


void ServerConnection::sync()
{
  auto reply = this->send("getmessages");
  if (reply.contents().front().compare("No messages.") != 0) {
    for (auto message : reply.contents()) {
      this->state.messages.push_back(message);
    }
  }

  // TODO sync activities
}
