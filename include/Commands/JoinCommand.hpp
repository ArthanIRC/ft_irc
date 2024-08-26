#pragma once

#include "Command.hpp"
#include <vector>

class JoinCommand : public Command {
  private:
    std::vector<Channel*> _chanlist;
    std::vector<std::string> _keylist;
    void checkParams(Client* client, std::vector<std::string> params);
    void setLists(Client* client, std::vector<std::string> params);

  public:
    JoinCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~JoinCommand();

    void run();
};
