#include "PartCommand.hpp"
#include "Replies.hpp"

PartCommand::PartCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    checkParams(client, params);
    parseParams(client);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

void PartCommand::checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "JOIN"));
        throw;
    }
}

void PartCommand::parseParams(Client* client) {
    std::istringstream iss(_params[0]);
    std::string chanName;
    size_t i = 0;

    while (std::getline(iss, chanName, ',')) {
        try {
            _channels[i] = Server::getInstance().findChannel(chanName);
        } catch (const Server::ChannelNotFoundException()) {
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, chanName));
            continue;
        }
        i++;
    }
}

void PartCommand::run() {
    for (size_t i = 0; i < _channels.size(); ++i) {
        if
    }
}