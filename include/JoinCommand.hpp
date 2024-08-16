#pragma once

#include "Command.hpp"

class JoinCommand : public Command {
  private:
    std::string _channel;

  public:
    JoinCommand(std::string prefix, std::vector<std::string> params);
    ~JoinCommand();

    void run();
};