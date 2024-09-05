#include "QuitCommand.hpp"
#include "Client.hpp"
#include "Message.hpp"
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
    _client->getChannels();
    // std::string reply = "ERROR: " + _reason;
    // reply = Message::create(reply);
    // _client->sendMessage(reply);
}

/*
avertir tous les channels ou je suis que je QUIT
QUIT les channels ou je suis

*/