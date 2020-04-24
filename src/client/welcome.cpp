#include <iostream>
#include <unistd.h>

#include "../util/colour.hpp"
#include "connect.hpp"


void ServerConnection::welcome()
{
  std::cout
    << "\n"
    << "Welcome to " BOLD "Àite" RESET ", a game about new horizons and final frontiers."
    << std::endl;

  usleep(200*1000);

  std::cout
    << "\n"
    << "This client will allow you to communicate with your colony; to give "
    << "orders, to check status, and to vicariously explore a far region of "
    << "the universe.\n"
    << "\n"
    << "Your fledgling colony has been dropped somewhere within " BOLD "àite "
    << "domhainn" RESET ". You should start by settling in to your planet, and "
    << "seeing what your new home has to offer. Resources are likely scarce: "
    << "make them count.\n"
    << std::endl;
}
