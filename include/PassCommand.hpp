#pragma once

#include "Command.hpp"

class PassCommand : public Command {
  private:
    std::string _password;

  public:
    PassCommand(std::string prefix, std::vector<std::string> params);
    ~PassCommand();

    void run();
};