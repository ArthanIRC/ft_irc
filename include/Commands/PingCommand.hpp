#pragma once

#include "Command.hpp"

class PingCommand : public Command {
  private:
    void checkParams(Client* client, std::vector<std::string> params);

  public:
    PingCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~PingCommand();

    void run();
};