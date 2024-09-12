#include "InviteCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Exception.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

InviteCommand::InviteCommand(string source, vector<string> params,
                             Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    Channel* chan;
    string chanName = toLowerCase(params[1]);
    this->_targetNickname = toLowerCase(params[0]);

    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "INVITE"));
        throw ClientException();
    }

    try {
        chan = Server::getInstance().findChannel(chanName);
    } catch (Server::ChannelNotFoundException&) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, chanName));
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

    if (chan->isInChannel(_targetNickname)) {
        client->sendMessage(
            Replies::ERR_USERONCHANNEL(client, _targetNickname, chan));
        throw ClientException();
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
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