#include "NamesCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include <string>

NamesCommand::NamesCommand(std::string source, std::vector<std::string> params,
                           Client* client) {
    if (params.size() > 0) {
        this->_params[0] = params[0];
    } else {
        this->_params.push_back("");
    }
    this->_source = source;
    this->_client = client;
}

NamesCommand::~NamesCommand(){};

void NamesCommand::run() {
    if (_params[0].empty()) {
        std::map<std::string, Channel*> allChannels =
            Server::getInstance().getChannels();
        for (std::map<std::string, Channel*>::iterator it = allChannels.begin();
             it != allChannels.end(); ++it) {
            _client->sendMessage(Replies::RPL_NAMREPLY(_client, it->second));
            _client->sendMessage(
                Replies::RPL_ENDOFNAMES(_client, it->second->getName()));
        }
    } else {
        std::vector<std::string> channels = split(_params[0], ',');
        Channel* currChannel;
        for (std::vector<std::string>::iterator it = channels.begin();
             it != channels.end(); ++it) {
            try {
                currChannel = Server::getInstance().findChannel(*it);
                _client->sendMessage(
                    Replies::RPL_NAMREPLY(_client, currChannel));
            } catch (Server::ChannelNotFoundException&) {
                _client->sendMessage(Replies::RPL_ENDOFNAMES(_client, *it));
                continue;
            }
            _client->sendMessage(
                Replies::RPL_ENDOFNAMES(_client, currChannel->getName()));
        }
    }
    return;
}