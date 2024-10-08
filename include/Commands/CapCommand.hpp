#pragma once

#include "Command.hpp"

class CapCommand : public Command {
  public:
    CapCommand(std::string source, std::vector<std::string> params,
               Client* client);
    ~CapCommand();

    void run();
};