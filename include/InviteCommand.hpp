#pragma once

#include "Command.hpp"

class InviteCommand : public Command {
  private:
    std::string nickname;
    std::string channel;

  public:
    InviteCommand(std::string prefix, std::vector<std::string> params);
    ~InviteCommand();

    void run();
};