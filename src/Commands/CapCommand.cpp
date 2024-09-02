#include "CapCommand.hpp"
#include "Client.hpp"
#include "LusersCommand.hpp"
#include "MotdCommand.hpp"

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
        string message = ":" + Server::getInstance().getSource() + " CAP * LS";
        _client->sendMessage(Message::create(message));
        _client->setState(CAP_STARTED);
    } else if (_params[0] == "END") {
        if (_client->getState() != USER_DONE) {
            if (_client->getState() == CAP_STARTED)
                _client->setCapEndedEarly();
            else {
                _client->sendMessage(Replies::ERR_REGFAILED());
                Server::getInstance().removeClient(_client);
            }
            return;
        } else
            _client->setState(REGISTERED);
        _client->sendMessage(
            Replies::RPL_WELCOME(_client, Server::getInstance()));
        _client->sendMessage(
            Replies::RPL_YOURHOST(_client, Server::getInstance()));
        _client->sendMessage(
            Replies::RPL_CREATED(_client, Server::getInstance()));
        _client->sendMessage(
            Replies::RPL_MYINFO(_client, Server::getInstance()));
        _client->sendMessage(
            Replies::RPL_ISUPPORT1(_client, Server::getInstance()));
        _client->sendMessage(
            Replies::RPL_ISUPPORT2(_client, Server::getInstance()));
        LusersCommand lusers(_source, _params, _client);
        lusers.run();
        MotdCommand motd(_source, _params, _client);
        motd.run();
        _client->sendMessage(Replies::RPL_UMODEIS(_client));
    }
}