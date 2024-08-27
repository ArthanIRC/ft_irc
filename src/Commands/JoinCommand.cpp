#include "JoinCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

JoinCommand::JoinCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

JoinCommand::~JoinCommand() {}

void JoinCommand::checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "JOIN"));
        throw;
    }
}

void JoinCommand::parseParams() {
    std::istringstream iss(_params[1]);
    std::istringstream iss2(_params[0]);
    std::string chanName;
    size_t i = 0;
    size_t j = 0;

    while (std::getline(iss, _keys[i], ','))
        j++;
    while (std::getline(iss2, chanName, ',')) {
        try {
            _channels[j] = Server::getInstance().findChannel(chanName);
        } catch (const Server::ChannelNotFoundException()) {
            try {
                if (i < _keys.size())
                    _channels[j] = new Channel(_client, chanName, _keys[j]);
                else
                    _channels[j] = new Channel(_client, chanName);
                Server::getInstance().addChannel(_channels[j]);
            } catch (Channel::wrongSyntaxChannelName()) {
                break;
            }
        }
        i++;
    }
}

void JoinCommand::joinAndReplies(Channel* channel) {
    try {
        channel->addClient(*_client);
    } catch (const Channel::userAlreadyExists()) {
        return;
    }

    std::string reply;
    reply = ":" + _client->getNickname() + " JOIN " + channel->getName();
    Message::create(reply);
    _client->sendMessage(reply);

    if (!channel->getTopic().empty()) {
        _client->sendMessage(Replies::RPL_TOPIC(_client, channel));
        _client->sendMessage(Replies::RPL_TOPICWHOTIME());
    }

    _client->sendMessage(Replies::RPL_NAMREPLY(_client, channel));
    _client->sendMessage(Replies::RPL_ENDOFNAMES(_client, channel));
}

void JoinCommand::run() {
    // if (_params[0] == "0") {
    //     std::vector<std::string> chanList;
    //     std::map<std::string, Channel*> mapChannel = _client.getChannels();
    //     std::map<std::string, Channel*>::const_iterator it =
    //     mapChannel.begin(); if (it != mapChannel.end()) {
    //         chanList[0] = it->first;
    //         ++it;
    //     }
    //     while (it != mapChannel.end()) {
    //         chanList[0] += "," + it->first;
    //         it++;
    //     }
    //     PartCommand p("", chanList, _client);
    //     p.run();
    //     return;
    // }
    parseParams();

    for (size_t i = 0; i < _channels.size(); ++i) {
        if (_channels[i]->isKeyed()) {
            if (i < _keys.size() || _keys[i] != _channels[i]->getKey()) {
                _client->sendMessage(Replies::ERR_BADCHANNELKEY());
                continue;
            }
        }

        if (_channels[i]->isBanned(*_client))
            _client->sendMessage(Replies::ERR_BANNEDFROMCHAN());

        else if (_channels[i]->getMaxClients() != 0 &&
                 _channels[i]->getMaxClients() ==
                     _channels[i]->getClients().size())
            _client->sendMessage(Replies::ERR_CHANNELISFULL());

        else if (_channels[i]->isInviteOnly() &&
                 !_channels[i]->isInvited(*_client))
            _client->sendMessage(Replies::ERR_INVITEONLYCHAN());

        else
            joinAndReplies(_channels[i]);
    }
}