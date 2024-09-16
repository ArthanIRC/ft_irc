#pragma once

#include "Command.hpp"
#include <vector>

class KickCommand : public Command {
  private:
    Channel* _channel;
    std::string _comment;
    Client* _target;

    void checkParams(Client* client, std::vector<std::string> params);

  public:
    KickCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~KickCommand();

    void run();
};