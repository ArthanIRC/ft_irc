#pragma once

#include "Command.hpp"
#include <string>

class OperCommand : public Command {
  private:
    std::string _name;
    std::string _password;

  public:
    OperCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~OperCommand();

    void run();
};