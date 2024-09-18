#include "NamesCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::map;
using std::string;
using std::vector;

NamesCommand::NamesCommand(string source, vector<string> params,
                           Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.size() > 0)
        this->_params.push_back(toLowerCase(params[0]));
    else
        this->_params.push_back("");

    this->_source = source;
    this->_client = client;
}

NamesCommand::~NamesCommand(){};

void NamesCommand::run() {
    if (_params[0].empty()) {
        map<string, Channel*> allChannels = Server::getInstance().getChannels();
        for (map<string, Channel*>::iterator it = allChannels.begin();
             it != allChannels.end(); ++it) {
            _client->sendMessage(Replies::RPL_NAMREPLY(_client, it->second));
            _client->sendMessage(
                Replies::RPL_ENDOFNAMES(_client, it->second->getName()));
        }
    } else {
        vector<string> channels = split(_params[0], ',');
        Channel* currChannel;
        for (vector<string>::iterator it = channels.begin();
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
