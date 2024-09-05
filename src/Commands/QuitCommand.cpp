#include "QuitCommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

QuitCommand::QuitCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }
    if (params.size() >= 1) {
        this->_reason = params[0];
    }
    this->_source = source;
    this->_client = client;
}

QuitCommand::~QuitCommand() {}

void QuitCommand::run() {
    std::string message =
        ":" + _client->getSource() + " QUIT :Quit: " + _reason;
    ;
    std::map<std::string, Channel*> joinedChans = _client->getChannels();
    Server::getInstance().sendMessage(joinedChans, message, _client);
    _client->sendMessage((Replies::ERR_QUIT(_reason)));
    Server::getInstance().removeClient(_client);
}