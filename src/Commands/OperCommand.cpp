#include "OperCommand.hpp"
#include "Client.hpp"
#include "ModeCommand.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include <map>

OperCommand::OperCommand(std::string source, std::vector<std::string> params,
                         Client* client) {
    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "OPER"));
        throw;
    }
    this->_name = params[0];
    this->_password = params[1];
    this->_source = source;
    this->_client = client;
}

OperCommand::~OperCommand() {}

void OperCommand::run() {
    if (_name.empty() || _password.empty())
        return;
    std::map<std::string, std::string> serverOperators =
        Server::getInstance().getOperators();
    if (serverOperators.find(_name) == serverOperators.end()) {
        _client->sendMessage(Replies::ERR_NOOPERHOST());
        return;
    } else {
        if (serverOperators[_name] != _password) {
            _client->sendMessage(Replies::ERR_PASSWDMISMATCH(_client));
            return;
        }
    }
    _client->setState(OPERATOR);
    _client->sendMessage(Replies::RPL_YOUREOPER());
    std::string reply = ":" + Server::getInstance().getPrefix() + " MODE " +
                        _client->getNickname() + " +o";
    _client->sendMessage(Message::create(reply));
}
