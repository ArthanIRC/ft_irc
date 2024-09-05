#include "AwayCommand.hpp"

using std::map;
using std::string;
using std::vector;

AwayCommand::AwayCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
}

AwayCommand::~AwayCommand() {}

void AwayCommand::run() {
    if (_params.empty()) {
        _client->setAway(false, "");
        _client->sendMessage(Replies::RPL_UNAWAY(_client));
    } else {
        _client->setAway(true, _params[0]);
        _client->sendMessage(Replies::RPL_NOWAWAY(_client));
    }

    string message =
        ":" + _client->getSource() + " AWAY " + _client->getAwayMsg();
    map<string, Channel*> channels = _client->getChannels();
    Server::getInstance().sendMessageIfAway(channels, Message::create(message),
                                            _client);
}