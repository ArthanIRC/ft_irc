#pragma once

#include "Command.hpp"

class MotdCommand : public Command {
  private:
  public:
    MotdCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~MotdCommand();

    void run();
};