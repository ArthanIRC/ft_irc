#pragma once

#include "Command.hpp"

class ModeCommand : public Command {
  public:
    ModeCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~ModeCommand();

    void run();
};