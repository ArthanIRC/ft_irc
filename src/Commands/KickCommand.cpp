#include "KickCommand.hpp"
#include "Exception.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

KickCommand::KickCommand(string source, vector<string> params, Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

KickCommand::~KickCommand() {}

void KickCommand::checkParams(Client* client, vector<string> params) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "KICK"));
        throw ClientException();
    }

    if (params[1][params[1].size() - 1] == ',') {
        params[1] = params[1].substr(0, params[1].size() - 1);
    }

    Channel* chan;
    string targetNickName = toLowerCase(params[1]);
    string chanName = toLowerCase(params[0]);

    try {
        chan = Server::getInstance().findChannel(chanName);
    } catch (const Server::ChannelNotFoundException&) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, chanName));
        throw ClientException();
    }

    this->_channel = chan;

    if (!chan->isInChannel(client)) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(client, _channel));
        throw ClientException();
    }

    try {
        this->_target = Server::getInstance().findClient(targetNickName);
    } catch (Server::ClientNotFoundException&) {
        client->sendMessage(Replies::ERR_NOSUCHNICK(client, targetNickName));
        throw ClientException();
    }

    if (!chan->isOperator(client) || chan->isOperator(_target)) {
        client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(client, chan));
        throw ClientException();
    }

    if (!chan->isInChannel(_target)) {
        client->sendMessage(
            Replies::ERR_USERNOTINCHANNEL(client, targetNickName, _channel));
        throw ClientException();
    }

    if (params[params.size() - 2].find(',') == string::npos) {
        this->_comment = params[params.size() - 1];
    } else
        this->_comment = "";
}

void KickCommand::run() {
    string reply;
    reply = ":" + _client->getSource() + " KICK " + _channel->getName() + " " +
            _target->getNickname() + " " + _comment;
    Message::create(reply);

    _channel->removeClient(_target);
    _target->sendMessage(reply);
    Server::getInstance().sendMessage(_channel, reply, NULL);
}