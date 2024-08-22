#pragma once

#include "Command.hpp"

class KickCommand : public Command {
  private:
    // std::str
  public:
    KickCommand(std::string prefix, std::vector<std::string> params);
    ~KickCommand();

    void run();
};