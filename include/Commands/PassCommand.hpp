#pragma once

#include "Client.hpp"
#include "Command.hpp"

class PassCommand : public Command {
  private:
    Client* client;
    std::string _password;

  public:
    PassCommand(std::string prefix, std::vector<std::string> params,
                Client* client);
    ~PassCommand();

    void run();
};