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
    this->_target = toLowerCase(_params[0]);
}

WhoCommand::~WhoCommand() {}

void WhoCommand::run() {
    if (_params.size() < 1)
        return;

    Channel* chan;
    Client* cli;

    try {
        chan = Server::getInstance().findChannel(_target);
    } catch (const Server::ChannelNotFoundException&) {
        chan = NULL;
    }

    try {
        cli = Server::getInstance().findClient(_target);
    } catch (const Server::ClientNotFoundException&) {
        cli = NULL;
    }

    if (chan == NULL && cli == NULL)
        return;

    if (cli != NULL) {
        map<string, Channel*> channels = _client->getChannels();
        for (map<string, Channel*>::iterator it = channels.begin();
             it != channels.end(); it++) {
            if (it->second->isInChannel(cli)) {
                _client->sendMessage(
                    Replies::RPL_WHOREPLY(_client, cli, it->second));
                _client->sendMessage(Replies::RPL_ENDOFWHO(_client, _target));
                return;
            }
        }
        if (!cli->isInvisible()) {
            _client->sendMessage(Replies::RPL_WHOREPLY(_client, cli, NULL));
            _client->sendMessage(Replies::RPL_ENDOFWHO(_client, _target));
        }
    } else {
        vector<Client*> clients = chan->getClients();
        for (vector<Client*>::iterator it = clients.begin();
             it != clients.end(); it++) {
            if (chan->isInChannel(_client))
                _client->sendMessage(Replies::RPL_WHOREPLY(_client, *it, chan));
        }
        _client->sendMessage(Replies::RPL_ENDOFWHO(_client, _target));
    }
}