#pragma once

#include "Command.hpp"
#include <vector>

class PartCommand : public Command {
  private:
    std::vector<Channel*> _channels;
    void checkParams(Client* client, std::vector<std::string> params);
    void parseParams(Client* client);

  public:
    PartCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~PartCommand();

    void run();
};
