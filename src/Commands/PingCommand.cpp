#include "PingCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

PingCommand::PingCommand(string source, vector<string> params, Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

PingCommand::~PingCommand() {}

void PingCommand::checkParams(Client* client, vector<string> params) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "PING"));
        throw ClientException();
    }
}

void PingCommand::run() {
    string reply =
        "PONG " + Server::getInstance().getSource() + " " + _params[0];
    reply = Message::create(reply);
    _client->sendMessage(reply);
}