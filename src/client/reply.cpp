#include <sstream>


#include "../util/exception.hpp"
#include "reply.hpp"


ServerReply::ServerReply(const char *s)
{
  std::stringstream ss(s);

  getline(ss, this->__category, '|');

  if (this->__category.compare("error") == 0)
    throw CommandError(Formatter() << s); //  TODO check what error it is and raise appropriately

  std::string line;
  while (getline(ss, line, '|'))
    this->__contents.push_back(line);

}

ServerReply::~ServerReply()
{
}

const std::string &ServerReply::category()
{
  return this->__category;
}

const std::list<std::string> &ServerReply::contents()
{
  return this->__contents;
}
