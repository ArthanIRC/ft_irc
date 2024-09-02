#include "InviteCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Exception.hpp"
#include "Replies.hpp"

using std::string;
using std::vector;

InviteCommand::InviteCommand(string source, vector<string> params,
                             Client* client) {
    Channel* chan;
    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "INVITE"));
        throw ClientException();
    }

    try {
        chan = Server::getInstance().findChannel(params[1]);
    } catch (Server::ChannelNotFoundException&) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, params[1]));
        throw ClientException();
    }
    if (!chan->isInChannel(client)) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(client, chan));
        throw ClientException();
    }
    if (chan->isInviteOnly() && !chan->isOperator(client)) {
        client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(client, chan));
        throw ClientException();
    }
    if (chan->isInChannel(params[0])) {
        client->sendMessage(
            Replies::ERR_USERONCHANNEL(client, params[0], chan));
        throw ClientException();
    }
    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_targetNickname = params[0];
    this->_channel = chan;
}

InviteCommand::~InviteCommand(){};

void InviteCommand::run() {
    string reply;

    reply = ":" + _client->getNickname() + " INVITE " + _targetNickname + " " +
            _channel->getName();
    Message::create(reply);
    Client* target;
    try {
        target = Server::getInstance().findClient(_targetNickname);
    } catch (Server::ClientNotFoundException&) {
        _client->sendMessage(Replies::ERR_NOSUCHNICK(_client, _targetNickname));
        return;
    }
    _channel->inviteClient(target);
    _client->sendMessage(
        Replies::RPL_INVITING(_client, _targetNickname, _channel));
    target->sendMessage(reply);
}