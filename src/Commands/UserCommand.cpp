#include "UserCommand.hpp"
#include "CapCommand.hpp"
#include "Client.hpp"
#include "Exception.hpp"

using std::string;
using std::vector;

UserCommand::UserCommand(string source, vector<string> params, Client* client) {

    if (params.size() < 4) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "USER"));
        throw ClientException();
    }

    if (client->getState() < NICK_DONE)
        throw RegFailedException();

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

    if (_client->hasCapEndedEarly()) {
        vector<string> paraOut;
        paraOut.push_back("END");
        CapCommand cap("", paraOut, _client);
        cap.run();
    }
}