#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "connect.hpp"
#include "../util/exception.hpp"
#include "../util/socket.hpp"


ServerConnection::ServerConnection(const char *ip_address, int port, std::string colony_name)
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

  this->join(colony_name);
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
  auto reply = this->send(Formatter() << "join|" << colony_name);

  if (reply.category().compare("welcome") == 0) {
    this->welcome();
    usleep(500000);
  }

  //std::cout << "Syncing with server... " << std::flush;
  this->sync();
  //std::cout << "done!" << std::endl;
  usleep(200000);

}


void ServerConnection::sync()
{

  this->state.status = std::map<std::string, std::string>();
  auto reply = this->send("query|status");
  for (auto line : reply.contents()) {

    std::string key, value;
    std::stringstream ss(line);
    getline(ss, key, ',');
    getline(ss, value, ',');

    this->state.status[key] = value;
  }

  reply = this->send("getmessages");
  if (reply.contents().front().compare("No messages.") != 0) {
    for (auto message : reply.contents()) {
      this->state.messages.push_back(message);
    }
  }

  reply = this->send("query|statusprojects");
  for (auto line : reply.contents()) {

    std::string name, status;
    std::stringstream ss(line);
    getline(ss, name, ':');
    getline(ss, status, ':');

    this->state.projects_status[name] = status;
  }
}


void ServerConnection::show_messages()
{
  if (this->state.messages.size()) {
    //std::cout << "\nYou have messages:\n";
    for (auto m : this->state.messages) {
      std::cout << "  " << m << std::endl;
    }

    this->state.messages = std::list<std::string>();
  }
}

void ServerConnection::show_status()
{
  std::cout << "\nStatus:\n";
  for (auto kv : this->state.status) {
    std::cout << "  " << kv.first << ": " << kv.second << "\n";
  }
}


void ServerConnection::request_project(std::string activity_name)
{
  this->send(Formatter() << "project|" << activity_name);
  this->sync();
  this->show_messages();
}
