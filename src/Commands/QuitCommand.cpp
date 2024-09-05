#include "QuitCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

QuitCommand::QuitCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    this->_reason = "";
    if (params.size() >= 1) {
        _reason = params[0];
    }
    this->_source = source;
    this->_client = client;
}

QuitCommand::~QuitCommand() {}

void QuitCommand::run() {
    std::string message = "Quit: " + _reason;
    std::map<std::string, Channel*> joinedChans = _client->getChannels();

    for (std::map<std::string, Channel*>::iterator it = joinedChans.begin();
         it != joinedChans.end(); ++it) {
        it->second->removeClient(_client);
        Server::getInstance().sendMessage(it->second, message, _client);
    }
    _client->sendMessage((Replies::ERR_QUIT(_client)));
}