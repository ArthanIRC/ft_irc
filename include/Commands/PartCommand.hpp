#pragma once

#include "Command.hpp"
#include <vector>

class PartCommand : public Command {
  private:
    std::vector<Channel*> _channels;
    std::string _reason;
    void checkParams(Client* client, std::vector<std::string> params);
    void parseParams(Client* client, std::vector<std::string> params);
    std::string createReply(Channel* channel);

  public:
    PartCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~PartCommand();

    void run();
};
