#pragma once

#include "Command.hpp"

class JoinCommand : public Command {
  public:
    JoinCommand(std::string prefix, std::vector<std::string> params,
                Client* client);
    ~JoinCommand();

    void run();
};