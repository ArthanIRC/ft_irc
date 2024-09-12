#include "PartCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

PartCommand::PartCommand(string source, vector<string> params, Client* client) {
    checkParams(client, params);
    parseParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

PartCommand::~PartCommand() {}

void PartCommand::checkParams(Client* client, vector<string> params) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "PART"));
        throw ClientException();
    }
}

void PartCommand::parseParams(Client* client, vector<string> params) {
    std::istringstream iss(params[0]);
    string chanName;
    this->_reason = "";

    while (std::getline(iss, chanName, ',')) {
        chanName = toLowerCase(chanName);
        try {
            _channels.push_back(Server::getInstance().findChannel(chanName));
        } catch (const Server::ChannelNotFoundException&) {
            client->sendMessage(Replies::ERR_NOSUCHCHANNEL(client, chanName));
            continue;
        }
    }

    if (params.size() > 1) {
        _reason = params[1];
    }
}

string PartCommand::createReply(Channel* channel) {
    string reply;
    reply = ":" + _client->getNickname() + " PART " + channel->getName() + " " +
            _reason;
    return Message::create(reply);
}

void PartCommand::run() {
    for (size_t i = 0; i < _channels.size(); ++i) {
        if (_channels[i]->isInChannel(_client)) {
            if (_channels[i]->isOperator(_client))
                _channels[i]->removeOperator(_client);
            _channels[i]->removeClient(_client);
            string reply = createReply(_channels[i]);
            Server::getInstance().sendMessage(_channels[i], reply, _client);
            _client->sendMessage(reply);
        } else {
            _client->sendMessage(
                Replies::ERR_NOTONCHANNEL(_client, _channels[i]));
        }
    }
}