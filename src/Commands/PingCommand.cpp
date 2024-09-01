#include "PingCommand.hpp"
#include "Server.hpp"
#include <vector>

PingCommand::PingCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    checkParams(client, params);
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

PingCommand::~PingCommand() {}

void PingCommand::checkParams(Client* client, std::vector<std::string> params) {
    if (params.size() < 1) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "PING"));
        throw ClientException();
    }
}

void PingCommand::run() {
    std::string reply =
        "PONG " + Server::getInstance().getPrefix() + " " + _params[0];
    reply = Message::create(reply);
    _client->sendMessage(reply);
}