#pragma once

#include "Command.hpp"

class PassCommand : public Command {
  public:
    PassCommand(std::string prefix, std::vector<std::string> params);
    ~PassCommand();

    void run();
};