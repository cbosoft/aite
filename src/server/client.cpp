#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

#include "../util/exception.hpp"
#include "../util/socket.hpp"
#include "../universe/universe.hpp"
#include "../colony/colony.hpp"
#include "../project/project.hpp"
#include "../event/event.hpp"
#include "../limits.hpp"

#include "server.hpp"


void GameServer::process_client_requests(int client_fd)
{
  std::string buffer;

  while (this->running) {

    int l = buffered_read(client_fd, buffer);
    if (l < 0) {
      std::cerr << FG_YELLOW << "WARNING" << RESET << " read error for client " << client_fd << " (" << errno << ", " << strerror(errno) << ")" << std::endl;
    }
    else if (l == 0) {
      // read of 0 in blocking read: connection is closed.
      break;
    }
    else {
      this->process_input(client_fd, std::string(buffer));
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
  std::string reply = "error|server error! (author at fault)";
  std::string category;
  std::vector<std::string> args;
  {
    std::stringstream ss(s);
    getline(ss, category, '|');

    std::string line;
    while (getline(ss, line, '|'))
      args.push_back(line);
  }

  if (category.compare("event") == 0) {

    try {
      Event_ptr event = Event::from_string(args[0]);
      this->universe->add_event(event);
      reply = "success|Event created.";
    }
    catch (const ArgumentError& e) {
      reply = "error|event argument error";
    }

  }
  else if (category.compare("join") == 0) {

    std::string colony_name = args[0];
    if (!this->universe->has_colony(colony_name)) {
      this->universe->add_colony(colony_name);
      reply = "welcome|Joined.";
    }
    else {
      // TODO: check password or key to verify client's ownership of colony
      reply = "success|Joined.";
    }

    Colony_ptr colony = this->universe->get_colony(colony_name);
    this->client_to_colony[client_fd] = colony;

  }
  else if (category.compare("project") == 0) {

    auto colony = this->client_to_colony[client_fd];
    colony->add_project(Project::from_args(args, *colony));
    reply = "success|done";

  }
  else if (category.compare("query") == 0) {

    const std::string &query = args[0];

    if (query.compare("number") == 0) {
      reply = Formatter() << "reply|" << this->client_to_colony[client_fd]->get_number();
    }
    else if (query.compare("status") == 0) {
      reply = Formatter() << "reply|" << this->client_to_colony[client_fd]->get_status();
    }
    else if (query.compare("statusprojects") == 0) {
      reply = Formatter() << "reply|" << this->client_to_colony[client_fd]->get_project_status();
    }
    else {
      reply = Formatter() << "error|query not understood: \"" << query << "\"";
    }

  }
  else if (category.compare("getmessages") == 0) {

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
  else if (category.compare("leaving") == 0) {
    reply = "acknowledged|acknowledged";
  }
  else {
    reply = Formatter() << "error|instruction not understood: \"" << category << "\"";
  }

  this->send(client_fd, reply);
}


void GameServer::send(int client_fd, std::string message)
{
  buffered_send(client_fd, message);
}
