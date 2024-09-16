#include "QuitCommand.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

QuitCommand::QuitCommand(string source, vector<string> params, Client* client) {
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
    string message = ":" + _client->getSource() + " QUIT :Quit: " + _reason;
    Server::getInstance().sendMessage(_client->getChannels(),
                                      Message::create(message), _client);
    _client->sendMessage((Replies::ERR_QUIT()));
    Server::getInstance().removeClient(_client);
}