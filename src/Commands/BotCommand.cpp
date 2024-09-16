#include "BotCommand.hpp"
#include "Client.hpp"
#include "Exception.hpp"
#include "JoinCommand.hpp"
#include "Replies.hpp"
#include <vector>

using std::map;
using std::string;
using std::vector;

BotCommand::BotCommand(string source, vector<string> params, Client* client) {
    if (!client->isRegistered()) {
        client->sendMessage(Replies::ERR_NOTREGISTERED());
        throw ClientException();
    }

    if (params.empty()) {
        client->sendMessage(Replies::ERR_NEEDMOREPARAMS(client, "BOT"));
        throw ClientException();
    }

    this->_source = source;
    this->_params = params;
    this->_client = client;
    this->_key = params[0];
}

BotCommand::~BotCommand() {}

void BotCommand::run() {
    if (Server::getInstance().getBotKey() != _key) {
        _client->sendMessage(Replies::ERR_INVALIDBOTKEY(_client));
        return;
    }

    _client->setState(OPERATOR);
    _client->setBot(true);
    _client->sendMessage(Replies::RPL_YOUREPRIVBOT(_client));
    _client->sendMessage(Replies::RPL_YOUREOPER(_client));
    string reply = ":" + Server::getInstance().getSource() + " MODE " +
                   _client->getNickname() + " +Bo";
    _client->sendMessage(Message::create(reply));

    map<string, Channel*> channels = Server::getInstance().getChannels();
    string chansToJoin;
    for (map<string, Channel*>::iterator it = channels.begin();
         it != channels.end(); it++) {
        if (!chansToJoin.empty())
            chansToJoin += ",";
        chansToJoin += it->first;
    }

    vector<string> tmp;
    tmp.push_back(chansToJoin);
    JoinCommand j("", tmp, _client);
    j.run();
}