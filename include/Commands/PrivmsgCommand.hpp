#include "Command.hpp"

class PrivmsgCommand : public Command {
  private:
    std::vector<std::string> _targets;
    std::string _message;

    void sendToChannel(std::string& target);
    void sendToClient(std::string& target);

  public:
    PrivmsgCommand(std::string source, std::vector<std::string> params,
                   Client* client);
    ~PrivmsgCommand();

    void run();
};