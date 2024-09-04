#include "OperCommand.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Server.hpp"

using std::map;
using std::string;
using std::vector;

OperCommand::OperCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.size() < 2) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "OPER"));
        throw ClientException();
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
    map<string, string> serverOperators = Server::getInstance().getOperators();
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
    _client->sendMessage(Replies::RPL_YOUREOPER(_client));
    string reply = ":" + Server::getInstance().getSource() + " MODE " +
                   _client->getNickname() + " +o";
    _client->sendMessage(Message::create(reply));
}
