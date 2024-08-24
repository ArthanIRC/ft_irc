#include "InviteCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <exception>

InviteCommand::InviteCommand(std::string source,
                             std::vector<std::string> params, Client* client) {
    Channel* chan;
    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_nickname = params[0];
    this->_channel = params[1];
    try {
        chan = Server::getInstance().findChannel(params[1]);
    } catch (const std::exception& e) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(_client, _channel));
        throw;
    }
    if (params.size() < 2) {
    }
    if (!chan->isInChannel(*client)) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(_client, chan));
        throw;
    }
    if (chan->getInviteOnly() && !chan->isOperator(*client)) {
        client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(_client, chan));
        throw;
    }
    if (chan->isInChannel(params[0])) {
        client->sendMessage(Replies::ERR_USERONCHANNEL());
        throw;
    }
}

InviteCommand::~InviteCommand(){};

void InviteCommand::run() {
    std::string reply;

    reply = ":" + _client->getNickname() + " " + _command + " " + _params[0] +
            " " + _params[1];
    Message::create(reply);
    _client->sendMessage(Replies::RPL_INVITING());
    Client* target = Server::getInstance().findClient(_params[0]);
    try {
        target->sendMessage(reply);
    } catch (Server::ClientNotFoundException()) {
        return;
    }
    return;
}

/*
When the invite is successful, the server MUST send a RPL_INVITING numeric to
the command issuer, and an INVITE message, with the issuer as <source>, to the
target user. Other channel members SHOULD NOT be notified.
*/