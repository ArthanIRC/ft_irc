#pragma once

#include "Command.hpp"

class JoinCommand : public Command {
  private:
    std::vector<Channel*> _channels;
    std::vector<std::string> _keys;

    void checkParams(Client* client, std::vector<std::string> params);
    void joinAndReplies(Channel* channel);
    void leaveChannels();
    void parseParams();

  public:
    JoinCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~JoinCommand();

    void run();
};
