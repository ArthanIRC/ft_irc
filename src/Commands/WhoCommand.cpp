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
        // comparer si le client et la target on un chan en commun
        _client->sendMessage(Replies::RPL_WHOREPLY());
        _client->sendMessage(Replies::RPL_ENDOFWHO());
        return;
    }
    map<string, Client*> clients = chan->getClients();
    for (map<string, Client*>::iterator it = clients.begin();
         it != clients.end(); it++) {
        if (!chan->isInChannel(_client) && (*it).second->isInvisible())
            continue;
        _client->sendMessage(Replies::RPL_WHOREPLY());
    }
    _client->sendMessage(Replies::RPL_ENDOFWHO());
}
// on va encoyer (*it).second dans la RPL_WHOREPLY en tant que target
// trouver une solution pour host