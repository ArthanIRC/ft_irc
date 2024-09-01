#pragma once

#include "Command.hpp"

class UserCommand : public Command {
  private:
    std::string _username;
    std::string _realname;

  public:
    UserCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~UserCommand();

    void run();
};