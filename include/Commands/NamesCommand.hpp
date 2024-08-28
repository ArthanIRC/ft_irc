#pragma once

#include "Command.hpp"
#include <map>
#include <string>

class NamesCommand : public Command {
  private:
    std::map<std::string, Channel*> _channels;
    Client* _client;

  public:
    NamesCommand(std::string source, std::vector<std::string> params,
                 Client* client);
    ~NamesCommand();

    void run();
};