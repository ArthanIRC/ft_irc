#pragma once

#include "Command.hpp"

class InviteCommand : public Command {
  private:
    std::string _nickname;
    std::string _channel;

  public:
    InviteCommand(std::string prefix, std::vector<std::string> params,
                  Client* client);
    ~InviteCommand();

    void run();
};