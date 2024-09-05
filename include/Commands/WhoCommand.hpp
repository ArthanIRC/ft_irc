#pragma once

#include "Command.hpp"
#include <vector>

class WhoCommand : public Command {
  public:
    WhoCommand(std::string source, std::vector<std::string> params,
               Client* client);
    ~WhoCommand();

    void run();
};