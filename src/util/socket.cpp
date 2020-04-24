#include <string>
#include <sstream>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#include "exception.hpp"
#include "../limits.hpp"


void buffered_send(int fd, std::string message)
{
  auto data = message.data();
  auto size = message.size();
  send(fd, data, size, 0);
}


int buffered_read(int fd, std::string &message)
{
  char buffer[SOCKET_BUFFER_SIZE+1] = {0};
  int total_bytes_recvd = 0;
  std::stringstream ss;

  while (true) {
    int l = read(fd, buffer, SOCKET_BUFFER_SIZE);
    if (l < 0) {
      return -1;
    }

    ss << buffer;
    memset(buffer, 0, SOCKET_BUFFER_SIZE);
    total_bytes_recvd += l;

    if (l < SOCKET_BUFFER_SIZE) {
      break;
    }
  }

  message = ss.str();
  return total_bytes_recvd;
}
