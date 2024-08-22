#pragma once

#include "Command.hpp"

class KickCommand : public Command {
  private:
    // std::str
  public:
    KickCommand(std::string prefix, std::vector<std::string> params,
                Client* client);
    ~KickCommand();

    void run();
};