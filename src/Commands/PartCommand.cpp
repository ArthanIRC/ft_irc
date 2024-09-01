#include "PartCommand.hpp"
#include "Replies.hpp"
#include <string>

PartCommand::PartCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    checkParams(client, params);
    parseParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

PartCommand::~PartCommand() {}

void PartCommand::checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "PART"));
        throw ClientException();
    }
}

void PartCommand::parseParams(Client* client, std::vector<std::string> params) {
    std::istringstream iss(params[0]);
    std::string chanName;
    size_t i = 0;
    this->_reason = "";

    while (std::getline(iss, chanName, ',')) {
        try {
            _channels[i] = Server::getInstance().findChannel(chanName);
        } catch (const Server::ChannelNotFoundException()) {
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, chanName));
            continue;
        }
        i++;
    }
    if (params.size() > 1) {
        _reason = params[1];
    }
}

std::string PartCommand::createReply(Channel* channel) {
    std::string reply;

    reply = ":" + _client->getNickname() + " PART " + channel->getName() + " " +
            _reason;

    return reply;
}

void PartCommand::run() {
    for (size_t i = 0; i < _channels.size(); ++i) {
        if (_channels[i]->isInChannel(_client)) {
            if (_channels[i]->isOperator(_client))
                _channels[i]->eraseOperator(_client);
            _channels[i]->eraseClient(_client);
            std::string reply = createReply(_channels[i]);
            Message::create(reply);
            Server::getInstance().sendMessage(_channels[i], reply);
        } else {
            _client->sendMessage(
                Replies::ERR_NOTONCHANNEL(_client, _channels[i]));
        }
    }
}