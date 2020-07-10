#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "../util/exception.hpp"
#include "../util/socket.hpp"
#include "../colony/colony.hpp"
#include "args.hpp"
#include "client.hpp"

#include <nlohmann/json.hpp>

int (*oconnect)(int, const struct sockaddr *, unsigned int) = &connect;


GameClient::GameClient(const char *ip_address, int port, std::string colony_name)
  : name(colony_name), colony(nullptr), connected(false)
{
  this->server_address.sin_family = AF_INET;
  this->server_address.sin_port = htons(port);
  if (inet_pton(AF_INET, ip_address, &this->server_address.sin_addr) <= 0) {
    throw SocketError(Formatter() << "IP address given (" << ip_address << ") not understood.", true);
  }
}

void GameClient::connect()
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

void GameClient::disconnect()
{
  if (not this->connected)
    return;

  nlohmann::json payload;
  payload["command"] = "leaving";
  this->send(payload);
  close(this->fd);
  this->connected = false;
}


GameClient::~GameClient()
{
  this->disconnect();
}


nlohmann::json GameClient::send(const nlohmann::json& to_send)
{
  if (to_send.type() != nlohmann::json::value_t::object) {
    throw Exception("GameClient::send", Formatter() << "client payload " << to_send << " needs to be object");
  }

  this->connect();

  std::string payload = to_send.dump();

  buffered_send(this->fd, payload);

  // get reply
  std::string buffer;
  int l = buffered_read(this->fd, buffer);

  if (l < 0) {
    throw SocketError("Error reading reply.", true);
  }

  auto reply = nlohmann::json::parse(buffer);

  // TODO check if error

  return reply;
}


void GameClient::join(std::string colony_name)
{
  nlohmann::json payload;
  payload["command"] = "join";
  payload["colony_name"] = colony_name;
  // payload["colony_key"] = <COLONY_KEY>;
  auto reply = this->send(payload);

  std::string category = reply["type"];
  if (category.compare("welcome") == 0) {
    this->welcome();
    usleep(500000);
  }
  else {
    // other categories?
  }

  this->sync();
  usleep(200000);

}


void GameClient::sync()
{
  nlohmann::json payload;
  payload["command"] = "sync";
  payload["sync_target"] = "colony";
  auto reply = this->send(payload);
  this->colony = Colony::from_serial(reply["sync_data"]);

  // TODO:
  // sync|universe
  // sync|other colonies
}


void GameClient::show_messages()
{
  if (this->colony->messages.size()) {
    std::cout << BOLD "Notifications:" RESET "\n";
    for (auto m : this->colony->messages) {
      std::cout << "  " << m << std::endl;
    }
  }
}


void GameClient::show_status()
{
  std::cerr
  << "  Name: " << this->colony->get_name() << "\n"
  << "Number: " << this->colony->get_number() << "\n"
  ;
}
