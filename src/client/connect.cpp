#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "../util/exception.hpp"
#include "../util/socket.hpp"
#include "args.hpp"
#include "connect.hpp"

int (*oconnect)(int, const struct sockaddr *, unsigned int) = &connect;


ServerConnection::ServerConnection(const char *ip_address, int port, std::string colony_name)
  : name(colony_name), connected(false)
{
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_port = htons(port);
  if (inet_pton(AF_INET, ip_address, &this->server_address.sin_addr) <= 0) {
    throw SocketError(Formatter() << "IP address given (" << ip_address << ") not understood.", true);
  }
}

void ServerConnection::connect()
{
  if (this->connected)
    return;

  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->fd < 0) {
    throw SocketError("Socket creation error", true);
  }

  if (oconnect(this->fd, (struct sockaddr *)&this->server_address, sizeof(this->server_address)) < 0 ) {
    throw SocketError("Connection failed.", true);
  }
  this->connected = true;

  this->join(this->name);
}

void ServerConnection::disconnect()
{
  if (not this->connected)
    return;

  this->send("leaving");
  close(this->fd);
  this->connected = false;
}


ServerConnection::~ServerConnection()
{
  this->disconnect();
}


ServerReply ServerConnection::send(std::string message)
{
  this->connect();

  buffered_send(this->fd, message);

  // get reply
  std::string buffer;
  int l = buffered_read(this->fd, buffer);

  if (l < 0) {
    throw SocketError("Error reading reply.", true);
  }

  return ServerReply(buffer);
}

void ServerConnection::execute(std::string command, std::list<std::string> args)
{

  if (not command.size()) {
    throw ArgumentError("Command required.");
  }


  if (command.compare("status") == 0) {

    this->sync();
    this->show_status();

  }
  else if (command.compare("startproject") == 0) {

    if (args.size() != 1)
      throw ArgumentError("Command startproject needs an argument: project name");

    this->request_project(args.front());
    this->sync();
    this->show_messages();

  }
  else {
    throw ArgumentError(Formatter() << "Unknown command " << command << ".");
  }

}






void ServerConnection::join(std::string colony_name)
{
  auto reply = this->send(Formatter() << "join|" << colony_name);

  if (reply.category().compare("welcome") == 0) {
    this->welcome();
    usleep(500000);
  }

  this->sync();
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
    std::cout << BOLD "Notifications:" RESET "\n";
    for (auto m : this->state.messages) {
      std::cout << "  " << m << std::endl;
    }

    this->state.messages = std::list<std::string>();
  }
}

void ServerConnection::show_status()
{
  std::cout << BOLD "Status:" RESET "\n";
  for (auto kv : this->state.status) {
    std::cout << "  " << kv.first << ": " << kv.second << "\n";
  }
}

void ServerConnection::show_status_projects()
{
  if (this->state.projects_status.size()) {
    std::cout << "\n" BOLD "Projects:" RESET "\n";
    for (auto kv : this->state.projects_status) {
      std::cout << "  " << kv.first << ": " << kv.second << "\n";
    }
  }
}


void ServerConnection::request_project(std::string project_name)
{
  this->send(Formatter() << "project|" << project_name);
}
