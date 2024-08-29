#include "MotdCommand.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Server.hpp"

MotdCommand::MotdCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    (void)params;
    this->_source = source;
    this->_client = client;
}

MotdCommand::~MotdCommand(){};

void MotdCommand::run() {
    std::string motd = Server::getInstance().getMotd();
    if (motd.empty()) {
        _client->sendMessage(Replies::ERR_NOMOTD(_client));
        return;
    }
    _client->sendMessage(Replies::RPL_MOTDSTART(_client));
    _client->sendMessage(Replies::RPL_MOTD(_client, motd));
    _client->sendMessage(Replies::RPL_ENDOFMOTD(_client));
}