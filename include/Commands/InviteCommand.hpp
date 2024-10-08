#pragma once

#include "Command.hpp"

class InviteCommand : public Command {
  private:
    std::string _targetNickname;
    Channel* _channel;

  public:
    InviteCommand(std::string source, std::vector<std::string> params,
                  Client* client);
    ~InviteCommand();

    void run();
};