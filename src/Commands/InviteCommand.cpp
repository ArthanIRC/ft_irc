#include "InviteCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"

InviteCommand::InviteCommand(std::string source,
                             std::vector<std::string> params, Client* client) {
    Channel* chan;
    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "INVITE"));
        throw;
    }
    try {
        chan = Server::getInstance().findChannel(params[1]);
    } catch (Server::ChannelNotFoundException()) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(_client, params[1]));
        throw;
    }
    if (!chan->isInChannel(client)) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(_client, chan));
        throw;
    }
    if (chan->isInviteOnly() && !chan->isOperator(client)) {
        client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(_client, chan));
        throw;
    }
    if (chan->isInChannel(params[0])) {
        client->sendMessage(Replies::ERR_USERONCHANNEL());
        throw;
    }
    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_targetNickname = params[0];
    this->_channel = chan;
}

InviteCommand::~InviteCommand(){};

void InviteCommand::run() {
    std::string reply;

    reply = ":" + _client->getNickname() + " INVITE " + _targetNickname + " " +
            _channel->getName();
    Message::create(reply);
    Client* target;
    try {
        target = Server::getInstance().findClient(_targetNickname);
    } catch (Server::ClientNotFoundException()) {
        _client->sendMessage(Replies::ERR_NOSUCHNICK(_client, _targetNickname));
        return;
    }
    _channel->inviteClient(target);
    _client->sendMessage(Replies::RPL_INVITING());
    target->sendMessage(reply);
}