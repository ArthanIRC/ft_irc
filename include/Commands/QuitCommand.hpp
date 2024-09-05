#pragma once

#include "Command.hpp"

class QuitCommand : public Command {
  private:
    std::string _reason;

  public:
    QuitCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~QuitCommand();

    void run();
};