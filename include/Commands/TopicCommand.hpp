#pragma once

#include "Command.hpp"

class TopicCommand : public Command {
  public:
    TopicCommand(std::string source, std::vector<std::string> params,
                 Client* client);
    ~TopicCommand();

    void run();
    void checkParams(Client* client, std::vector<std::string> params);
};