#pragma once

#include "Command.hpp"

class TopicCommand : public Command {
  private:
    Channel* _channel;

    void checkParams(Client* client, std::vector<std::string> params);

  public:
    TopicCommand(std::string source, std::vector<std::string> params,
                 Client* client);
    ~TopicCommand();

    void run();
};