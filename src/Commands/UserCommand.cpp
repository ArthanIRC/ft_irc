#include "UserCommand.hpp"
#include "Client.hpp"

UserCommand::UserCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 4) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "USER"));
        throw;
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_username = params[0];
    this->_realname = params[3];
}

UserCommand::~UserCommand() {}

void UserCommand::run() {
    if (_client->getState() >= USER_DONE) {
        _client->sendMessage(Replies::ERR_ALREADYREGISTERED(_client));
        return;
    }

    _client->setUsername(_username);
    _client->setRealname(_realname);
    _client->setState(USER_DONE);
}