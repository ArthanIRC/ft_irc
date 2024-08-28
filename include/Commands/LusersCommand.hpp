#pragma once

#include "Command.hpp"
#include <vector>

class LusersCommand : public Command {
  private:
    void checkParams(Client* client, std::vector<std::string> params);

  public:
    LusersCommand(std::string source, std::vector<std::string> params,
                  Client* client);
    ~LusersCommand();

    void run();
};