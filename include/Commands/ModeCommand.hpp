#pragma once

#include "Command.hpp"

class ModeCommand : public Command {
  private:
    std::string _target;
    std::string _mode;
    bool _chanTarget;
    Channel* _channel;

    void chanMode();
    void userMode();

  public:
    ModeCommand(std::string source, std::vector<std::string> params,
                Client* client);
    ~ModeCommand();

    void run();
};