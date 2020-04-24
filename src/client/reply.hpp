#pragma once
#include <string>
#include <list>

class ServerReply {

  private:
    std::string __category;
    std::list<std::string> __contents;

  public:
    ServerReply(std::string);
    ~ServerReply();

    const std::string &category();
    const std::list<std::string> &contents();
};
