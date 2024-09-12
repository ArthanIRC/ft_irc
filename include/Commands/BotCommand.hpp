#pragma once

#include "Command.hpp"

class BotCommand : public Command {
  private:
    std::string _key;

  public:
    BotCommand(std::string source, std::vector<std::string> params,
               Client* client);
    ~BotCommand();

    void run();
};