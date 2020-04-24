#pragma once
#include <string>
#include <list>

class ServerReply {

  private:
    std::string __category;
    std::list<std::string> __contents;

  public:
    ServerReply(const char *v);
    ~ServerReply();

    const std::string &category();
    const std::list<std::string> &contents();
};
