#pragma once

#include "Command.hpp"
#include <vector>

class WhoCommand : public Command {
  private:
    std::string _target;

  public:
    WhoCommand(std::string source, std::vector<std::string> params,
               Client* client);
    ~WhoCommand();

    void run();
};