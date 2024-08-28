#pragma once

#include "Command.hpp"
#include <vector>

class JoinCommand : public Command {
  private:
    std::vector<Channel*> _channels;
    std::vector<std::string> _keys;
    void checkParams(Client* client, std::vector<std::string> params);
    void parseParams();
    void leaveChannels();
    void joinAndReplies(Channel* channel);

  public:
    JoinCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~JoinCommand();

    void run();
};
