#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "../util/exception.hpp"
#include "../universe/universe.hpp"
#include "../colony/colony.hpp"
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
      std::cerr << FG_YELLOW << "WARNING" << RESET << " read error for client " << client_fd << " (" << errno << ", " << strerror(errno) << ")" << std::endl;
    }
    else if (l == 0) {
      // read of 0 in blocking read: connection is closed.
      break;
    }
    else {
      this->process_input(client_fd, std::string(buffer));
      memset(buffer, 0, 1024);
    }

  }

  std::lock_guard<std::mutex> lock(this->fds_mutex);
  this->invalid_fds.push_back(client_fd);
}

void GameServer::process_client_requests_in_bg(int client_fd)
{
  std::cerr << "[NEW THREAD:" << client_fd << "]" << std::endl;
  std::lock_guard<std::mutex> lock(this->threads_mutex);
  this->threads[client_fd] = std::thread(&GameServer::process_client_requests, this, client_fd);
}


void GameServer::process_input(int client_fd, std::string s)
{
  std::string type, rest, reply = "error|server error! (author at fault)";
  {
    std::stringstream ss(s);
    getline(ss, type, '|');
    getline(ss, rest, '|');
  }

  if (type.compare("event") == 0) {

    try {
      Event_ptr event = Event::from_string(rest);
      this->universe->add_event(event);
      reply = "success|Event created.";
    }
    catch (const ArgumentError& e) {
      reply = "error|event argument error";
    }

  }
  else if (type.compare("join") == 0) {

    // rest is colony name
    if (!this->universe->has_colony(rest)) {
      this->universe->add_colony(rest);
    }

    Colony_ptr colony = this->universe->get_colony(rest);
    this->client_to_colony[client_fd] = colony;

    reply = "success|Joined.";

  }
  else if (type.compare("query") == 0) {

    if (rest.compare("number") == 0) {
      reply = Formatter() << "reply|" << this->client_to_colony[client_fd]->get_number() << "\n";
    }
    else {
      reply = Formatter() << "error|query not understood: \"" << rest << "\"";
    }

  }
  else if (type.compare("getmessages") == 0) {

    auto colony = this->client_to_colony[client_fd];
    auto messages = colony->get_messages();
    if (messages.size()) {
      std::stringstream ss;
      ss << "reply|";
      for (auto message : messages) {
        ss << message << "|";
      }
      reply = ss.str();
    }
    else {
      reply = "reply|No messages.";
    }

  }
  else {
    reply = Formatter() << "error|instruction not understood: \"" << type << "\"";
  }

  this->send(client_fd, reply);
}


void GameServer::send(int client_fd, std::string message)
{
  // add a newline to the end of the message
  std::stringstream ss;
  ss << message << "\n";
  std::string s = ss.str();
  (*socket_send)(client_fd, s.data(), s.size(), 0);
}
