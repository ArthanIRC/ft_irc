#pragma once

#include "Command.hpp"

class BotCommand : public Command {
  private:
    std::string _key;
    std::string _target;
    std::string _sender;
    std::string _source;

  public:
    BotCommand(std::string source, std::vector<std::string> params,
               Client* client);
    ~BotCommand();

    void imDad(std::string name);
    void joke();
    std::string joinMessage(std::vector<std::string>& splitData);
    void checkSender();
    void dadParse(std::string& data);
    void run();
};