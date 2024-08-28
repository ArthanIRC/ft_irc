#include "CapCommand.hpp"
#include "Client.hpp"

using std::string;
using std::vector;

CapCommand::CapCommand(string source, vector<string> params, Client* client) {
    this->_source = source;
    this->_params = params;
    this->_client = client;
}

CapCommand::~CapCommand() {}

void CapCommand::run() {
    if (_params.empty())
        return;

    if (_params[0] == "LS") {
        string message = Server::getInstance().getPrefix() + " CAP LS *";
        _client->sendMessage(Message::create(message));
    } else if (_params[0] == "END") {
        if (_client->getState() != USER_DONE) {
            _client->sendMessage(Replies::ERR_REGFAILED());
        } else
            _client->setState(REGISTERED);
        _client->sendMessage(Replies::RPL_WELCOME(
            _client, Server::getInstance().getNetworkName()));
        _client->sendMessage(Replies::RPL_YOURHOST(
            _client, Server::getInstance().getServerName(),
            Server::getInstance().getVersion()));
        _client->sendMessage(Replies::RPL_CREATED(
            _client, Server::getInstance().getCreationDate()));
        _client->sendMessage(Replies::RPL_MYINFO());
        _client->sendMessage(Replies::RPL_ISUPPORT());
        // LUSER Command
        // MOTD Command
        _client->sendMessage(Replies::RPL_UMODEIS(_client));
    }
}