#include "WhoCommand.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::map;
using std::string;
using std::vector;

WhoCommand::WhoCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
}

WhoCommand::~WhoCommand() {}

void WhoCommand::run() {
    if (_params.size() < 1)
        return;

    Channel* chan;
    Client* target;

    try {
        chan = Server::getInstance().findChannel(_params[0]);
    } catch (const Server::ChannelNotFoundException&) {
        chan = NULL;
    }

    try {
        target = Server::getInstance().findClient(_params[0]);
    } catch (const Server::ClientNotFoundException&) {
        target = NULL;
    }

    if (chan == NULL && target == NULL)
        return;

    if (target != NULL) {
        map<string, Channel*> channels = _client->getChannels();
        for (map<string, Channel*>::iterator it = channels.begin();
             it != channels.end(); it++) {
            if (it->second->isInChannel(target)) {
                _client->sendMessage(
                    Replies::RPL_WHOREPLY(_client, target, it->second));
                _client->sendMessage(
                    Replies::RPL_ENDOFWHO(_client, _params[0]));
                return;
            }
        }
        if (!target->isInvisible()) {
            _client->sendMessage(Replies::RPL_WHOREPLY(_client, target, NULL));
            _client->sendMessage(Replies::RPL_ENDOFWHO(_client, _params[0]));
        }
    } else {
        vector<Client*> clients = chan->getClients();
        for (vector<Client*>::iterator it = clients.begin();
             it != clients.end(); it++) {
            if (chan->isInChannel(_client))
                _client->sendMessage(Replies::RPL_WHOREPLY(_client, *it, chan));
        }
        _client->sendMessage(Replies::RPL_ENDOFWHO(_client, _params[0]));
    }
}