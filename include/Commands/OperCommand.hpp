#pragma once

#include "Command.hpp"

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