#pragma once

#include "Command.hpp"
#include <vector>

class WhoCommand : public Command {
  private:
    std::vector<Channel*> _channels;
    std::string _mask;
    void checkParams(Client* client, std::vector<std::string> params);

  public:
    WhoCommand(std::string source, std::vector<std::string> params,
               Client* client);
    ~WhoCommand();

    void run();
};