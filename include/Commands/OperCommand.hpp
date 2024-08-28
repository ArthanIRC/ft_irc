#pragma once

#include "Command.hpp"

class OperCommand : public Command {
  private:
  public:
    OperCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~OperCommand();

    void run();
};