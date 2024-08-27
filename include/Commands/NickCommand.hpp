#pragma once

#include "Command.hpp"

class NickCommand : Command {
  private:
    std::string _nick;

    bool isNicknameUsed(std::string& nick);

  public:
    NickCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~NickCommand();

    void run();
};