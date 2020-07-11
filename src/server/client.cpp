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
#include "../event/event.hpp"
#include "../limits.hpp"

#include "server.hpp"


void GameServer::process_client_requests(int client_fd)
{
  std::string buffer;

  while (this->running) {

    int l = buffered_read(client_fd, buffer);
    if (l < 0) {
      // read error; wait a wee bit and retry
      usleep(500);
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
  nlohmann::json reply;
  reply["type"] = "error";

  nlohmann::json input = nlohmann::json::parse(s);

  std::string command = input["command"];

  if (command.compare("join") == 0) {

    std::string colony_name = input["colony_name"];
    if (!this->universe->has_colony(colony_name)) {
      this->universe->add_colony(colony_name);
      reply["type"] = "welcome";
    }
    else {
      // TODO: check password or key to verify client's ownership of colony
      // if (check(input["colony_key"], input["colony_name"])) ...
      reply["type"] = "success";
      reply["detail"] = "Joined.";
    }

    Colony_ptr colony = this->universe->get_colony(colony_name);
    this->client_to_colony[client_fd] = colony;

  }
  // else if (command.compare("add") == 0) {
  //   const std::string &add_type = input["add_type"];

  //   if (add_type.compare("project") == 0) {
  //     // TODO
  //   }
  //   else {
  //     reply["error_string"] = Formatter() << "add argument " << add_type << " not understood";
  //   }

  // }
  else if (command.compare("sync") == 0) {

    const std::string &sync_target = input["sync_target"];

    if (sync_target.compare("colony") == 0) {
      reply["type"] = "success";
      // TODO determine if sync necessary
      // `if (input["mtime"] < colony.mtime())`
      // or perhaps a finer grained approch with mtimes for stats, messages,
      // abilities, or other members of colony
      reply["sync_data"] = this->client_to_colony[client_fd]->to_serial();
      this->client_to_colony[client_fd]->clear_messages();
    }
    else {
      // TODO: check for other types of sync (generated objects/systems/galaxies, other players)
      // TODO: log this error
      reply["error_detail"] = Formatter() << "Sync failed: sync_target not understood: \"" << sync_target << "\"";
    }

  }
  else if (command.compare("leaving") == 0) {
    reply["type"] = "acknowledge";
  }
  else {
    reply["error_string"] = Formatter() << "Command not understood: \"" << command << "\"";
  }

  this->send(client_fd, reply);
}


void GameServer::send(int client_fd, nlohmann::json payload)
{
  if (payload.type() != nlohmann::json::value_t::object) {
    throw Exception("GameServer::send", "server payload needs to be object");
  }
  std::string payload_string = payload.dump();
  buffered_send(client_fd, payload_string);
}
