#include <iostream>
#include <unistd.h>

#include "universe.hpp"


void Universe::process_client_requests(int client_fd)
{
  char buffer[1024] = {0};

  while (this->running) {
    if (read(client_fd, buffer, 1023) < 0) {
      std::cerr << "read error" << std::endl;
    }
    else {
      std::cerr << buffer << std::endl;
    }
  }
}

void Universe::process_client_requests_in_bg(int client_fd)
{
  std::lock_guard<std::mutex> lock(this->threads_mutex);
  this->threads.push_back(std::thread(&Universe::process_client_requests_in_bg, this, client_fd));
}
