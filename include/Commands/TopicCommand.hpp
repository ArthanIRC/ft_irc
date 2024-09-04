#pragma once

#include "Command.hpp"

class TopicCommand : public Command {
  private:
    void checkParams(Client* client, std::vector<std::string> params);
    Channel* _channel;

  public:
    TopicCommand(std::string source, std::vector<std::string> params,
                 Client* client);
    ~TopicCommand();

    void run();
};