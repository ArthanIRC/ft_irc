#include "MotdCommand.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::string;
using std::vector;

MotdCommand::MotdCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    this->_params = params;
    this->_source = source;
    this->_client = client;
}

MotdCommand::~MotdCommand(){};

void MotdCommand::run() {
    string motd = Server::getInstance().getMotd();
    if (motd.empty()) {
        _client->sendMessage(Replies::ERR_NOMOTD(_client));
        return;
    }
    _client->sendMessage(Replies::RPL_MOTDSTART(_client));
    _client->sendMessage(Replies::RPL_MOTD(_client, motd));
    _client->sendMessage(Replies::RPL_ENDOFMOTD(_client));
}