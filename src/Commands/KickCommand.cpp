#include "KickCommand.hpp"

KickCommand::KickCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

KickCommand::~KickCommand() {}

void KickCommand::checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "KICK"));
        throw ClientException();
    }
    if (params[1][params[1].size() - 1] == ',') {
        params[1] = params[1].substr(0, params[1].size() - 1);
    }
    Channel* chan;
    try {
        chan = Server::getInstance().findChannel(params[0]);
    } catch (const Server::ChannelNotFoundException&) {
        client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, params[0]));
        throw ClientException();
    }
    this->_channel = chan;
    if (!chan->isInChannel(client)) {
        client->sendMessage(Replies::ERR_NOTONCHANNEL(client, chan));
        throw ClientException();
    }
    if (!chan->isOperator(client)) {
        client->sendMessage(Replies::ERR_CHANOPRIVSNEEDED(client, chan));
        throw ClientException();
    }
    if (!chan->isInChannel(params[1])) {
        client->sendMessage(
            Replies::ERR_USERNOTINCHANNEL(_client, params[1], _channel));
        throw ClientException();
    }
    this->_targetNickname = params[1];
    if (params[params.size() - 2].find(',') == std::string::npos) {
        this->_comment = params[params.size() - 1];
    } else
        this->_comment = "";
}

void KickCommand::run() {
    std::string reply;

    reply = ":" + _client->getNickname() + " KICK " + _channel->getName() +
            _targetNickname + " " + _comment;
    Message::create(reply);
    Client* target;
    try {
        target = Server::getInstance().findClient(_targetNickname);
    } catch (Server::ClientNotFoundException&) {
        _client->sendMessage(Replies::ERR_NOSUCHNICK(_client, _targetNickname));
        return;
    }
    _channel->eraseClient(target);
    if (_channel->isOperator(target))
        _channel->eraseOperator(target);
    target->sendMessage(reply);
}