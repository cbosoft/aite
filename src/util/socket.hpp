#pragma once
#include <string>

void buffered_send(int fd, std::string message);
int buffered_read(int fd, std::string &message);
