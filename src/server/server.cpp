#include "../universe/universe.hpp"
#include "server.hpp"


GameServer::GameServer(int port)
{
  this->port = port;
  this->universe = Universe::get_universe();
}


GameServer::~GameServer()
{
  this->stop();
}


void GameServer::stop()
{
  // stop accepting new connections; stop processing current connections.
  this->running = false;

  // if there is a universe, destroy it.
  if (this->universe)
    this->universe->stop();

  // wait for any remaining connection threads to die
  for (auto kv_it = this->threads.begin(); kv_it != this->threads.end(); kv_it++) {
    // first is key (client fd), second is value (thread)
    kv_it->second.join();
  }
}


void GameServer::start()
{
  // listen for new connections
  this->listen_in_bg();

  // run game!
  this->universe->run_events();
}
