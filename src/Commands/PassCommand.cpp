#include "PassCommand.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

PassCommand::PassCommand(string source, vector<string> params, Client* client) {
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
    string serverPass = Server::getInstance().getPassword();

    if (serverPass.empty()) {
        _client->setState(PASS_DONE);
        return;
    }
    if (_client->getState() >= PASS_DONE) {
        _client->sendMessage(Replies::ERR_ALREADYREGISTERED(_client));
        return;
    }
    if (_password != serverPass) {
        _client->sendMessage(Replies::ERR_PASSWDMISMATCH(_client));
        throw RegFailedException();
    }
    _client->setState(PASS_DONE);
    return;
}
