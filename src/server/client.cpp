#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "../util/exception.hpp"
#include "../universe/universe.hpp"
#include "../event/event.hpp"

#include "server.hpp"

// GameServer method "send" overshadows socket send function. Create ref
// with different name to alleviate this.
static ssize_t (*socket_send)(int, const void *, size_t, int) = &send;


void GameServer::process_client_requests(int client_fd)
{
  char buffer[1024] = {0};

  while (this->running) {

    int l = read(client_fd, buffer, 1023);
    if (l < 0) {
      std::cerr << "read error" << std::endl;
    }
    else if (l == 0) {
      std::cerr << "read of 0 in blocking read: connection is closed." << std::endl;
      break;
    }
    else {
      this->process_input(client_fd, std::string(buffer));
    }

  }

  std::cerr << "client exited" << std::endl;

  std::lock_guard<std::mutex> lock(this->fds_mutex);
  this->invalid_fds.push_back(client_fd);
}

void GameServer::process_client_requests_in_bg(int client_fd)
{
  std::cerr << "launching connection thread for client " << client_fd << std::endl;
  std::lock_guard<std::mutex> lock(this->threads_mutex);

  this->threads[client_fd] = std::thread(&GameServer::process_client_requests, this, client_fd);
}


void GameServer::process_input(int client_fd, std::string s)
{
  std::stringstream ss(s);
  std::string type, rest;
  getline(ss, type, '|');
  getline(ss, rest, '|');

  std::cerr << "TYPE: " << type << ", REST: " << rest << std::endl;

  if (type.compare("event") == 0) {
    try {
      Event_ptr event = Event::from_string(rest);
      this->universe->add_event(event);
    }
    catch (const ArgumentError& e) {
      this->send(client_fd, "error|event argument error");
    }
  }
  else if (type.compare("join") == 0) {

    // rest is colony name
    if (!this->universe->has_colony(rest)) {
      this->universe->add_colony(rest);
    }

  }
  else {
    this->send(client_fd, "error|instruction not understood");
  }
}


void GameServer::send(int client_fd, std::string message)
{
  // add a newline to the end of the message
  std::stringstream ss;
  ss << message << "\n";
  std::string s = ss.str();
  (*socket_send)(client_fd, s.data(), s.size(), 0);
}
