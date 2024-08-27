#pragma once

#include "Command.hpp"
#include <string>

class NamesCommand : public Command {
  private:
  public:
    NamesCommand(std::string source, std::vector<std::string> params,
                 Client* client);
    ~NamesCommand();

    void run();
};