#pragma once

#include "Command.hpp"
#include <vector>

class LusersCommand : public Command {
  public:
    LusersCommand(std::string source, std::vector<std::string> params,
                  Client* client);
    ~LusersCommand();

    void run();
};