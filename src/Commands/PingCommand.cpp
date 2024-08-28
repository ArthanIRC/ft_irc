#include "PingCommand.hpp"
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
        throw;
    }
}

void PingCommand::run() {
    std::string reply = "PONG " + _params[0];
    reply = Message::create(reply);
    _client->sendMessage(reply);
}