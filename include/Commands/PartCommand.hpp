#pragma once

#include "Command.hpp"

class PartCommand : public Command {
  private:
    std::vector<Channel*> _channels;
    std::string _reason;

    std::string createReply(Channel* channel);
    void parseParams(Client* client, std::vector<std::string> params);
    void checkParams(Client* client, std::vector<std::string> params);

  public:
    PartCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~PartCommand();

    void run();
};
