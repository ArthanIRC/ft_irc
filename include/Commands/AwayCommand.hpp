#pragma once

#include "Command.hpp"

class AwayCommand : public Command {
  public:
    AwayCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~AwayCommand();

    void run();
};