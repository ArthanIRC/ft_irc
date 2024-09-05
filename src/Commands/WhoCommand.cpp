#include "WhoCommand.hpp"
#include "Channel.hpp"
#include "Server.hpp"
#include <cstddef>
#include <vector>

WhoCommand::WhoCommand(std::string source, std::vector<std::string> params,
                       Client* client) {

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
    if (chan != NULL) {
    }
}