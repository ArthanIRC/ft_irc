#include "PrivmsgCommand.hpp"
#include "Channel.hpp"

using std::string;
using std::vector;

PrivmsgCommand::PrivmsgCommand(string source, vector<string> params,
                               Client* client) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NORECIPIENT(client));
        throw ClientException();
    }
    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NOTEXTTOSEND(client));
        throw ClientException();
    }

    this->_targets = split(params[0], ',');
    this->_message = params[1];
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

PrivmsgCommand::~PrivmsgCommand() {}

void PrivmsgCommand::sendToChannel(string& target) {
    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(target);
    } catch (Server::ChannelNotFoundException&) {
        _client->sendMessage(Replies::ERR_NOSUCHNICK(_client, target));
        return;
    }

    if (chan->isBanned(_client))
        return;

    if (chan->isNoExternal() && !chan->isInChannel(_client)) {
        _client->sendMessage(Replies::ERR_CANNOTSENDTOCHAN(_client, target));
        return;
    }

    if ((chan->isInviteOnly() && !chan->isInvited(_client) &&
         !chan->isNoExternal()) ||
        (chan->isModerated() && !chan->isVoiced(_client))) {
        _client->sendMessage(Replies::ERR_CANNOTSENDTOCHAN(_client, target));
        return;
    }

    string message =
        ":" + _client->getSource() + " PRIVMSG " + target + " " + _message;
    Server::getInstance().sendMessage(chan, Message::create(message), _client);
}

void PrivmsgCommand::sendToClient(string& target) {
    Client* cli;

    try {
        cli = Server::getInstance().findClient(target);
    } catch (Server::ClientNotFoundException&) {
        _client->sendMessage(Replies::ERR_NOSUCHNICK(_client, target));
        return;
    }

    string message =
        ":" + _client->getSource() + " PRIVMSG " + target + " " + _message;
    cli->sendMessage(Message::create(message));
}

void PrivmsgCommand::run() {
    for (vector<string>::iterator it = this->_targets.begin();
         it < this->_targets.end(); it++) {
        if ((*it)[0] == '#')
            sendToChannel(*it);
        else
            sendToClient(*it);
    }
}