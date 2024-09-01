#include "PassCommand.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include <cctype>

PassCommand::PassCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "PASS"));
        throw ClientException();
    }
    if (!source.empty()) {
        throw ClientException();
    }
    this->_client = client;
    this->_password = params[0];
};

PassCommand::~PassCommand(){};

void PassCommand::run() {
    std::string serverPass = Server::getInstance().getPassword();

    if (serverPass.empty()) {
        _client->setState(PASS_DONE);
        return;
    }
    if (_client->getState() != UNKNOWN) {
        client->sendMessage(Replies::ERR_ALREADYREGISTERED(_client));
        throw;
    }
    if (_password != serverPass) {
        client->sendMessage(Replies::ERR_PASSWDMISMATCH(_client));
        throw;
    }
    _client->setState(PASS_DONE);
    return;
}
