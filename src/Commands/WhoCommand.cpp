#include "WhoCommand.hpp"
#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include <cstddef>
#include <map>
#include <vector>

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
        map<string, Channel*> chansClient = _client->getChannels();
        map<string, Channel*> chansTarget = target->getChannels();
        map<string, Channel*>::iterator it = chansClient.begin();
        map<string, Channel*>::iterator itt;
        while (it != chansClient.end()) {
            itt = chansTarget.begin();
            while (itt != chansTarget.end()) {
                if ((*it) == (*itt) || !target->isInvisible()) {
                    _client->sendMessage(Replies::RPL_WHOREPLY());
                    _client->sendMessage(Replies::RPL_ENDOFWHO());
                    return;
                }
                itt++;
            }
            it++;
        }
    } else {
        vector<Client*> clients = chan->getClients();
        for (vector<Client*>::iterator it = clients.begin();
             it != clients.end(); it++) {
            if (!chan->isInChannel(_client) && (*it)->isInvisible())
                continue;
            _client->sendMessage(Replies::RPL_WHOREPLY());
        }
        _client->sendMessage(Replies::RPL_ENDOFWHO());
    }
}