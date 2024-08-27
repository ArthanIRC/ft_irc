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

void JoinCommand::setLists() {
    std::istringstream iss(_params[0]);
    std::istringstream iss2(_params[1]);
    std::string chanName;
    size_t i = 0;
    size_t j = 0;

    while (std::getline(iss, chanName, ',')) {
        try {
            _chanlist[i] = Server::getInstance().findChannel(chanName);
        } catch (const Server::ChannelNotFoundException()) {
            try {
                if (i < _keylist.size())
                    _chanlist[i] = new Channel(_client, chanName, _keylist[i]);
                else
                    _chanlist[i] = new Channel(_client, chanName);
                Server::getInstance().addChannel(_chanlist[i]);
            } catch (Channel::wrongSyntaxChannelName()) {
                throw Channel::wrongSyntaxChannelName();
            }
        }
        i++;
    }
    while (std::getline(iss2, _keylist[j], ','))
        j++;
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
    setLists();

    size_t i = 0;
    while (i < _chanlist.size()) {
        if (_chanlist[i]->isKeyed()) {
            if (i < _keylist.size() || _keylist[i] != _chanlist[i]->getKey()) {
                _client->sendMessage(Replies::ERR_BADCHANNELKEY());
                continue;
            }
        }

        if (_chanlist[i]->isBanned(*_client))
            _client->sendMessage(Replies::ERR_BANNEDFROMCHAN());

        else if (_chanlist[i]->getMaxClients() != 0 &&
                 _chanlist[i]->getMaxClients() ==
                     _chanlist[i]->getClients().size())
            _client->sendMessage(Replies::ERR_CHANNELISFULL());

        else if (_chanlist[i]->isInviteOnly() &&
                 !_chanlist[i]->isInvited(*_client))
            _client->sendMessage(Replies::ERR_INVITEONLYCHAN());

        else
            joinAndReplies(_chanlist[i]);

        i++;
    }
}